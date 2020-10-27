#include "IntentStore.h"
#include "TimeIntent.h"
#include "JokeIntent.h"
#include "StopwatchIntent.h"

std::map<const char*, IntentInfo> IntentStore::storage;

IntentStore::IntentStoreFiller::IntentStoreFiller(){
	storage["time"] = {
			"time",
			[](void*) -> Intent* { return new TimeIntent(nullptr); },
			nullptr
	};

	storage["joke"] = {
			"joke",
			[](void*) -> Intent* { return new JokeIntent(nullptr); },
			nullptr
	};

	storage["stopwatch"] = {
		"stopwatch",
			[](void*) -> Intent* { return new StopwatchIntent(nullptr); },
			nullptr
	};
}

const IntentInfo* IntentStore::findIntent(const char* intent){
	auto foundIntent = storage.find(intent);
	if(foundIntent == storage.end()) return nullptr;
	return &foundIntent->second;
}
