#pragma once

#include "Material.h"
#include "..\Render\Pixel.h"
#include "..\Math\Vector2D.h"

//Converts gif to RGB XY pixel matrix
class BMP : public Material {
private:
  Vector2D imageSize;
  Vector2D offsetPosition;
  Vector2D shiftPosition;
  const uint8_t* file;
  uint8_t padding;
  uint8_t glitch;
  int xPixels;
  int yPixels;
  long imagePixels;
  const int displayWidth = 320;

  RGBColor ConvertRGB565(uint16_t color){

    Serial.println("Not done yet");

    return RGBColor();
  }
  
public:
  BMP(Vector2D imageSize, Vector2D offsetPosition, const uint8_t* bmpArray, uint8_t padding) : file(bmpArray){
    //this->file = bmpArray;
    Serial.println("READING BMP FILE");
    this->imageSize = imageSize;
    this->offsetPosition = offsetPosition;
    this->padding = padding;
    this->glitch = 0;

    xPixels = *(int*)&file[18];
    yPixels = *(int*)&file[22];

    imagePixels = 3 * xPixels * yPixels;
    /*
    int xPos = 0;
    int yPos = 0;
    
    for(int i = 54; i < imagePixels + 54; i += 3){
      //pixels[i - 54].X = Mathematics::Map(xPos, 0, xPixels, 0 + offsetPosition.X, imageSize.X + 1 + offsetPosition.X);
      //pixels[i - 54].Y = Mathematics::Map(yPos, 0, yPixels, 0 + offsetPosition.Y, imageSize.Y + 1 + offsetPosition.Y);
      //pixels[i - 54].Color = RGBColor(file[i + 2], file[i + 1], file[i]);

      Serial.print(file[i + 2]);
      Serial.print(" ");
      Serial.print(file[i + 1]);
      Serial.print(" ");
      Serial.print(file[i]);
      Serial.print(" ");
      Serial.print(xPos);
      Serial.print(" ");
      Serial.println(yPos);
      
      xPos++;
      if(xPos >= xPixels){
        xPos = 0;
        yPos++;
      }
    }
    */
  }

  void ShiftPosition(Vector2D shiftPosition){
    this->shiftPosition = this->shiftPosition + shiftPosition;
  }

  void ResetShift(){
    shiftPosition = Vector2D();
  }

  void Glitch(uint8_t value){
    this->glitch = value;
  }

  //maps XY position to an rgb value on the 
  RGBColor GetRGB(Vector2D xyPosition){
    //convert xyposition to integer position on image plane
    int xPosition, yPosition;

    xPosition = Mathematics::Map(xyPosition.X, offsetPosition.X + shiftPosition.X, imageSize.X + 1 + offsetPosition.X + shiftPosition.X, 0, xPixels);//scale to fit image size
    yPosition = Mathematics::Map(xyPosition.Y, offsetPosition.Y + shiftPosition.Y, imageSize.Y + 1 + offsetPosition.Y + shiftPosition.Y, 0, yPixels);
    /*
    Serial.print(xyPosition.ToString());
    Serial.print("\t");
    Serial.print(xPosition);
    Serial.print("\t");
    Serial.print(yPosition);
    */
    //map xy to to imagesize with offset position
    if (xPosition < 0 || xPosition > xPixels - 1) return RGBColor(0, 0, 0);
    if (yPosition < 0 || yPosition > yPixels - 1) return RGBColor(0, 0, 0);


    long pixelStart = 54 + xPosition * 3 + (xPixels * yPosition * 3 + (yPosition * padding)) + glitch;// + (yPosition) | + (yPosition  * 2)
    /*
    Serial.print("\t");
    Serial.print(pixelStart);
    Serial.print("\t");
    Serial.print(file[pixelStart + 2]);
    Serial.print("\t");
    Serial.print(file[pixelStart + 1]);
    Serial.print("\t");
    Serial.println(file[pixelStart]);
    */
    return RGBColor(file[pixelStart + 2], file[pixelStart + 1], file[pixelStart]);
  }
};
