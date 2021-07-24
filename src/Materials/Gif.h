#pragma once

#include <AnimatedGIF.h>
#include "..\Render\Pixel.h"
#include "..\Math\Vector2D.h"

//Converts gif to RGB XY pixel matrix
class Gif{
private:
  AnimatedGIF gifFile;
  Vector2D imageSize;
  Vector2D offsetPosition;
  Pixel* pixels;
  int xPixels;
  int yPixels;
  const int displayWidth = 320;

  RGBColor ConvertRGB565(uint16_t color){
    
  }

  void UpdateLine(GIFDRAW *pDraw){//GIFDraw
        uint8_t *s;
        uint16_t *d, *usPalette, usTemp[320];
        int x, y;

        usPalette = pDraw->pPalette;
        y = pDraw->iY + pDraw->y; // current line
        
        if (pDraw->iWidth > displayWidth)
        pDraw->iWidth = displayWidth;
        s = pDraw->pPixels;
        if (pDraw->ucDisposalMethod == 2) // restore to background color
        {
        for (x=0; x < pDraw->iWidth; x++)
        {
            if (s[x] == pDraw->ucTransparent)
            s[x] = pDraw->ucBackground;
        }
        pDraw->ucHasTransparency = 0;
        }

        if (pDraw->ucHasTransparency) {
        //do nothing for now
        }
        else
        {
        s = pDraw->pPixels;
        // Translate the 8-bit pixels through the RGB565 palette (already byte reversed)
        for (x=0; x < pDraw->iWidth; x++)
            usTemp[x] = usPalette[*s++];

        Serial.println(usTemp[x]);
        }
    }
  
public:
    Gif(Vector2D imageSize, Vector2D offsetPosition, const uint8_t* file){
        this->imageSize = imageSize;
        this->offsetPosition = offsetPosition;
        
        gifFile.begin(BIG_ENDIAN_PIXELS);
        
        if (gifFile.open((uint8_t*)file, sizeof(file), UpdateLine))
        {
        xPixels = gifFile.getCanvasWidth();
        yPixels = gifFile.getCanvasHeight();
        
        Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gifFile.getCanvasWidth(), gifFile.getCanvasHeight());
        while (gifFile.playFrame(true, NULL)){}
        gifFile.close();
        }
        
        pixels = new Pixel[xPixels * yPixels];
    }

    void GetFrame(int i){
        //i = i > maxFrames ? i % maxFrames : i;

    }

    void ReadFrame(){
        
    }

    //maps XY position to an rgb value on the 
    RGBColor GetRGB(Vector2D xyPosition){
        return RGBColor();
    }
};
