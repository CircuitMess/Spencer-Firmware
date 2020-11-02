#include "IntentStore.h"
#include "TimeIntent.h"
#include "JokeIntent.h"
#include "StopwatchIntent.h"
#include "../Services/TimeService/TimeService.h"

std::map<const char*, IntentInfo, IntentStore::CStrCompare> IntentStore::storage;

void IntentStore::fillStorage(){
	storage["time"] = {
			"time",
			[](const std::map<std::string, std::string>& params) -> Intent*{
				TimeIntentParam launchParams {TimeIntentType::TIME, TimeService.getTime()};
				return new TimeIntent(&launchParams);
			},
			nullptr
	};

	storage["joke"] = {
			"joke",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new JokeIntent(); },
			nullptr
	};

	storage["stopwatch"] = {
			"stopwatch",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new StopwatchIntent(); },
			nullptr
	};
}

const IntentInfo* IntentStore::findIntent(const char* intent){
	auto foundIntent = storage.find(intent);
	if(foundIntent == storage.end()) return nullptr;
	return &foundIntent->second;
}
