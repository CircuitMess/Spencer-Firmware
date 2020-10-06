#ifndef SPENCER_SPEECH2INTENT_H
#define SPENCER_SPEECH2INTENT_H

class SpeechToIntent
{
public:
    void identifyVoice(void (*callback)(void), const char* fileName = "recording.wav");
};

extern SpeechToIntent speechToIntent;
#endif