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
	ledmatrix.setBrightness(10);
	ledmatrix.setRotation(2);


	gd_GIF *gif = gd_open_gif("speaking1.gif");
	if(gif == NULL)
	{
		return;
	}
	uint8_t *buffer = (uint8_t*)malloc(gif->width * gif->height * 3);
	for (unsigned looped = 1;; looped++) {
		while (gd_get_frame(gif)) {
			gd_render_frame(gif, buffer);
			//draw
			delay(gif->gce.delay * 10);
			/* insert code to render buffer to screen
				and wait for delay time to pass here  */
		}
		if (looped == gif->loop_count)
			break;
		gd_rewind(gif);
	}
	free(buffer);
	gd_close_gif(gif);
}

void loop(){
	
}
