#ifndef SPENCER_INTENT_H
#define SPENCER_INTENT_H

class Intent
{
public:
    virtual ~Intent() = default;
    virtual void loop() = 0;
};

struct IntentInfo {
	const char* title;
	Intent* (*launch)(void* params);

	struct Upsell {
		const char* query;
		const char* intent;
	}* upsell;
};

/*
example:

const IntentInfo whatIsCorona {
	"what_corona",
	[](void* params) -> Intent* { return new WhatCoronaIntent(); },
	new IntentInfo::Upsell { // or nullptr
		"Would like to know about the current corona state?",
		"coronaupdate"
	}
};
 */

#endif
