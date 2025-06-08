/************************************************************
 *  - GitHub firmware fetch
 *  - Local file load
 *  - Intel HEX parsing -> 1KB blocks
 *  - WebHID upload to Teensy bootloader
 *  - Serial open/close
 ************************************************************/

// ===== DOM Elements / Globals =====
const statusElement = document.getElementById("status");
const progressElement = document.getElementById("progress");
const outputBox = document.getElementById("serial-output");
const firmwareSelect = document.getElementById("firmware-select");
const radioButtons = document.querySelectorAll('input[name="firmware-source"]');
const latestBuildsDiv = document.getElementById("latest-builds");
const localFileDiv = document.getElementById("local-file");
const firmwareInput = document.getElementById("firmware");
let firmwareFile = null;
let firmwareFileName = null;
let device = null;
let serialPort = null;
let serialReader = null;
const outputBuffer = [];
let incompleteLine = "";

// GitHub API URL for ProtoTracer releases
const githubReleasesUrl = "https://api.github.com/repos/coelacant1/ProtoTracer/releases/latest";

// ===== Utility Functions =====
function setStatus(message) {
    statusElement.textContent = message;
}

function appendOutput(message) {
    outputBuffer.push(message);
    if (outputBuffer.length > 20) {
        outputBuffer.shift();
    }
    outputBox.value = outputBuffer.join("\n");
    outputBox.scrollTop = outputBox.scrollHeight;
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

// ===== GitHub Firmware Fetch =====
async function fetchFirmwareFiles() {
    try {
        const response = await fetch(githubReleasesUrl);
        if (!response.ok) {
            throw new Error(`GitHub API error: ${response.status}`);
        }

        const releaseData = await response.json();
        const assets = releaseData.assets || [];
        const hexFiles = assets.filter(asset => asset.name.endsWith(".hex"));

        if (hexFiles.length === 0) {
            setStatus("No firmware files found in the latest release.");
            return;
        }

        firmwareSelect.innerHTML = "";
        hexFiles.forEach(file => {
            const option = document.createElement("option");
            option.value = file.browser_download_url;
            option.textContent = file.name;
            firmwareSelect.appendChild(option);
        });

        setStatus("Firmware files loaded from the latest release.");
    } catch (error) {
        console.error(error);
        setStatus("Failed to fetch firmware files from GitHub.");
    }
}

// Initialize the dropdown on page load
document.addEventListener("DOMContentLoaded", fetchFirmwareFiles);

// Toggle firmware source
radioButtons.forEach(radio => {
    radio.addEventListener("change", (event) => {
        if (event.target.value === "latest-builds") {
            latestBuildsDiv.style.display = "block";
            localFileDiv.style.display = "none";
            firmwareFile = null;
        } else if (event.target.value === "local-file") {
            latestBuildsDiv.style.display = "none";
            localFileDiv.style.display = "block";
            firmwareFile = null;
        }
        setStatus("Select a firmware file.");
        document.getElementById("upload").disabled = true;
    });
});

// Handle local file upload
firmwareInput.addEventListener("change", (event) => {
    const file = event.target.files[0];
    if (file) {
        const reader = new FileReader();
        reader.onload = () => {
            firmwareFile = new Uint8Array(reader.result);
            firmwareFileName = file.name.toLowerCase();
            setStatus(`Firmware loaded: ${firmwareFileName}`);
            document.getElementById("upload").disabled = false;
        };
        reader.onerror = () => {
            setStatus("Error reading the firmware file.");
        };
        reader.readAsArrayBuffer(file);
    } else {
        firmwareFile = null;
        firmwareFileName = null;
        setStatus("No firmware file selected.");
    }
});

// Handle firmware selection from dropdown
firmwareSelect.addEventListener("change", async (event) => {
    const url = `${event.target.value}`;

    if (!url) {
        setStatus("No firmware file selected.");
        firmwareFile = null;
        firmwareFileName = null;
        return;
    }

    try {
        setStatus("Downloading firmware...");
        const response = await fetch(url);
        if (!response.ok) {
            throw new Error(`Download error: ${response.status}`);
        }

        const arrayBuffer = await response.arrayBuffer();
        firmwareFile = new Uint8Array(arrayBuffer);
        firmwareFileName = url.split("/").pop().toLowerCase();
        setStatus(`Firmware loaded: ${firmwareFileName}`);
        document.getElementById("upload").disabled = false;
    } catch (error) {
        console.error(error);
        setStatus("Failed to download the firmware file.");
    }
});

// Select Teensy device
document.getElementById("select-device").addEventListener("click", async () => {
    try {
        const devices = await navigator.hid.requestDevice({
            filters: [
                { vendorId: 5824, productId: 1144 }, // 0x16C0, 0x0478 (Teensy 4.0)
                { vendorId: 5824, productId: 1145 }  // 0x16C0, 0x0479 (Teensy 4.1)
            ]
        });

        if (devices.length > 0) {
            device = devices[0];
            const deviceName = device.productName ||
                (device.productId === 1144 ? "Teensy 4.0" :
                 device.productId === 1145 ? "Teensy 4.1" : "Unknown");
            setStatus(`Device selected: ${deviceName}`);
        } else {
            setStatus("No device selected.");
        }
    } catch (error) {
        console.error(error);
        setStatus("Failed to select device.");
    }
});

// ===== Intel HEX Parsing Logic =====
// Parse a `.hex` into 1KB blocks, skipping addresses below 0 or above some limit.
async function parseHexToBlocks(hexData, blockSize, offset) {
    // Convert the firmwareFile (Uint8Array) into lines for parsing
    // Typically, an Intel HEX file is ASCII text with lines ending in \n or \r\n.
    // We'll do a quick approach: decode to string, then parse line by line.
    // If your .hex is extremely large, a streaming approach might be needed.

    const text = new TextDecoder().decode(hexData);

    const lines = text.split(/\r?\n/);
    const blocks = [];
    let baseAddress = 0;

    function ensureBlock(idx) {
        if (!blocks[idx]) {
            const block = new Uint8Array(blockSize);
            block.fill(0xff);
            blocks[idx] = block;
        }
    }

    for (let lineNum = 0; lineNum < lines.length; lineNum++) {
        let line = lines[lineNum].trim();
        if (!line) continue;
        if (!line.startsWith(':')) {
            throw new Error(`Invalid HEX: missing ':' on line ${lineNum+1}`);
        }

        line = line.slice(1);
        // parse length, address, type, data + checksum
        const length = parseInt(line.slice(0, 2), 16);
        const address = parseInt(line.slice(2, 6), 16);
        const recordType = parseInt(line.slice(6, 8), 16);
        let cursor = 8;
        let calcSum = length + ((address >> 8) & 0xFF) + (address & 0xFF) + recordType;

        if (line.length !== (10 + length*2)) {
            throw new Error(`Line length mismatch on line ${lineNum+1}`);
        }

        switch (recordType) {
            case 0x00: {
                // data record
                const dataBytes = new Uint8Array(length);
                for (let i = 0; i < length; i++) {
                    const byteVal = parseInt(line.slice(cursor, cursor+2), 16);
                    cursor += 2;
                    dataBytes[i] = byteVal;
                    calcSum += byteVal;
                }

                const checkSum = parseInt(line.slice(cursor, cursor+2), 16);
                calcSum = (calcSum & 0xFF);
                const total = (calcSum + checkSum) & 0xFF;
                if (total !== 0) {
                    throw new Error(`Checksum error on line ${lineNum+1}`);
                }

                let addr32 = baseAddress + address;
                addr32 -= offset;  // subtract 0x60000000 for Teensy 4.x

                if (addr32 < 0) {
                    // data is below the offset (e.g. 0x6000_0000)
                    continue;
                }

                // place bytes into blocks
                let dataIndex = 0;
                while (dataIndex < dataBytes.length) {
                    let blockIndex = Math.floor(addr32 / blockSize);
                    ensureBlock(blockIndex);

                    const blockStartAddr = blockIndex * blockSize;
                    const withinBlockOffset = addr32 - blockStartAddr;
                    const spaceInBlock = blockSize - withinBlockOffset;
                    const toCopy = Math.min(spaceInBlock, dataBytes.length - dataIndex);

                    // copy data
                    blocks[blockIndex].set(
                        dataBytes.subarray(dataIndex, dataIndex + toCopy),
                        withinBlockOffset
                    );

                    dataIndex += toCopy;
                    addr32 += toCopy;
                }
                break;
            }
            case 0x01: {
                // End of file
                // parse the checksum
                for (let i = 0; i < length; i++) {
                    const byteVal = parseInt(line.slice(cursor, cursor+2), 16);
                    cursor += 2;
                    calcSum += byteVal;
                }
                const checkSum = parseInt(line.slice(cursor, cursor+2), 16);
                calcSum = (calcSum & 0xFF);
                const total = (calcSum + checkSum) & 0xFF;
                if (total !== 0) {
                    throw new Error(`Checksum error on EOF line ${lineNum+1}`);
                }
                // no more data records, we can stop
                break;
            }
            case 0x02: {
                // Extended Segment Address Record
                // Usually not used by Teensy 4.x, but let's parse properly
                const highAddr = parseInt(line.slice(cursor, cursor+4), 16);
                calcSum += ((highAddr >> 8) & 0xFF) + (highAddr & 0xFF);
                cursor += 4;
                const checkSum = parseInt(line.slice(cursor, cursor+2), 16);
                calcSum = (calcSum & 0xFF);
                if (((calcSum + checkSum) & 0xFF) !== 0) {
                    throw new Error(`Checksum error on line ${lineNum+1}`);
                }
                baseAddress = highAddr << 4; // shift by 4 bits
                break;
            }
            case 0x04: {
                // Extended Linear Address Record
                const upper16 = parseInt(line.slice(cursor, cursor+4), 16);
                calcSum += ((upper16 >> 8) & 0xFF) + (upper16 & 0xFF);
                cursor += 4;
                const checkSum = parseInt(line.slice(cursor, cursor+2), 16);
                calcSum = (calcSum & 0xFF);
                if (((calcSum + checkSum) & 0xFF) !== 0) {
                    throw new Error(`Checksum error on line ${lineNum+1}`);
                }
                baseAddress = upper16 << 16;
                break;
            }
            default: {
                // parse the bytes to keep the checksum logic correct
                for (let i = 0; i < length; i++) {
                    const byteVal = parseInt(line.slice(cursor, cursor+2), 16);
                    cursor += 2;
                    calcSum += byteVal;
                }
                const checkSum = parseInt(line.slice(cursor, cursor+2), 16);
                calcSum = (calcSum & 0xFF);
                if (((calcSum + checkSum) & 0xFF) !== 0) {
                    throw new Error(`Checksum error on line ${lineNum+1}`);
                }
                // ignoring other record types
                break;
            }
        }
    }

    return blocks.filter(b => b); // remove empty slots
}

/**
 * Re-split the 'firmwareFile' (which might be actual .hex ASCII) if it's truly a .hex,
 * or just return [ 1024-chunks ] if it's already a raw binary. 
 * 
 * We'll guess by file extension: if it's .hex => parse with parseHexToBlocks.
 * otherwise => raw.
 */
async function buildFirmwareBlocks(firmwareFile, firmwareFileName) {
    if (firmwareFileName.endsWith('.hex')) {
        // parse Intel HEX => 1KB blocks
        setStatus("Parsing Intel HEX...");
        let blocks = await parseHexToBlocks(firmwareFile, 1024, 0x60000000); 
        // if any blocks are >1KB in length, they've already been truncated above,
        // but we keep each block as a 1KB Uint8Array.
        return blocks;
    } else {
        // treat the firmwareFile as a raw .bin
        setStatus("Treating file as raw 1KB pages");
        const pages = [];
        for (let i = 0; i < firmwareFile.length; i += 1024) {
            const chunk = firmwareFile.slice(i, i + 1024);
            if (chunk.length < 1024) {
                // pad to 1024
                const padded = new Uint8Array(1024);
                padded.fill(0xFF);
                padded.set(chunk, 0);
                pages.push(padded);
            } else {
                pages.push(chunk);
            }
        }
        return pages;
    }
}

// Upload firmware to Teensy
document.getElementById("upload").addEventListener("click", async () => {
    if (!firmwareFile || !device) {
        setStatus("Please load a firmware file and select a device first.");
        return;
    }

    const isTeensy40 = (device.productId === 1144) && firmwareFileName.includes("teensy40");
    const isTeensy41 = (device.productId === 1145) && firmwareFileName.includes("teensy41");

    if (!isTeensy40 && !isTeensy41) {
        setStatus("Firmware file does not match the selected device. Upload canceled.");
        return;
    }

    setStatus("Building firmware blocks...");
    progressElement.value = 0;

    let blocks = [];
    try {
        blocks = await buildFirmwareBlocks(firmwareFile, firmwareFileName);
    } catch (err) {
        console.error(err);
        setStatus(`Failed to parse firmware file: ${err}`);
        return;
    }

    setStatus("Uploading firmware...");
    try {
        await flashFirmware(blocks, device, progress => {
            progressElement.value = progress;
        });
        setStatus("Firmware uploaded successfully!");
    } catch (error) {
        console.error(error);
        setStatus("Failed to upload firmware.");
    }
});

/**
 * Flash Teensy firmware:
 *  - WebHID open
 *  - skip 0xFF blocks except first
 *  - send block as [3 address bytes + 61 zero + 1024 data = 1088 total]
 *  - small delay after each block
 *  - final "magic bytes" 0xFF,0xFF,0xFF
 * @param {Uint8Array[]} firmwarePages 
 * @param {HIDDevice} device 
 * @param {(progress:number)=>void} progressCb 
 */
async function flashFirmware(firmwarePages, device, progressCb) {
    progressCb(0);
    await device.open();

    // each HID report is 1088 bytes for Teensy 4.x:
    //   [0..2]=address bytes, [3..63]=zero padding, [64..1087]=data
    const PAGE_SIZE = 1024;
    const REPORT_SIZE = PAGE_SIZE + 64; //1088
    const report = new Uint8Array(REPORT_SIZE);

    try {
        // Count how many blocks we'll actually send:
        // (skip blank blocks except the first)
        const neededBlocks = firmwarePages.filter(
            (b, i) => i === 0 || !b.every(x => x === 0xFF)
        ).length;

        let processed = 0;
        for (let i = 0; i < firmwarePages.length; i++) {
            const block = firmwarePages[i];
            // skip blank except first
            if (i !== 0 && block.every(x => x === 0xFF)) {
                continue;
            }

            // build the 1088 byte report
            report.fill(0); 
            const addr = i * PAGE_SIZE;

            // address in first 3 bytes
            report[0] = addr & 0xFF;
            report[1] = (addr >> 8) & 0xFF;
            report[2] = (addr >> 16) & 0xFF;
            // copy data at offset 64
            report.set(block, 64);

            // attempt to write w/ minimal retry
            const success = await sendReportWithRetries(device, report, 5);
            if (!success) {
                throw new Error(`Block upload failed at block index=${i}`);
            }

            processed++;
            progressCb(processed / neededBlocks);

            // delay after each block
            await sleep(i === 0 ? 1500 : 5); 
            // 1.5s after the first block (erase), 5ms for subsequent
        }

        // final "magic" = 0xFF,0xFF,0xFF
        report.fill(0);
        report[0] = 0xFF;
        report[1] = 0xFF;
        report[2] = 0xFF;
        await sendReportWithRetries(device, report, 5);

        // optional short wait
        await sleep(100);

    } finally {
        await device.close().catch(() => {});
    }
}

/**
 * Try sending a HID report up to maxRetries times.
 */
async function sendReportWithRetries(device, data, maxRetries=5) {
    for (let attempt = 0; attempt < maxRetries; attempt++) {
        try {
            await device.sendReport(0, data);
            return true;
        } catch (err) {
            console.warn(`sendReport attempt ${attempt+1} failed`, err);
            await sleep(100);
        }
    }
    return false;
}

// ====== Serial Port Logic (unchanged) =====
function processSerialData(data) {
    incompleteLine += data;
    const lines = incompleteLine.split("\n");

    for (let i = 0; i < lines.length - 1; i++) {
        appendOutput(lines[i].trim());
    }

    incompleteLine = lines[lines.length - 1];
}

// Open Serial Port
document.getElementById("open-serial").addEventListener("click", async () => {
    try {
        if (serialPort) {
            setStatus("Serial port already open.");
            return;
        }

        serialPort = await navigator.serial.requestPort();
        await serialPort.open({ baudRate: 115200 });
        setStatus("Serial port opened successfully.");
        appendOutput("Serial port opened.");

        const textDecoder = new TextDecoderStream();
        const readableStreamClosed = serialPort.readable.pipeTo(textDecoder.writable);
        const reader = textDecoder.readable.getReader();

        serialReader = reader;
        while (true) {
            const { value, done } = await reader.read();
            if (done) break;
            processSerialData(value);
        }
    } catch (error) {
        console.error(error);
        setStatus("Failed to open the serial port.");
    }
});

// Close Serial Port
document.getElementById("close-serial").addEventListener("click", async () => {
    if (!serialPort) {
        setStatus("No serial port is open.");
        return;
    }

    try {
        appendOutput("Closing serial port...");
        if (serialReader) {
            await serialReader.cancel();
            serialReader = null;
        }
        await serialPort.close();
        serialPort = null;
        incompleteLine = "";
        setStatus("Serial port closed successfully.");
        appendOutput("Serial port closed.");
    } catch (error) {
        console.error(error);
        setStatus("Failed to close the serial port.");
    }
});
