#ifndef SPENCER_ANIMATION_H
#define SPENCER_ANIMATION_H

#include <Arduino.h>
#include "gifdec.h"

/*!
	@brief Struct to abstract 24-bit color values.
*/
struct RGBpixel{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

/*!
	@brief Each frame is consisted of a 24-bit color depth array (length = w*h) and its duration in ms.
*/
struct AnimationFrame
{
	RGBpixel *data;
	uint duration;
};

class Animation
{
public:
	Animation(char* gifPath);
	~Animation();
	void rewind();
	AnimationFrame* getNextFrame();
	uint getWidth();
	uint getHeight();
	uint currentFrame = 0;

private:
	std::vector<AnimationFrame> frames;
	gd_GIF *gif;
};



#endif