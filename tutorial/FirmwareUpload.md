# Firmware Upload Online {#FirmwareUpload}

@htmlonly
<h1>ProtoTracer Teensy 4.0/4.1 Firmware Uploader</h1>
<div>Select the firmware file you would like to upload to your Teensy 4.0 or 4.1, press the reset button on the Teensy so the light turns red, select the device, and upload your firmware.</div>
<div style="padding-top: 5px;">Latest Build is a work-in-progress - dealing with CORS issue. Please download the repository from here: <a href="https://github.com/coelacant1/ProtoTracer/releases/download/v1.14/firmware_build_1.14.zip">ProtoTracer Build v1.14</a></div>
<div id="uploader">
    <h1>Firmware Uploader</h1>
    <label>
        <input type="radio" name="firmware-source" value="latest-builds" checked />
        Latest Builds
    </label>
    <label>
        <input type="radio" name="firmware-source" value="local-file" />
        Local File Upload
    </label>

    <div id="latest-builds">
        <select id="firmware-select">
            <option value="">Select firmware...</option>
        </select>
    </div>

    <div id="local-file" style="display: none;">
        <input type="file" id="firmware" accept=".hex" />
    </div>

    <button id="select-device">Select Device</button>
    <button id="upload" disabled>Upload Firmware</button>
    <progress id="progress" value="0" max="1"></progress>
    <p id="status"></p>
</div>

<div id="serial">
    <button id="open-serial">Open Serial Port</button>
    <button id="close-serial">Close Serial Port</button>
    <textarea id="serial-output" readonly style="width: 100%; height: 200px;"></textarea>
</div>
<script src="prototracer-firmware-uploader.js"></script>
@endhtmlonly
