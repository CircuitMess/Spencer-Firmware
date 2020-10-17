#ifndef SPENCER_INTENT_H
#define SPENCER_INTENT_H

class Intent
{
public:
    Intent(void* params){};
    virtual ~Intent(){};
    virtual void loop() = 0;
};

struct IntentInfo {
	const char* title;
	Intent* (*launch)(void* params);
};

/*
example:

const IntentInfo countInfo {
		"count",
		[](void* params) -> Intent* { return new Intent(params); }
}; */

#endif
