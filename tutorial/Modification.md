\page Modification Modifying ProtoTracer

## Modifying and Customizing ProtoTracer

ProtoTracer is designed to be flexible and extensible, allowing you to customize its features for your specific projects. Whether you’re adding new functionality, tweaking existing settings, or converting assets for use, this guide will provide an overview and link to more in-depth pages on key customization topics.

---

## Customization Options

### 1. **Convert GIF to AnimatedMaterial**
ProtoTracer supports animated materials derived from GIFs, enabling dynamic visuals on your Protogen display. Follow the detailed guide to learn how to:
- Convert a GIF into the required format.
- Adjust frame rates and resolutions for optimal performance.
- Integrate the material into your project.

**Read more about GIF to AnimatedMaterial Conversion**:
\subpage GIFConverter

---

### 2. **Convert OBJ Files to ProtoTracer 3D Format**
Bring your 3D models to life by converting standard `.OBJ` files into a format ProtoTracer can use. This guide covers:
- Preparing `.OBJ` files for conversion.
- Using the provided tools for the conversion process.
- Optimizing models for real-time performance on ProtoTracer.

**Read more about OBJ to ProtoTracer Conversion**:
\subpage OBJConverter

---

### 3. **Convert FBX Files to ProtoTracer 3D Format**
FBX files are widely used for 3D models and animations. This guide will help you:
- Import and convert `.FBX` files to the ProtoTracer format.
- Retain blendshapes in the process.
- Troubleshoot common issues in the conversion process.

**Read more about FBX to ProtoTracer Conversion**:
\subpage FBXConverter

---

### 4. **Voice Formant Calibration**
The FFT voice detection system in ProtoTracer uses formant frequencies to detect visemes (mouth shapes). This guide will show you how to:
- Use a spectrum analyzer to identify formant frequencies.
- Calibrate the formant frequency map for accurate viseme detection.
- Adjust thresholds and tuning parameters.

**Read more about Voice Formant Calibration**:
\subpage VoiceCalibration

---

## Advanced Customizations

### Modify Core Functionality
- Explore the codebase to understand ProtoTracer’s modular structure.
- Extend or override classes in key modules such as rendering, physics, or animation.
- Leverage the `platformio.ini` file for custom build configurations.

### Extend Project Templates
- Use the provided templates under Examples to extend functionality.

### Create Custom Scenes and Materials
- Use the provided `Scene` class to set up new environments.
- Create and integrate custom materials, including static and animated textures.

---

## Contributing to ProtoTracer
If you’ve made a valuable customization or tool, consider sharing it by:
- Submitting a pull request to the GitHub repository.
- Adding documentation for your feature or modification.

---

## Feedback and Support
For questions, feature requests, or troubleshooting, feel free to:
- Open an issue on the [GitHub Repository](https://github.com/coelacant1/ProtoTracer).
- Join the community discussions in our [Discord server](https://discord.gg/YwaWnhJ).
