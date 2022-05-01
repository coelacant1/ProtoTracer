// Audio spectrum display for KB WS35 matrix sets on the Protocontroller V1.1 by https://twitter.com/MeteorTheProto with help from https://twitter.com/mylowhylo

// Audio Spectrum Display
// Copyright 2013 Tony DiCola (tony@tonydicola.com)

// This code is part of the guide at http://learn.adafruit.com/fft-fun-with-fourier-transforms/

#define ARM_MATH_CM4
#include <arm_math.h>

#include <OctoWS2811.h>

const int ledsPerStrip = 346;
DMAMEM int displayMemory[346 * 6];
int drawingMemory[346 * 6];
const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);
int flasher = 0;
unsigned long previousMillis = 0;
const long interval = 200;

void ledFlash() {
  unsigned long currentMillis = millis();
if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    
switch (flasher) {
  case 1:
    leds.setPixel(0,112, 146, 190);
    
    break;
  case 2: 
    leds.setPixel(0,181, 230, 29);
    
    break;
  case 3: 
    leds.setPixel(0,166, 75, 168);
    
    break;
  case 4: 
    leds.setPixel(0,23, 255, 243);
    
    break;
  case 5: 
    leds.setPixel(0,255, 255, 128);
    
    break;
    case 6:
    leds.setPixel(0,252, 3, 98);
    
    break;
    
    }
    if (flasher >= 6) {
      flasher = 1;
    } else{
    flasher++;
    }
  }
}
//led colors
const int colorsR[] = {
255, 255, 255, 255, 255,
225, 225, 212, 170, 128,
85, 43, 0, 0, 0,
0, 0, 0, 0, 0, 
0, 0, 0, 0, 0,
43, 85, 128, 170, 212,
255, 255, 255, 255, 255,
255
};
const int colorsG[] = {
0, 42, 85, 128, 170,
213, 225, 255, 255, 255,
255, 255, 255, 255, 255,
255, 255, 255, 255, 213,
170, 128, 85, 42, 0,
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
255
};
const int colorsB[] = {
0, 0, 0, 0, 0,
0, 0, 0, 0, 0,
0, 0, 0, 42, 85,
128, 170, 213, 225, 255,
255, 255, 255, 255, 255,
255, 255, 255, 255, 255,
255, 255, 255, 255, 255,
255
};
/*
rgb(252, 3, 90) pink
rgb(236, 55, 143)
rgb(204, 92, 182)
rgb(163, 118, 202)
rgb(128, 136, 203)
rgb(112, 146, 190) light blue

rgb(112, 146, 190) light blue
rgb(0, 170, 216)
rgb(0, 194, 213)
rgb(0, 213, 177)
rgb(66, 226, 116)
rgb(181, 230, 29) green

rgb(181, 230, 29) green
rgb(237, 185, 0)
rgb(255, 136, 49)
rgb(255, 91, 98)
rgb(227, 69, 140)
rgb(166, 75, 168) purple

rgb(166, 75, 168) purple
rgb(130, 121, 223)
rgb(41, 161, 255)
rgb(0, 197, 255)
rgb(0, 228, 255)
rgb(23, 255, 243) teal

rgb(23, 255, 243)teal
rgb(88, 255, 218)
rgb(134, 255, 191)
rgb(176, 255, 165)
rgb(216, 255, 143)
rgb(255, 255, 128) yellow

 rgb(255, 255, 128) yellow
rgb(255, 218, 90) 
rgb(255, 179, 68)
rgb(255, 136, 64)
rgb(255, 88, 73)
rgb(252, 3, 90) pink



*/
const int16_t frontHalf[15][25] = {
{-1, 214,191,190,165,164,137,136,107,106,77,76,47,46,21,20,5,4,-1, -1, -1, -1, -1, -1, -1,},
{215, 213,192,189,166,163,138,135,108,105,78,75,48,45,22,19,6,3,0, -1, -1, -1, -1, -1, -1,},
{216, 212,193,188,167,162,139,134,109,104,79,74,49,44,23,18,7,2,-1, -1, -1, -1, -1, -1, -1,},
{217, 211,194,187,168,161,140,133,110,103,80,73,50,43,24,17,8,1,-1, -1, -1, -1, -1, -1, -1,},
{218, 210,195,186,169,160,141,132,111,102,81,72,51,42,25,16,9,-1,-1, -1, -1, -1, -1, -1, -1,},
{219, 209,196,185,170,159,142,131,112,101,82,71,52,41,26,15,10,-1,-1, -1, -1, -1, -1, -1, -1,},
{220, 208,197,184,171,158,143,130,113,100,83,70,53,40,27,14,11,-1,-1, -1, -1, -1, -1, -1, -1,},
{221, 207,198,183,172,157,144,129,114,99,84,69,54,39,28,13,-1,-1,-1, -1, -1, -1, -1, -1, -1,},
{222, 206,199,182,173,156,145,128,115,98,85,68,55,38,29,12,-1,-1,-1, -1, -1, -1, -1, -1, -1,},
{223, 205,200,181,174,155,146,127,116,97,86,67,56,37,30,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1,},
{224, 204,201,180,175,154,147,126,117,96,87,66,57,36,31,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1,},
{-1, 203,202,179,176,153,148,125,118,95,88,65,58,35,32,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1,},
{-1, -1,-1,178,177,152,149,124,119,94,89,64,59,34,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1,},
{-1, -1,-1,-1,-1,151,150,123,120,93,90,63,60,33,-1,-1,-1,-1,-1, -1, -1, -1, -1, -1, -1,},
{-1, -1, -1, -1, -1, -1, -1, 122, 121, 92, 91, 62, 61, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,}
};

const int16_t frontHalfRight[15][25] = {
 {-1, -1, -1, -1, -1, -1, -1, 102, 103, 132, 133, 162, 163, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, 73,  74,  101, 104, 131, 134, 161, 164, 191, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, 46,  47,  72,  75,  100, 105, 130, 135, 160, 165, 190, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, 21,  22,  45,  48,  71,  76,  99,  106, 129, 136, 159, 166, 189, 192, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0,   20,  23,  44,  49,  70,  77,  98,  107, 128, 137, 158, 167, 188, 193, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1,   19,  24,  43,  50,  69,  78,  97,  108, 127, 138, 157, 168, 187, 194, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {2,   18,  25,  42,  51,  68,  79,  96,  109, 126, 139, 156, 169, 186, 195, 212, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {3,   17,  26,  41,  52,  67,  80,  95,  110, 125, 140, 155, 170, 185, 196, 211, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {4,   16,  27,  40,  53,  66,  81,  94,  111, 124, 141, 154, 171, 184, 197, 210, 213, -1, -1, -1, -1, -1, -1, -1, -1},
  {5,   15,  28,  39,  54,  65,  82,  93,  112, 123, 142, 153, 172, 183, 198, 209, 214, -1, -1, -1, -1, -1, -1, -1, -1},
  {6,   14,  29,  38,  55,  64,  83,  92,  113, 122, 143, 152, 173, 182, 199, 208, 215, -1, -1, -1, -1, -1, -1, -1, -1},
  {7,   13,  30,  37,  56,  63,  84,  91,  114, 121, 144, 151, 174, 181, 200, 207, 216, 223, -1, -1, -1, -1, -1, -1, -1},
  {8,   12,  31,  36,  57,  62,  85,  90,  115, 120, 145, 150, 175, 180, 201, 206, 217, 222, -1, -1, -1, -1, -1, -1, -1},
  {9,   11,  32,  35,  58,  61,  86,  89,  116, 119, 146, 149, 176, 179, 202, 205, 218, 221, 224, -1, -1, -1, -1, -1, -1},
  {-1, 10,  33,  34,  59,  60,  87,  88,  117, 118, 147, 148, 177, 178, 203, 204, 219, 220, -1, -1, -1, -1, -1, -1, -1}
};

const int16_t backHalf[19][25] = {
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,116,79,-1,-1,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,153,152,117,115,80,78,43,-1,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,188,187,154,151,118,114,81,77,44,42,-1,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,-1,-1,221,220,189,186,155,150,119,113,82,76,45,41,14,-1,-1,-1,-1},
  {-1,-1,-1,-1,-1,-1,252,251,222,219,190,185,156,149,120,112,83,75,46,40,15,13,-1,-1,-1},
  {-1,-1,-1,308,281,280,253,250,223,218,191,184,157,148,121,111,84,74,47,39,16,12,0,-1,-1},
  {-1,334,309,307,282,279,254,249,224,217,192,183,158,147,122,110,85,73,48,38,17,11,1,-1,-1},
  {335,333,310,306,283,278,255,248,225,216,193,182,159,146,123,109,86,72,49,37,18,10,2,-1,-1},
  {336,332,311,305,284,277,256,247,226,215,194,181,160,145,124,108,87,71,50,36,19,9,3,-1,-1},
  {337,331,312,304,285,276,257,246,227,214,195,180,161,144,125,107,88,70,51,35,20,8,4,-1,-1},
  {338,330,313,303,286,275,258,245,228,213,196,179,162,143,126,106,89,69,52,34,21,7,-1,-1,-1},
  {339,329,314,302,287,274,259,244,229,212,197,178,163,142,127,105,90,68,53,33,22,6,-1,-1,-1},
  {340,328,315,301,288,273,260,243,230,211,198,177,164,141,128,104,91,67,54,32,23,5,-1,-1,-1},
  {341,327,316,300,289,272,261,242,231,210,199,176,165,140,129,103,92,66,55,31,24,-1,-1,-1,-1},
  {342,326,317,299,290,271,262,241,232,209,200,175,166,139,130,102,93,65,56,30,25,-1,-1,-1,-1},
  {343,325,318,298,291,270,263,240,233,208,201,174,167,138,131,101,94,64,57,29,26,-1,-1,-1,-1},
  {344,324,319,297,292,269,264,239,234,207,202,173,168,137,132,100,95,63,58,28,-1,-1,-1,-1,-1},
  {345,323,320,296,293,268,265,238,235,206,203,172,169,136,133,99,96,62,59,27,-1,-1,-1,-1,-1},
  {-1,322,321,295,294,267,266,237,236,205,204,171,170,135,134,98,97,61,60,-1,-1,-1,-1,-1,-1}
};
const int16_t backRightHalf[19][25] = {
  {-1, 23, 24, 50, 51, 78, 79, 108, 109, 140, 141, 174, 175, 210, 211, 247, 248, 284, 285,  -1,  -1,  -1,  -1,  -1,  -1},
  { 0, 22, 25, 49, 52, 77, 80, 107, 110, 139, 142, 173, 176, 209, 212, 246, 249, 283, 286, 318,  -1,  -1,  -1,  -1,  -1},
  { 1, 21, 26, 48, 53, 76, 81, 106, 111, 138, 143, 172, 177, 208, 213, 245, 250, 282, 287, 317,  -1,  -1,  -1,  -1,  -1},
  { 2, 20, 27, 47, 54, 75, 82, 105, 112, 137, 144, 171, 178, 207, 214, 244, 251, 281, 288, 316, 319,  -1,  -1,  -1,  -1},
  { 3, 19, 28, 46, 55, 74, 83, 104, 113, 136, 145, 170, 179, 206, 215, 243, 252, 280, 289, 315, 320,  -1,  -1,  -1,  -1},
  { 4, 18, 29, 45, 56, 73, 84, 103, 114, 135, 146, 169, 180, 205, 216, 242, 253, 279, 290, 314, 321,  -1,  -1,  -1,  -1},
  { 5, 17, 30, 44, 57, 72, 85, 102, 115, 134, 147, 168, 181, 204, 217, 241, 254, 278, 291, 313, 322, 340,  -1,  -1,  -1},
  { 6, 16, 31, 43, 58, 71, 86, 101, 116, 133, 148, 167, 182, 203, 218, 240, 255, 277, 292, 312, 323, 339,  -1,  -1,  -1},
  { 7, 15, 32, 42, 59, 70, 87, 100, 117, 132, 149, 166, 183, 202, 219, 239, 256, 276, 293, 311, 324, 338,  -1,  -1,  -1},
  { 8, 14, 33, 41, 60, 69, 88,  99, 118, 131, 150, 165, 184, 201, 220, 238, 257, 275, 294, 310, 325, 337, 341,  -1,  -1},
  { 9, 13, 34, 40, 61, 68, 89,  98, 119, 130, 151, 164, 185, 200, 221, 237, 258, 274, 295, 309, 326, 336, 342,  -1,  -1},
  {10, 12, 35, 39, 62, 67, 90,  97, 120, 129, 152, 163, 186, 199, 222, 236, 259, 273, 296, 308, 327, 335, 343,  -1,  -1},
  {-1, 11, 36, 38, 63, 66, 91,  96, 121, 128, 153, 162, 187, 198, 223, 235, 260, 272, 297, 307, 328, 334, 344,  -1,  -1},
  {-1, -1, -1, 37, 64, 65, 92,  95, 122, 127, 154, 161, 188, 197, 224, 234, 261, 271, 298, 306, 329, 333, 345,  -1,  -1},
  {-1, -1, -1, -1, -1, -1, 93,  94, 123, 126, 155, 160, 189, 196, 225, 233, 262, 270, 299, 305, 330, 332, -1,  -1,  -1},
  {-1, -1, -1, -1, -1, -1, -1,  -1, 124, 125, 156, 159, 190, 195, 226, 232, 263, 269, 300, 304, 331,  -1, -1,  -1,  -1},
  {-1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1, 157, 158, 191, 194, 227, 231, 264, 268, 301, 303,  -1,  -1, -1,  -1,  -1},
  {-1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1, 192, 193, 228, 230, 265, 267, 302,  -1,  -1,  -1, -1,  -1,  -1},
  {-1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, 229, 266,  -1,-  1,  -1,  -1,  -1, -1,  -1,  -1},
 };

// Accessor function for front array
// Returns -1 if pixel isn't actually on the panel.
int16_t frontPanelToNeopixel(uint16_t x, uint16_t y, bool flipHorizontal, bool flipVertical) {
  if (x > 24 || y > 14){
    return -1;    // Catch out-of-bounds
  }

  if (flipHorizontal && !flipVertical){
    return frontHalf[y][24-x];
  }else if (!flipHorizontal && flipVertical) {
    return frontHalf[14-y][x];
  }else if (flipHorizontal && flipVertical) {
    return frontHalf[14-y][24-x];
  }else {
    return frontHalf[y][x];
  }
}

// Accessor function for front right array
// Returns -1 if pixel isn't actually on the panel.
int16_t frontRightPanelToNeopixel(uint16_t x, uint16_t y, bool flipHorizontal, bool flipVertical) {
  if (x > 24 || y > 14){
    return -1;    // Catch out-of-bounds
  }

  if (flipHorizontal && !flipVertical){
    return frontHalfRight[y][24-x];
  }else if (!flipHorizontal && flipVertical) {
    return frontHalfRight[14-y][x];
  }else if (flipHorizontal && flipVertical) {
    return frontHalfRight[14-y][24-x];
  }else {
    return frontHalfRight[y][x];
  }
}

// Accessor function for rear array
// Returns -1 if pixel isn't actually on the panel.
int16_t rearPanelToNeopixel(uint16_t x, uint16_t y, bool flipHorizontal, bool flipVertical) {
  if (x > 24 || y > 18){ 
    return -1;  // Catch out-of-bounds
  }
  if (flipHorizontal) {
    return backHalf[y][24-x];
  }else if (!flipHorizontal && flipVertical) {
    return backHalf[18-y][x];
  }else if (flipHorizontal && flipVertical) {
    return backHalf[18-y][24-x];
  }else {
    return backHalf[y][x];
  }
}

// Accessor function for rear right array
int16_t rearRightPanelToNeopixel(uint16_t x, uint16_t y, bool flipHorizontal, bool flipVertical) {
  if (x > 24 || y > 18){ 
    return -1;  // Catch out-of-bounds
  }
  if (flipHorizontal) {
    return backRightHalf[y][24-x];
  }else if (!flipHorizontal && flipVertical) {
    return backRightHalf[18-y][x];
  }else if (flipHorizontal && flipVertical) {
    return backRightHalf[18-y][24-x];
  }else {
    return backRightHalf[y][x];
  }
}

int loudness;
int shift = 0;
int reverse = 0;

////////////////////////////////////////////////////////////////////////////////
// CONIFIGURATION 
// These values can be changed to alter the behavior of the spectrum display.
////////////////////////////////////////////////////////////////////////////////

int SAMPLE_RATE_HZ = 9000;             // Sample rate of the audio in hertz.
float SPECTRUM_MIN_DB = 30.0;          // Audio intensity (in decibels) that maps to low LED brightness.
float SPECTRUM_MAX_DB = 90.0;          // Audio intensity (in decibels) that maps to high LED brightness.
int LEDS_ENABLED = 1;                  // Control if the LED's should display the spectrum or not.  1 is true, 0 is false.
                                       // Useful for turning the LED display on and off with commands from the serial port.
const int FFT_SIZE = 256;              // Size of the FFT.  Realistically can only be at most 256 
                                       // without running out of memory for buffers and other state.
const int AUDIO_INPUT_PIN = 22;        // Input ADC pin for audio data.
const int ANALOG_READ_RESOLUTION = 10; // Bits of resolution for the ADC.
const int ANALOG_READ_AVERAGING = 16;  // Number of samples to average with each ADC reading.
const int POWER_LED_PIN = 13;          // Output pin for power LED (pin 13 to use Teensy 3.0's onboard LED).
const int NEO_PIXEL_PIN = 21;           // Output pin for neo pixels. 5
const int NEO_PIXEL_COUNT = 32;         // Number of neo pixels.  You should be able to increase this without
                                       // any other changes to the program.
const int MAX_CHARS = 65;              // Max size of the input command buffer


////////////////////////////////////////////////////////////////////////////////
// INTERNAL STATE
// These shouldn't be modified unless you know what you're doing.
////////////////////////////////////////////////////////////////////////////////

IntervalTimer samplingTimer;
float samples[FFT_SIZE*2];
float magnitudes[FFT_SIZE];
int sampleCounter = 0;


char commandBuffer[MAX_CHARS];
float frequencyWindow[NEO_PIXEL_COUNT+1];
float hues[NEO_PIXEL_COUNT];


////////////////////////////////////////////////////////////////////////////////
// MAIN SKETCH FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

void setup() {
  
  
  // Set up serial port.
  Serial.begin(38400);
  leds.begin();
  leds.show();
  
  
  // Set up ADC and audio input.
  pinMode(AUDIO_INPUT_PIN, INPUT);
  analogReadResolution(ANALOG_READ_RESOLUTION);
  analogReadAveraging(ANALOG_READ_AVERAGING);
  
  // Turn on the power indicator LED.
  pinMode(POWER_LED_PIN, OUTPUT);
  digitalWrite(POWER_LED_PIN, HIGH);
  
  
  // Clear the input command buffer
  memset(commandBuffer, 0, sizeof(commandBuffer));
  
  // Initialize spectrum display
  spectrumSetup();
  
  // Begin sampling audio
  samplingBegin();
}

void loop() {
  // Calculate FFT if a full sample is available.
  if (samplingIsDone()) {
    // Run FFT on sample data.
    arm_cfft_radix4_instance_f32 fft_inst;
    arm_cfft_radix4_init_f32(&fft_inst, FFT_SIZE, 0, 1);
    arm_cfft_radix4_f32(&fft_inst, samples);
    // Calculate magnitude of complex numbers output by the FFT.
    arm_cmplx_mag_f32(samples, magnitudes, FFT_SIZE);
  
    if (LEDS_ENABLED == 1) {
      spectrumLoop();
     ledFlash();
     
      leds.show();
    }
  
    // Restart audio sampling.
    samplingBegin();
    
  }

}


////////////////////////////////////////////////////////////////////////////////
// UTILITY FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// Compute the average magnitude of a target frequency window vs. all other frequencies.
void windowMean(float* magnitudes, int lowBin, int highBin, float* windowMean, float* otherMean) {
    *windowMean = 0;
    *otherMean = 0;
    // Notice the first magnitude bin is skipped because it represents the
    // average power of the signal.
    for (int i = 1; i < FFT_SIZE/2; ++i) {
      if (i >= lowBin && i <= highBin) {
        *windowMean += magnitudes[i];
      }
      else {
        *otherMean += magnitudes[i];
      }
    }
    *windowMean /= (highBin - lowBin) + 1;
    *otherMean /= (FFT_SIZE / 2 - (highBin - lowBin));
}

// Convert a frequency to the appropriate FFT bin it will fall within.
int frequencyToBin(float frequency) {
  float binFrequency = float(SAMPLE_RATE_HZ) / float(FFT_SIZE);
  return int(frequency / binFrequency);
}

////////////////////////////////////////////////////////////////////////////////
// SPECTRUM DISPLAY FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

void spectrumSetup() {
  // Set the frequency window values by evenly dividing the possible frequency
  // spectrum across the number of neo pixels.
  float windowSize = (SAMPLE_RATE_HZ / 2.0) / float(NEO_PIXEL_COUNT);
  for (int i = 0; i < NEO_PIXEL_COUNT+1; ++i) {
    frequencyWindow[i] = i*windowSize;
  }
  // Evenly spread hues across all pixels.
  for (int i = 0; i < NEO_PIXEL_COUNT; ++i) {
    hues[i] = 255*(float(i)/float(NEO_PIXEL_COUNT-1));
  }
}

void spectrumLoop() {
  // Update each LED based on the intensity of the audio 
  // in the associated frequency window.
  float intensity, otherMean;
  for (int i = 0; i < 32; ++i) {
    windowMean(magnitudes, 
               frequencyToBin(frequencyWindow[i]),
               frequencyToBin(frequencyWindow[i+1]),
               &intensity,
               &otherMean);
    // Convert intensity to decibels.
    intensity = 20.0*log10(intensity);
    // Scale the intensity and clamp between 0 and 1.0.
    intensity -= SPECTRUM_MIN_DB;
    intensity = intensity < 0.0 ? 0.0 : intensity;
    intensity /= (SPECTRUM_MAX_DB-SPECTRUM_MIN_DB);
    intensity = intensity > 1.0 ? 1.0 : intensity;
    loudness = intensity * 25;
    shift = i + 5;
    if (i < 15) {
      for(int c = 0; c <25; c++){
       leds.setPixel(frontPanelToNeopixel(c, i, false,true) + 346*6, 0,0,0);
       leds.setPixel(frontRightPanelToNeopixel(c, i, false, false) + 346*7, 0,0,0);
        }
        
      for (int j = 0; j < 25; j++) {
        
          if (loudness - j > 1) {
            leds.setPixel(frontPanelToNeopixel(j, i, false,true) + 346*6, colorsR[i]/25, colorsG[i]/25, colorsB[i]/25);
            leds.setPixel(frontRightPanelToNeopixel(j, i, false, false) + 346*7, colorsR[i]/25, colorsG[i]/25, colorsB[i]/25);
            
          } else if (loudness - j < 1 && loudness - j > 0){
            leds.setPixel(frontPanelToNeopixel(j, i, false,true) + 346*6, colorsR[i] * 4, colorsG[i] * 4, colorsB[i] * 4);
            leds.setPixel(frontRightPanelToNeopixel(j, i, true, false) + 346*7, colorsR[i] * 4, colorsG[i] * 4, colorsB[i] * 4); 
          } else {
            break;
          }
      
        }
           //FastLED.show();
      }
      
     
          
      if (i >= 15){
        for(int c = 0; c <25; c++){
          leds.setPixel(rearPanelToNeopixel(c, i - 15,  false, true) + 346*4, 0,0,0);
          leds.setPixel(rearRightPanelToNeopixel(c, i - 15,  false, false) + 346*5, 0,0,0);
        }
        for (int j = 0; j < 25; j++) {
       
          if (loudness - j > 1) {
            leds.setPixel(rearPanelToNeopixel(j, i - 15,  false, true) + 346*4, colorsR[i]/25, colorsG[i]/25, colorsB[i]/25);
            leds.setPixel(rearRightPanelToNeopixel(j, i - 15,  false, false) + 346*5, colorsR[i]/25, colorsG[i]/25, colorsB[i]/25);
            
          } else if (loudness - j < 1 && loudness - j > 0){
            leds.setPixel(rearPanelToNeopixel(j, i - 15,  false, true) + 346*4, colorsR[i] * 4, colorsG[i] * 4, colorsB[i] * 4);
            leds.setPixel(rearRightPanelToNeopixel(j, i - 15, false, false) + 346*5, colorsR[i] * 4, colorsG[i] * 4, colorsB[i] * 4);
          } else {
            break;
          }
          
      }
    //FastLED.show();
      
    }
    
  shift = 0;
  }
}


////////////////////////////////////////////////////////////////////////////////
// SAMPLING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

void samplingCallback() {
  // Read from the ADC and store the sample data
  samples[sampleCounter] = (float32_t)analogRead(AUDIO_INPUT_PIN);
  // Complex FFT functions require a coefficient for the imaginary part of the input.
  // Since we only have real data, set this coefficient to zero.
  samples[sampleCounter+1] = 0.0;
  // Update sample buffer position and stop after the buffer is filled
  sampleCounter += 2;
  if (sampleCounter >= FFT_SIZE*2) {
    samplingTimer.end();
  }
}

void samplingBegin() {
  // Reset sample buffer position and start callback at necessary rate.
  sampleCounter = 0;
  samplingTimer.begin(samplingCallback, 1000000/SAMPLE_RATE_HZ);
}

boolean samplingIsDone() {
  return sampleCounter >= FFT_SIZE*2;
}
