#include "TextEngine.h"

template<uint8_t lineCount, uint8_t characterWidth>
TextEngine<lineCount, characterWidth>::TextEngine(bool isEfficient) {
    this->isEfficient = isEfficient;

    ClearText(); //init to spaces
}

template<uint8_t lineCount, uint8_t characterWidth>
TextEngine<lineCount, characterWidth>::TextEngine(Vector2D size, Vector2D position, uint16_t blinkTime, bool isEfficient) {
    this->size = size;
    this->positionOffset = position;
    this->blinkTime = blinkTime;
    this->isEfficient = isEfficient;

    ClearText(); //init to spaces
}

template<uint8_t lineCount, uint8_t characterWidth>
void TextEngine<lineCount, characterWidth>::SetMaterial(Material* material) {
    this->material = material;
}

template<uint8_t lineCount, uint8_t characterWidth>
void TextEngine<lineCount, characterWidth>::SetSize(Vector2D size) {
    this->size = size;
}

template<uint8_t lineCount, uint8_t characterWidth>
void TextEngine<lineCount, characterWidth>::SetPositionOffset(Vector2D positionOffset) {
    this->positionOffset = positionOffset;
}

template<uint8_t lineCount, uint8_t characterWidth>
void TextEngine<lineCount, characterWidth>::SetRotationOffset(Vector2D rotationOffset) {
    this->rotationOffset = rotationOffset;
}

template<uint8_t lineCount, uint8_t characterWidth>
void TextEngine<lineCount, characterWidth>::SetRotationAngle(float rotationAngle) {
    this->rotationAngle = rotationAngle;
}

template<uint8_t lineCount, uint8_t characterWidth>
void TextEngine<lineCount, characterWidth>::SetBlinkTime(uint16_t blinkTime) {
    this->blinkTime = blinkTime;
}

template<uint8_t lineCount, uint8_t characterWidth>
void TextEngine<lineCount, characterWidth>::SetText(uint8_t line, String value, bool centerText) {
    uint8_t length = value.length();
    int spacing = centerText ? (length - characterWidth) / 2 : 0;

    if (line > lineCount || spacing < 0 || length > characterWidth) return; //break when outside of bounds

    for (int i = spacing; i < length + spacing; i++) {
        lines[line][i] = value[i - spacing];
    }
}

template<uint8_t lineCount, uint8_t characterWidth>
void TextEngine<lineCount, characterWidth>::ClearText() {
    for (uint8_t i = 0; i < lineCount; i++) {
        for (uint8_t j = 0; j < characterWidth; j++) {
            lines[i][j] = ' ';
        }
    }
}

template<uint8_t lineCount, uint8_t characterWidth>
RGBColor TextEngine<lineCount, characterWidth>::GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) {
    if(rotationAngle != 0 && !isEfficient){
        position = position - Vector3D(rotationOffset.X, rotationOffset.Y, 0);

        Quaternion temp = Rotation(EulerAngles(Vector3D(0, 0, rotationAngle), EulerConstants::EulerOrderXYZS)).GetQuaternion();
        
        position = temp.RotateVector(position);// rotate

        position = position + Vector3D(rotationOffset.X, rotationOffset.Y, 0);
    }
    else{
        Vector2D tempPos = position;

        if(Mathematics::IsClose(int(rotationAngle) % 360, 90.0f, 45.0f)){
            position.X = tempPos.Y;
            position.Y = -tempPos.X;
        }
        else if (Mathematics::IsClose(int(rotationAngle) % 360, 180.0f, 45.0f)){
            position.X = -tempPos.X;
            position.Y = -tempPos.Y;
        }
        else if (Mathematics::IsClose(int(rotationAngle) % 360, 270.0f, 45.0f)){
            position.X = -tempPos.Y;
            position.Y = tempPos.X;
        }
    }

    position = position - Vector3D(positionOffset.X, positionOffset.Y, 0);//offset position
    
    int x = floorf(Mathematics::Map(position.X, 0.0f, size.X, characterWidth * 10.0f, 0.0f));
    int y = floorf(Mathematics::Map(position.Y, 0.0f, size.Y, lineCount * 10.0f, 0.0f));

    if(x < 0 || x >= characterWidth * 10 || y < 0 || y >= lineCount * 10) return black;

    //bit 
    uint8_t charXBit = 9 - (x % 10);
    uint8_t charYBit = y % 10;

    char searchChar = lines[y / 10][x / 10];
    bool blink = millis() % (blinkTime * 2) > blinkTime;

    if(charYBit == 0 || charYBit == 9 || charXBit == 0 || charXBit == 9){//margin
        if (searchChar > 90 && blink) {
            return material->GetRGB(position, normal, uvw).HueShift(180);
        }
        else return black;
    }
    else{
        uint8_t yCharacter = Characters::GetCharacter(searchChar)[charYBit - 1];//get character

        bool xBit = 1 & (yCharacter >> (charXBit - 1));
        
        if (searchChar > 90 && blink){
            return xBit ? black : material->GetRGB(position, normal, uvw).HueShift(180);
        }
        else if (searchChar > 90){
            return xBit ? material->GetRGB(position, normal, uvw).HueShift(180) : black;
        }
        else {
            return xBit ? material->GetRGB(position, normal, uvw) : black;
        }
    }
}
