#ifndef SPENCER_INTENTINFO_H
#define SPENCER_INTENTINFO_H

#include <map>

class Intent;

struct IntentInfo {
	const char* title;
	Intent* (*launch)(const std::map<std::string, std::string>& params);

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

#endif //SPENCER_INTENTINFO_H
