#include "Animation.h"

Animation::Animation(char* gifPath)
{
	gif = gd_open_gif(gifPath);
	if(gif == NULL) return;

	// Serial.printf("width: %d, height: %d\n", gif->width, gif->height);
	while (gd_get_frame(gif) == 1) {

		uint8_t *buffer = (uint8_t*)malloc(gif->width * gif->height);
		//render 24-bit color frame into buffer
		gd_render_frame(gif, buffer, 1);
		frames.push_back(AnimationFrame{buffer, gif->gce.delay*10});
	}
}

Animation::~Animation()
{
	for(AnimationFrame i : frames)
	{
		free(i.data);
	}
	gd_close_gif(gif);
}

void Animation::rewind()
{
	currentFrame = 0;
}

AnimationFrame* Animation::getNextFrame()
{
	if(currentFrame >= frames.size()) return nullptr;
	return &frames[currentFrame++];
}

uint Animation::getWidth()
{
	return gif->width;
}

uint Animation::getHeight()
{
	return gif->height;
}