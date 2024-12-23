/**
 * @file ProtogenProjectTemplate.h
 * @brief Contains the class definition for ProtogenProject, a default project 
 *        template for handling microphone input, boop sensor input, button control,
 *        and various material/animation functionalities in a small-scale 3D 
 *        rendering environment for microcontrollers.
 */

#pragma once

#include "../Templates/Project.h"
#include "../../Animation/KeyFrameTrack.h"
#include "../../Animation/EasyEaseAnimator.h"
#include "../../Assets/Models/OBJ/Background.h"
#include "../../ExternalDevices/InputDevices/Menu/Menu.h"
#include "../../ExternalDevices/Sensors/APDS9960.h"
#include "../../ExternalDevices/Displays/SSD1306.h"
#include "../../ExternalDevices/Sensors/Microphone/MicrophoneFourier_MAX9814.h"
#include "../../ExternalDevices/OutputDevices/FanController.h"

#include "../../Scene/Materials/Utils/MaterialAnimator.h"
#include "../../Scene/Materials/Static/SimpleMaterial.h"
#include "../../Scene/Materials/Animated/FlowNoise.h"
#include "../../Scene/Materials/Animated/RainbowNoise.h"
#include "../../Scene/Materials/Animated/RainbowSpiral.h"
#include "../../Scene/Materials/Animated/HorizontalRainbow.h"
#include "../../Scene/Materials/Animated/SpectrumAnalyzer.h"
#include "../../Scene/Materials/Animated/AudioReactiveGradient.h"
#include "../../Scene/Materials/Animated/Oscilloscope.h"

#include "../../Animation/AnimationTracks/BlinkTrack.h"
#include "../../Utils/Signals/FunctionGenerator.h"
#include "../../ExternalDevices/Sensors/Microphone/Utils/FFTVoiceDetection.h"
#include "../../Scene/Objects/ObjectAlign.h"

#include "../../Utils/Time/TimeStep.h"

#include "../UserConfiguration.h"

/**
 * @class ProtogenProject
 * @brief A default project template that includes functionality for an analog microphone,
 *        APDS9960 boop sensor, and button control. It provides a small-scale 3D rendering
 *        environment and various material animations for prototyping.
 *
 * This class inherits from Project and extends it with additional features:
 * - 2D camera alignment (front/rear) for objects
 * - Material layering and animation
 * - Microphone input (Fourier analysis, voice detection, spectrum analysis, etc.)
 * - Gesture/boop sensor detection
 * - EasyEaseAnimations for param-based transitions
 * - HUD handling and UI control via menu
 */
class ProtogenProject : public Project {
private:
    /**
     * @brief Background object and associated 3D model.
     */
    Background background;

    /**
     * @brief Minimum and maximum bounds for the primary (front) camera view.
     */
    Vector2D camMin = Vector2D(0.0f, 0.0f);     ///< Front camera minimum bounds.
    Vector2D camMax = Vector2D(189.0f, 93.0f); ///< Front camera maximum bounds.

    /**
     * @brief Minimum and maximum bounds for the rear camera view.
     */
    Vector2D camMinRear = Vector2D(214.0f, 5.0f);   ///< Rear camera minimum bounds.
    Vector2D camMaxRear = Vector2D(279.0f, 100.0f); ///< Rear camera maximum bounds.

    /**
     * @brief Flag to indicate if the APDS9960 sensor has detected a "boop".
     */
    bool isBooped = false;

    /**
     * @brief Flag to indicate if the blink parameter has been set.
     */
    bool blinkSet = false;

    /**
     * @brief The size of the camera used for rendering calculations.
     */
    Vector2D cameraSize;

    /**
     * @brief Offsets used for small "wiggle" or motion in the scene.
     */
    float xOffset = 0.0f; ///< X-axis offset.
    float yOffset = 0.0f; ///< Y-axis offset.

    /**
     * @brief Pin assignments and face count.
     */
    uint8_t microphonePin = 0; ///< Pin for the microphone input.
    uint8_t buttonPin    = 0; ///< Pin for the button input.
    uint8_t faceCount    = 10; ///< Total number of faces available (e.g., for UI or animations).

    // --- Materials ---
    FlowNoise flowNoise;               ///< Noise-based animated material.
    RainbowSpiral rainbowSpiral;       ///< Spiral rainbow animated material.
    HorizontalRainbow hRainbow;        ///< Horizontal rainbow animated material.
    SimpleMaterial redMaterial    = SimpleMaterial(RGBColor(255, 0, 0));   ///< Solid red material.
    SimpleMaterial orangeMaterial = SimpleMaterial(RGBColor(255, 165, 0)); ///< Solid orange material.
    SimpleMaterial whiteMaterial  = SimpleMaterial(RGBColor(255, 255, 255)); ///< Solid white material.
    SimpleMaterial greenMaterial  = SimpleMaterial(RGBColor(0, 255, 0));   ///< Solid green material.
    SimpleMaterial blueMaterial   = SimpleMaterial(RGBColor(0, 0, 255));   ///< Solid blue material.
    SimpleMaterial yellowMaterial = SimpleMaterial(RGBColor(255, 255, 0)); ///< Solid yellow material.
    SimpleMaterial purpleMaterial = SimpleMaterial(RGBColor(255, 0, 255)); ///< Solid purple material.
    SimpleMaterial blackMaterial  = SimpleMaterial(RGBColor(0, 0, 0));     ///< Solid black material.
    
    /**
     * @brief Gradient used for color transitions.
     */
    RGBColor gradientSpectrum[2] = {RGBColor(255, 0, 0), RGBColor(255, 0, 0)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);

    /**
     * @brief Material animators for face and background layering.
     */
    MaterialAnimator<20> materialAnimator;   ///< Handles layering of face materials.
    MaterialAnimator<20> backgroundMaterial; ///< Handles layering of background materials.
    
    /**
     * @brief Audio-reactive materials.
     */
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(200, 100), Vector2D(100, 50), true, true); 
    AudioReactiveGradient aRG = AudioReactiveGradient(Vector2D(160, 160), Vector2D(0, 0), true, true); 
    Oscilloscope oSC = Oscilloscope(Vector2D(200, 100), Vector2D(0, 0));

    // --- Project controllers ---
    BlinkTrack<2> blink; ///< Blink track handler.

    /**
     * @brief Object alignment for the front, rear, and an additional alignment object.
     */
    ObjectAlign objA     = ObjectAlign(camMin, camMax, Quaternion());       ///< Alignment for the front camera.
    ObjectAlign objARear = ObjectAlign(camMinRear, camMaxRear, Quaternion()); ///< Alignment for the rear camera.
    ObjectAlign objAOther = ObjectAlign(Vector2D(), Vector2D(), Quaternion()); ///< Generic alignment object.

    /**
     * @brief Function generators for X/Y wiggle movements.
     */
    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 5.3f); 
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 6.7f);

    /**
     * @brief Fan controller for controlling a fan's PWM.
     */
    FanController fanController = FanController(15);

    /**
     * @brief Gesture sensor used for detecting "boops."
     */
    APDS9960 boop;

    /**
     * @brief Voice detection system based on FFT data.
     */
    FFTVoiceDetection<128> voiceDetection;

    /**
     * @brief Facial offset parameters for layering advanced materials (e.g., Spectrum Analyzer).
     */
    float offsetFace    = 0.0f;  ///< Generic face offset.
    float offsetFaceSA  = 0.0f;  ///< Offset for SpectrumAnalyzer face.
    float offsetFaceARG = 0.0f;  ///< Offset for AudioReactiveGradient face.
    float offsetFaceOSC = 0.0f;  ///< Offset for Oscilloscope face.

    uint8_t offsetFaceInd    = 50; ///< Index for generic face offset in EasyEaseAnimator.
    uint8_t offsetFaceIndSA  = 51; ///< Index for SpectrumAnalyzer offset in EasyEaseAnimator.
    uint8_t offsetFaceIndARG = 52; ///< Index for AudioReactiveGradient offset in EasyEaseAnimator.
    uint8_t offsetFaceIndOSC = 53; ///< Index for Oscilloscope offset in EasyEaseAnimator.

    /**
     * @brief Links internal parameters to the EasyEaseAnimator or other controllers.
     */
    void LinkParameters();

    /**
     * @brief Sets the base material for the face material animator.
     * @param material Pointer to the material to set as the base.
     */
    void SetBaseMaterial(Material* material);

    /**
     * @brief Sets up the initial layering of materials for both the face and background.
     */
    void SetMaterialLayers();

    /**
     * @brief Updates any keyframe tracks (e.g., blink track).
     */
    void UpdateKeyFrameTracks();

    /**
     * @brief Updates FFT-based visemes for voice detection and mouth shape animations.
     */
    void UpdateFFTVisemes();

    /**
     * @brief Sets the material color based on menu selection, applying color changes.
     */
    void SetMaterialColor();

    /**
     * @brief A TimeStep object to limit frames (e.g., to 120 FPS).
     */
    TimeStep frameLimiter = TimeStep(120);

protected:
    /**
     * @enum Color
     * @brief Enumeration of different color states for the face material.
     */
    enum Color {
        CBASE,              ///< Base or default color.
        CYELLOW,            ///< Yellow color.
        CORANGE,            ///< Orange color.
        CWHITE,             ///< White color.
        CGREEN,             ///< Green color.
        CPURPLE,            ///< Purple color.
        CRED,               ///< Red color.
        CBLUE,              ///< Blue color.
        CRAINBOW,           ///< Rainbow spiral.
        CRAINBOWNOISE,      ///< Flow noise (rainbow noise).
        CHORIZONTALRAINBOW, ///< Horizontal rainbow effect.
        CBLACK              ///< Black color.
    };

    /**
     * @brief Animator that eases parameter transitions.
     */
    EasyEaseAnimator<60> eEA = EasyEaseAnimator<60>(IEasyEaseAnimator::Overshoot, 1.0f, 0.35f);

    /**
     * @brief Heads-up display (HUD) for the face overlay or additional data.
     */
    HeadsUpDisplay hud = HeadsUpDisplay(Vector2D(0.0f, 0.0f), Vector2D(192.0f, 96.0f));

    /**
     * @brief Links external or user-defined control parameters (pure virtual to be implemented).
     */
    virtual void LinkControlParameters() = 0;

    /**
     * @brief Updates the face's rendered content, reading any user input and applying changes.
     * @param ratio A normalized ratio (0.0f to 1.0f) often used in animation phases.
     */
    void UpdateFace(float ratio);

    /**
     * @brief Sets the camera bounds for the main (front) view.
     * @param min The minimum 2D bounds (bottom-left corner).
     * @param max The maximum 2D bounds (top-right corner).
     */
    void SetCameraMain(Vector2D min, Vector2D max);

    /**
     * @brief Sets the camera bounds for the rear view.
     * @param min The minimum 2D bounds (bottom-left corner).
     * @param max The maximum 2D bounds (top-right corner).
     */
    void SetCameraRear(Vector2D min, Vector2D max);

    /**
     * @brief Computes a transform for aligning a single Object3D within the given bounds.
     * @param min The minimum 2D bounds (bottom-left corner).
     * @param max The maximum 2D bounds (top-right corner).
     * @param obj Pointer to the Object3D to align.
     * @param rotation The rotation angle (in degrees) applied to the object.
     * @param margin Additional margin (border spacing).
     * @return Transform containing position, rotation, and scale to align the object.
     */
    Transform GetAlignmentTransform(Vector2D min, Vector2D max, Object3D* obj, float rotation = 0.0f, float margin = 2.0f);

    /**
     * @brief Computes a transform for aligning multiple Object3D objects within the given bounds.
     * @param min The minimum 2D bounds (bottom-left corner).
     * @param max The maximum 2D bounds (top-right corner).
     * @param objects Pointer to an array of Object3D pointers to align.
     * @param objectCount The number of objects in the array.
     * @param rotation The rotation angle (in degrees) applied to the objects.
     * @param margin Additional margin (border spacing).
     * @return Transform containing position, rotation, and scale for the objects.
     */
    Transform GetAlignmentTransform(Vector2D min, Vector2D max, Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f);

    /**
     * @brief Aligns a single Object3D within the given bounds, applying scaling.
     * @param min The minimum 2D bounds.
     * @param max The maximum 2D bounds.
     * @param obj Pointer to the Object3D to align.
     * @param rotation Rotation to apply.
     * @param margin Margin spacing.
     * @param mirror Whether to mirror the object along the X-axis.
     */
    void AlignObject(Vector2D min, Vector2D max, Object3D* obj, float rotation = 0.0f, float margin = 2.0f, bool mirror = true);

    /**
     * @brief Aligns multiple Object3D objects, applying scaling.
     * @param min The minimum 2D bounds.
     * @param max The maximum 2D bounds.
     * @param objects Array of Object3D pointers.
     * @param objectCount Number of objects.
     * @param rotation Rotation to apply.
     * @param margin Margin spacing.
     * @param mirror Whether to mirror along the X-axis.
     */
    void AlignObjects(Vector2D min, Vector2D max, Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f, bool mirror = true);

    /**
     * @brief Aligns a single Object3D without scaling.
     * @param min The minimum 2D bounds.
     * @param max The maximum 2D bounds.
     * @param obj Pointer to the Object3D to align.
     * @param rotation Rotation to apply.
     * @param margin Margin spacing.
     * @param mirror Whether to mirror the object along the X-axis.
     */
    void AlignObjectNoScale(Vector2D min, Vector2D max, Object3D* obj, float rotation = 0.0f, float margin = 2.0f, bool mirror = true);

    /**
     * @brief Aligns multiple Object3D objects without scaling.
     * @param min The minimum 2D bounds.
     * @param max The maximum 2D bounds.
     * @param objects Array of Object3D pointers.
     * @param objectCount Number of objects.
     * @param rotation Rotation to apply.
     * @param margin Margin spacing.
     * @param mirror Whether to mirror along the X-axis.
     */
    void AlignObjectsNoScale(Vector2D min, Vector2D max, Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f, bool mirror = true);

    /**
     * @brief Aligns a single Object3D to the "face" camera bounds with scaling.
     * @param obj Pointer to the Object3D to align.
     * @param rotation Rotation to apply.
     * @param margin Margin spacing.
     * @param mirror Whether to mirror along the X-axis.
     */
    void AlignObjectFace(Object3D* obj, float rotation = 0.0f, float margin = 2.0f, bool mirror = true);

    /**
     * @brief Aligns multiple Object3D objects to the "face" camera bounds with scaling.
     * @param objects Array of Object3D pointers.
     * @param objectCount Number of objects.
     * @param rotation Rotation to apply.
     * @param margin Margin spacing.
     * @param mirror Whether to mirror along the X-axis.
     */
    void AlignObjectsFace(Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f, bool mirror = true);

    /**
     * @brief Aligns a single Object3D to the "face" camera bounds without scaling.
     * @param obj Pointer to the Object3D to align.
     * @param rotation Rotation to apply.
     * @param margin Margin spacing.
     * @param mirror Whether to mirror along the X-axis.
     */
    void AlignObjectNoScaleFace(Object3D* obj, float rotation = 0.0f, float margin = 2.0f, bool mirror = true);

    /**
     * @brief Aligns multiple Object3D objects to the "face" camera bounds without scaling.
     * @param objects Array of Object3D pointers.
     * @param objectCount Number of objects.
     * @param rotation Rotation to apply.
     * @param margin Margin spacing.
     * @param mirror Whether to mirror along the X-axis.
     */
    void AlignObjectsNoScaleFace(Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f, bool mirror = true);

    /**
     * @brief Aligns a single Object3D to the rear camera bounds with scaling.
     * @param obj Pointer to the Object3D to align.
     * @param rotation Rotation to apply.
     * @param margin Margin spacing.
     * @param mirror Whether to mirror along the X-axis.
     */
    void AlignObjectRear(Object3D* obj, float rotation = 0.0f, float margin = 2.0f, bool mirror = true);

    /**
     * @brief Aligns multiple Object3D objects to the rear camera bounds with scaling.
     * @param objects Array of Object3D pointers.
     * @param objectCount Number of objects.
     * @param rotation Rotation to apply.
     * @param margin Margin spacing.
     * @param mirror Whether to mirror along the X-axis.
     */
    void AlignObjectsRear(Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f, bool mirror = true);

    /**
     * @brief Aligns a single Object3D to the rear camera bounds without scaling.
     * @param obj Pointer to the Object3D to align.
     * @param rotation Rotation to apply.
     * @param margin Margin spacing.
     * @param mirror Whether to mirror along the X-axis.
     */
    void AlignObjectNoScaleRear(Object3D* obj, float rotation = 0.0f, float margin = 2.0f, bool mirror = true);

    /**
     * @brief Aligns multiple Object3D objects to the rear camera bounds without scaling.
     * @param objects Array of Object3D pointers.
     * @param objectCount Number of objects.
     * @param rotation Rotation to apply.
     * @param margin Margin spacing.
     * @param mirror Whether to mirror along the X-axis.
     */
    void AlignObjectsNoScaleRear(Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f, bool mirror = true);

    /**
     * @brief Gets the generic ObjectAlign instance.
     * @return A pointer to the ObjectAlign handling custom alignment.
     */
    ObjectAlign* GetObjectAlign();

    /**
     * @brief Gets the ObjectAlign instance for the face camera.
     * @return A pointer to the ObjectAlign used for face alignment.
     */
    ObjectAlign* GetObjectAlignFace();

    /**
     * @brief Gets the ObjectAlign instance for the rear camera.
     * @return A pointer to the ObjectAlign used for rear alignment.
     */
    ObjectAlign* GetObjectAlignRear();

    /**
     * @brief Computes the face scaling based on a user-defined face size.
     * @return A float representing the scale factor to apply for the face.
     */
    float GetFaceScale();

    /**
     * @brief Adds a parameter to the EasyEaseAnimator for interpolation.
     * @param index The parameter index within the animator.
     * @param parameter Pointer to the float parameter to animate.
     * @param transitionFrames How many frames the transition should take.
     * @param interpolationMethod The interpolation method (overshoot, linear, etc.).
     * @param invertDirection Whether to invert the animation (1.0f to 0.0f).
     */
    void AddParameter(uint8_t index, float* parameter, uint16_t transitionFrames, 
                      IEasyEaseAnimator::InterpolationMethod interpolationMethod = IEasyEaseAnimator::InterpolationMethod::Overshoot, 
                      bool invertDirection = false);

    /**
     * @brief Adds a viseme parameter to the animator (for mouth shapes).
     * @param visemeName The mouth shape (e.g., Viseme::EE, Viseme::AH, etc.).
     * @param parameter Pointer to the float parameter controlling that viseme.
     */
    void AddViseme(Viseme::MouthShape visemeName, float* parameter);

    /**
     * @brief Adds a float parameter to the blink track for controlling blinking.
     * @param blinkParameter Pointer to the float controlling blinking.
     */
    void AddBlinkParameter(float* blinkParameter);

    /**
     * @brief Adds a frame target to a previously added parameter.
     * @param ProjectIndex The index for the parameter.
     * @param target The target value for that parameter.
     */
    void AddParameterFrame(uint16_t ProjectIndex, float target);

    /**
     * @brief Adds a new material to the face's MaterialAnimator with given parameters.
     * @param method The blend method (e.g., Material::Add, Material::Replace).
     * @param material Pointer to the material to add.
     * @param frames How many frames the transition will take.
     * @param minOpacity The minimum opacity.
     * @param maxOpacity The maximum opacity.
     */
    void AddMaterial(Material::Method method, Material* material, uint16_t frames = 20, 
                     float minOpacity = 0.0f, float maxOpacity = 1.0f);

    /**
     * @brief Adds a new material frame to the face's MaterialAnimator from a color enum.
     * @param color The color enum to switch to.
     * @param opacity The target opacity for that color material.
     */
    void AddMaterialFrame(Color color, float opacity = 0.8f);

    /**
     * @brief Adds a new material frame to the face's MaterialAnimator from a Material reference.
     * @param material A reference to the material to add.
     * @param opacity The target opacity.
     */
    void AddMaterialFrame(Material& material, float opacity = 1.0f);

    /**
     * @brief Adds a new material to the background's MaterialAnimator with given parameters.
     * @param method The blend method.
     * @param material The material to add.
     * @param frames Transition frames.
     * @param minOpacity Minimum opacity.
     * @param maxOpacity Maximum opacity.
     */
    void AddBackgroundMaterial(Material::Method method, Material* material, uint16_t frames = 20, 
                               float minOpacity = 0.0f, float maxOpacity = 1.0f);

    /**
     * @brief Adds a material frame to the background from a color enum.
     * @param color The color enum to switch to.
     * @param opacity The target opacity.
     */
    void AddBackgroundMaterialFrame(Color color, float opacity = 0.8f);

    /**
     * @brief Adds a material frame to the background from a Material reference.
     * @param material The material to add.
     * @param opacity The target opacity.
     */
    void AddBackgroundMaterialFrame(Material& material, float opacity = 1.0f);

    /**
     * @brief Enables the Spectrum Analyzer on the face, updating offsets and calling callbacks.
     */
    void SpectrumAnalyzerFace();

    /**
     * @brief Enables the Audio Reactive Gradient on the face, updating offsets and calling callbacks.
     */
    void AudioReactiveGradientFace();

    /**
     * @brief Enables the Oscilloscope on the face, updating offsets and calling callbacks.
     */
    void OscilloscopeFace();

    /**
     * @brief Hides the face by setting its offset parameter.
     */
    void HideFace();

    /**
     * @brief Disables blinking (pauses and resets the blink track).
     */
    void DisableBlinking();

    /**
     * @brief Enables blinking (resets and plays the blink track).
     */
    void EnableBlinking();

    /**
     * @brief Checks if the sensor has detected a boop.
     * @return True if booped, false otherwise.
     */
    bool IsBooped();

    /**
     * @brief Computes and returns a Vector3D offset for a "wiggle" effect using function generators.
     * @return The updated wiggle offset in 3D.
     */
    Vector3D GetWiggleOffset();

    /**
     * @brief Sets the overall wiggle speed for both X and Y function generators.
     * @param multiplier The speed multiplier.
     */
    void SetWiggleSpeed(float multiplier);

    /**
     * @brief Adjusts the menu's wiggle speed along X, Y, and rotation.
     * @param multiplierX Speed multiplier for X-axis.
     * @param multiplierY Speed multiplier for Y-axis.
     * @param multiplierR Speed multiplier for rotation.
     */
    void SetMenuWiggleSpeed(float multiplierX, float multiplierY, float multiplierR);

    /**
     * @brief Sets the menu's position offset.
     * @param offset The 2D offset to apply.
     */
    void SetMenuOffset(Vector2D offset);

    /**
     * @brief Sets the menu's size.
     * @param size The new 2D size for the menu.
     */
    void SetMenuSize(Vector2D size);

    /**
     * @brief Retrieves the current face material animator.
     * @return Pointer to the Material used for the face.
     */
    Material* GetFaceMaterial();

    /**
     * @brief Retrieves the current background material animator.
     * @return Pointer to the Material used for the background.
     */
    Material* GetBackgroundMaterial();

public:
    /**
     * @brief Constructs a ProtogenProject instance.
     * @param cameras Pointer to the project's CameraManager.
     * @param controller Pointer to the main Controller.
     * @param numObjects Number of objects (including extra for internal usage).
     * @param camMin The minimum 2D bounds for the main camera.
     * @param camMax The maximum 2D bounds for the main camera.
     * @param microphonePin The pin used for the microphone.
     * @param buttonPin The pin used for the button.
     * @param faceCount The number of faces for possible UI or animations.
     */
    ProtogenProject(CameraManager* cameras, Controller* controller, uint8_t numObjects, 
                    Vector2D camMin, Vector2D camMax, uint8_t microphonePin, 
                    uint8_t buttonPin, uint8_t faceCount);

    /**
     * @brief Initializes the ProtogenProject, setting up sensors, menus, and hardware.
     */
    void Initialize() override;

    /**
     * @brief Callback invoked when the Spectrum Analyzer face is enabled/updated.
     * 
     * This method is pure virtual and must be implemented by the derived class
     * to define custom behavior upon enabling or updating the Spectrum Analyzer face.
     */
    virtual void SpectrumAnalyzerCallback() = 0;

    /**
     * @brief Callback invoked when the Audio Reactive Gradient face is enabled/updated.
     * 
     * This method is pure virtual and must be implemented by the derived class
     * to define custom behavior upon enabling or updating the Audio Reactive Gradient face.
     */
    virtual void AudioReactiveGradientCallback() = 0;

    /**
     * @brief Callback invoked when the Oscilloscope face is enabled/updated.
     * 
     * This method is pure virtual and must be implemented by the derived class
     * to define custom behavior upon enabling or updating the Oscilloscope face.
     */
    virtual void OscilloscopeCallback() = 0;
};
