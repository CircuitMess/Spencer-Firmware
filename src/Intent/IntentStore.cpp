#include "IntentStore.h"
#include "TimeIntent.h"
#include "JokeIntent.h"
#include "StopwatchIntent.h"
#include "../Services/TimeService/TimeService.h"

std::map<const char*, IntentInfo, IntentStore::CStrCompare> IntentStore::storage;

void IntentStore::fillStorage(){
	storage["time"] = {
			"time",
			[](void*) -> Intent*{
				TimeIntentParam params{TimeIntentType::TIME, TimeService.getTime()};
				return new TimeIntent(&params);
			},
			nullptr
	};

	storage["joke"] = {
			"joke",
			[](void*) -> Intent*{ return new JokeIntent(); },
			nullptr
	};

	storage["stopwatch"] = {
			"stopwatch",
			[](void*) -> Intent*{ return new StopwatchIntent(); },
			nullptr
	};
}

const IntentInfo* IntentStore::findIntent(const char* intent){
	auto foundIntent = storage.find(intent);
	if(foundIntent == storage.end()) return nullptr;
	return &foundIntent->second;
}
