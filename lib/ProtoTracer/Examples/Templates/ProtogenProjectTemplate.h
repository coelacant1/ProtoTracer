#pragma once

#include "../Templates/Project.h"
#include "../../Animation/KeyFrameTrack.h"
#include "../../Animation/EasyEaseAnimator.h"
#include "../../Assets/Models/OBJ/Background.h"
#include "../../ExternalDevices/InputDevices/Menu/Menu.h"
#include "../../ExternalDevices/Sensors/APDS9960.h"
#include "../../ExternalDevices/Displays/SSD1306.h"
#include "../../ExternalDevices/Sensors/Microphone/MicrophoneFourier_MAX9814.h"
//#include "../Sensors/MicrophoneFourier_DMA.h"
#include "../../ExternalDevices/OutputDevices/FanController.h"

#include "../../Scene/Materials/Utils/MaterialAnimator.h"
#include "../../Scene/Materials/Static/SimpleMaterial.h"
#include "../../Scene/Materials/Animated/FlowNoise.h"
#include "../../Scene/Materials/Animated/RainbowNoise.h"
#include "../../Scene/Materials/Animated/RainbowSpiral.h"
#include "../../Scene/Materials/Animated/SpectrumAnalyzer.h"
#include "../../Scene/Materials/Animated/AudioReactiveGradient.h"
#include "../../Scene/Materials/Animated/Oscilloscope.h"

#include "../../Animation/AnimationTracks/BlinkTrack.h"
#include "../../Utils/Signals/FunctionGenerator.h"
#include "../../ExternalDevices/Sensors/Microphone/Utils/FFTVoiceDetection.h"
#include "../../Scene/Objects/ObjectAlign.h"

#include "../UserConfiguration.h"

//Default Project base for Analog microphone, APDS9960 boop sensor, and button control
class ProtogenProject : public Project {
private:
    Background background;

    Vector2D camMin = Vector2D(0.0f, 0.0f);
    Vector2D camMax = Vector2D(189.0f, 93.0f);

    Vector2D camMinRear = Vector2D(214.0f, 5.0f);
    Vector2D camMaxRear = Vector2D(279.0f, 100.0f);
    
    bool isBooped = false;
    bool blinkSet = false;

    Vector2D cameraSize;
    float xOffset = 0.0f;
    float yOffset = 0.0f;

    uint8_t microphonePin = 0;
    uint8_t buttonPin = 0;
    uint8_t faceCount = 10;
    
    //Materials
    FlowNoise flowNoise;
    RainbowSpiral rainbowSpiral;
    SimpleMaterial redMaterial = SimpleMaterial(RGBColor(255, 0, 0));
    SimpleMaterial orangeMaterial = SimpleMaterial(RGBColor(255, 165, 0));
    SimpleMaterial whiteMaterial = SimpleMaterial(RGBColor(255, 255, 255));
    SimpleMaterial greenMaterial = SimpleMaterial(RGBColor(0, 255, 0));
    SimpleMaterial blueMaterial = SimpleMaterial(RGBColor(0, 0, 255));
    SimpleMaterial yellowMaterial = SimpleMaterial(RGBColor(255, 255, 0));
    SimpleMaterial purpleMaterial = SimpleMaterial(RGBColor(130, 0, 255));
    SimpleMaterial roseMaterial = SimpleMaterial(RGBColor(255, 150, 255));
    SimpleMaterial customMaterial = SimpleMaterial(RGBColor(100, 100, 100)); 

    RGBColor gradientSpectrum[2] = {RGBColor(255, 0, 0), RGBColor(255, 0, 0)};
    GradientMaterial<2> gradientMat = GradientMaterial<2>(gradientSpectrum, 350.0f, false);
    
    MaterialAnimator<15> materialAnimator;
    MaterialAnimator<10> backgroundMaterial;
    
    SpectrumAnalyzer sA = SpectrumAnalyzer(Vector2D(200, 100), Vector2D(100, 50), true, true); 
    AudioReactiveGradient aRG = AudioReactiveGradient(Vector2D(160, 160), Vector2D(0, 0), true, true); 
    Oscilloscope oSC = Oscilloscope(Vector2D(200, 100), Vector2D(0, 0));

    //Project controllers
    BlinkTrack<1> blink;
    ObjectAlign objA = ObjectAlign(camMin, camMax, Quaternion());
    ObjectAlign objARear = ObjectAlign(camMinRear, camMaxRear, Quaternion());
    ObjectAlign objAOther = ObjectAlign(Vector2D(), Vector2D(), Quaternion());

    FunctionGenerator fGenMatXMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 5.3f);
    FunctionGenerator fGenMatYMove = FunctionGenerator(FunctionGenerator::Sine, -2.0f, 2.0f, 6.7f);

    FanController fanController = FanController(15);
    APDS9960 boop;
    FFTVoiceDetection<128> voiceDetection;
    
    float offsetFace = 0.0f;
    float offsetFaceSA = 0.0f;
    float offsetFaceARG = 0.0f;
    float offsetFaceOSC = 0.0f;
    uint8_t offsetFaceInd = 50;
    uint8_t offsetFaceIndSA = 51;
    uint8_t offsetFaceIndARG = 52;
    uint8_t offsetFaceIndOSC = 53;

    void LinkParameters();
    void SetBaseMaterial(Material* material);
    void SetMaterialLayers();
    void UpdateKeyFrameTracks();
    void UpdateFFTVisemes();
    void SetMaterialColor();

protected:
    enum Color{
        CBASE,
        CYELLOW,
        CORANGE,
        CWHITE, 
        CGREEN,
        CPURPLE,
        CRED,
        CBLUE,
        CPINK,
        CRAINBOW,
        CRAINBOWNOISE
    };
    
    EasyEaseAnimator<60> eEA = EasyEaseAnimator<60>(IEasyEaseAnimator::Overshoot, 1.0f, 0.35f);
    HeadsUpDisplay hud = HeadsUpDisplay(Vector2D(0.0f, 0.0f), Vector2D(192.0f, 96.0f));

    virtual void LinkControlParameters() = 0;
    void UpdateFace(float ratio);

    void SetCameraMain(Vector2D min, Vector2D max);
    void SetCameraRear(Vector2D min, Vector2D max);

    Transform GetAlignmentTransform(Vector2D min, Vector2D max, Object3D* obj, float rotation = 0.0f, float margin = 2.0f);
    Transform GetAlignmentTransform(Vector2D min, Vector2D max, Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f);
    void AlignObject(Vector2D min, Vector2D max, Object3D* obj, float rotation = 0.0f, float margin = 2.0f);
    void AlignObjects(Vector2D min, Vector2D max, Object3D** obj, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f);
    void AlignObjectNoScale(Vector2D min, Vector2D max, Object3D* obj, float rotation = 0.0f, float margin = 2.0f);
    void AlignObjectsNoScale(Vector2D min, Vector2D max, Object3D** obj, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f);

    void AlignObjectFace(Object3D* obj, float rotation = 0.0f, float margin = 2.0f);
    void AlignObjectsFace(Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f);
    void AlignObjectNoScaleFace(Object3D* obj, float rotation = 0.0f, float margin = 2.0f);
    void AlignObjectsNoScaleFace(Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f);
    void AlignObjectRear(Object3D* obj, float rotation = 0.0f, float margin = 2.0f);
    void AlignObjectsRear(Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f);
    void AlignObjectNoScaleRear(Object3D* obj, float rotation = 0.0f, float margin = 2.0f);
    void AlignObjectsNoScaleRear(Object3D** objects, uint8_t objectCount, float rotation = 0.0f, float margin = 2.0f);

    float GetFaceScale();

    void AddParameter(uint8_t index, float* parameter, uint8_t transitionFrames, IEasyEaseAnimator::InterpolationMethod interpolationMethod = IEasyEaseAnimator::InterpolationMethod::Overshoot, bool invertDirection = false);
    void AddViseme(Viseme::MouthShape visemeName, float* parameter);
    void AddBlinkParameter(float* blinkParameter);
    void AddParameterFrame(uint16_t ProjectIndex, float target);
    void AddMaterial(Material::Method method, Material* material, uint16_t frames = 20, float minOpacity = 0.0f, float maxOpacity = 1.0f);
    void AddMaterialFrame(Color color);
    void AddMaterialFrame(Material& material, float opacity = 1.0f);
    void AddBackgroundMaterial(Material::Method method, Material* material, uint16_t frames = 20, float minOpacity = 0.0f, float maxOpacity = 1.0f);
    void AddBackgroundMaterialFrame(Material& material, float opacity = 1.0f);
    void SetCustomColor(RGBColor color);

    void SpectrumAnalyzerFace();
    void AudioReactiveGradientFace();
    void OscilloscopeFace();
    void HideFace();
    void DisableBlinking();
    void EnableBlinking();
    bool IsBooped();

    Vector3D GetWiggleOffset();
    void SetWiggleSpeed(float multiplier);
    void SetMenuWiggleSpeed(float multiplierX, float multiplierY, float multiplierR);
    void SetMenuOffset(Vector2D offset);
    void SetMenuSize(Vector2D size);

    Material* GetFaceMaterial();
    Material* GetBackgroundMaterial();

public:
    ProtogenProject(CameraManager* cameras, Controller* controller, uint8_t numObjects, Vector2D camMin, Vector2D camMax, uint8_t microphonePin, uint8_t buttonPin, uint8_t faceCount);

    void Initialize() override;

};
