#include <Arduino.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <CircuitOS.h>
#include <Input/InputGPIO.h>
#include "src/Services/Audio/Audio.h"
#include "Spencer.hpp"
#include "src/LEDmatrix/LEDmatrix.h"
#include "src/LEDmatrix/gifdec.h"

InputGPIO input;
Audio audio;
LEDmatrix ledmatrix;
struct RGBpixel{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};
void setup(){
	Serial.begin(115200);

	SPIClass spi(3);
	spi.begin(18, 19, 23, FLASH_CS_PIN);
	if(!SerialFlash.begin(spi, FLASH_CS_PIN)){
		Serial.println("Flash fail");
		return;
	}

	if(!ledmatrix.begin())
	{
		Serial.println("couldn't start matrix");
		while(1);
	}
	ledmatrix.clear();
	ledmatrix.setBrightness(20);
	ledmatrix.setRotation(2);

	gd_GIF *gif = gd_open_gif("speaking1.gif");
	if(gif == NULL) return;

	Serial.printf("width: %d, height: %d\n", gif->width, gif->height);
	uint8_t *buffer = (uint8_t*)malloc(gif->width * gif->height * 3);
	for (;;) {
		while (gd_get_frame(gif) == 1) {

			//render color frame into buffer
			gd_render_frame(gif, buffer);

			//draw
			ledmatrix.clear();
			for(uint8_t y = 0; y < gif->height; y++)
			{
				for(uint8_t x = 0; x < gif->width; x++)
				{
					ledmatrix.drawPixel(x, y, ((RGBpixel*)buffer)[y*gif->width + x].r);
				}
			}
			ledmatrix.push();

			//delay according to the frame duration 
			delay(gif->gce.delay * 10);
		}
		gd_rewind(gif);
	}
	free(buffer);
	gd_close_gif(gif);

}

void loop(){
	
}