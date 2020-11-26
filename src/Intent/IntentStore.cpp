#include "IntentStore.h"
#include "TimeIntent.h"
#include "JokeIntent.h"
#include "StopwatchIntent.h"
#include "WeatherIntent.h"
#include "VolumeIntent.h"
#include "BrightnessIntent.h"
#include "../Services/TimeService/TimeService.h"
#include "FunpackInclude.hpp"

std::map<const char*, IntentInfo, IntentStore::CStrCompare> IntentStore::storage;

void IntentStore::fillStorage(){
	storage["time"] = {
			"time",
			[](const std::map<std::string, std::string>& params) -> Intent*{
				return new TimeIntent(TimeIntentType::TIME);
			},
			nullptr
	};

	storage["date"] = {
			"date",
			[](const std::map<std::string, std::string>& params) -> Intent*{
				return new TimeIntent(TimeIntentType::DATE);
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

	storage["weather"] = {
			"weather",
			[](const std::map<std::string, std::string>& params) -> Intent*{
				WeatherIntentParam launchParams;
				if(params.at("time").c_str() == nullptr){
					launchParams = WeatherIntentParam::TODAY;
				}else{
					if(strcmp(params.at("time").c_str(), "today") == 0){
					launchParams = WeatherIntentParam::TODAY;
					}else if(strcmp(params.at("time").c_str(), "tomorrow") == 0){
					launchParams = WeatherIntentParam::TOMORROW;
					}else if(strcmp(params.at("time").c_str(), "this week") == 0){
					launchParams = WeatherIntentParam::WEEK;
					}
				}
				return new WeatherIntent(launchParams); },
			nullptr
	};

	storage["volume"] = {
			"volume",
			[](const std::map<std::string, std::string>& params) -> Intent*{
				const char* param = params.at("level").c_str();
				AudioValue value;
				if(param == nullptr){
					value = AudioValue::A_NONE;
				}else{
					if(strcmp(param, "low") == 0 || strcmp(param, "min") == 0 || strcmp(param, "minimum") == 0){
						value = AudioValue::A_LO;
					}else if(strcmp(param, "medium") == 0){
						value = AudioValue::A_MEDIUM;
					}else if(strcmp(param, "high") == 0 || strcmp(param, "max") == 0 || strcmp(param, "maximum") == 0){
						value = AudioValue::A_HI;
					}else if(strcmp(param, "down") == 0 || strcmp(param, "decrease") == 0){
						value = AudioValue::A_DECREASE;
					}else if(strcmp(param, "up") == 0 || strcmp(param, "increase") == 0){
						value = AudioValue::A_INCREASE;
					}
				}
				return new VolumeIntent(value); },
			nullptr
	};

	storage["brightness"] = {
			"brightness",
			[](const std::map<std::string, std::string>& params) -> Intent*{
				const char* param = params.at("level").c_str();
				BrightnessValue value;
				if(param == nullptr){
					value = BrightnessValue::B_NONE;
				}else{
					if(strcmp(param, "low") == 0 || strcmp(param, "min") == 0 || strcmp(param, "minimum") == 0){
						value = BrightnessValue::B_LO;
					}else if(strcmp(param, "medium") == 0){
						value = BrightnessValue::B_MEDIUM;
					}else if(strcmp(param, "high") == 0 || strcmp(param, "max") == 0 || strcmp(param, "maximum") == 0){
						value = BrightnessValue::B_HI;
					}else if(strcmp(param, "down") == 0 || strcmp(param, "decrease") == 0){
						value = BrightnessValue::B_DECREASE;
					}else if(strcmp(param, "up") == 0 || strcmp(param, "increase") == 0){
						value = BrightnessValue::B_INCREASE;
					}
				}
				return new BrightnessIntent(value); },
			nullptr
	};

	storage["funpack.name"] = {
		"funpack.name",
		[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackName(); },
		nullptr
	};
	storage["funpack.feeling"] = {
			"funpack.feeling",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFeeling(); },
			nullptr
	};
	storage["funpack.whatcanyoudo"] = {
			"funpack.whatcanyoudo",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatcanyoudo(); },
			nullptr
	};
	storage["funpack.help"] = {
			"funpack.help",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHelp(); },
			nullptr
	};
	storage["funpack.hello"] = {
			"funpack.hello",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHello(); },
			nullptr
	};
	storage["funpack.horoscope"] = {
			"funpack.horoscope",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHoroscope(); },
			nullptr
	};
	storage["funpack.age"] = {
			"funpack.age",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackAge(); },
			nullptr
	};
	storage["funpack.girlfriend"] = {
			"funpack.girlfriend",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGirlfriend(); },
			nullptr
	};
	storage["funpack.boyfriend"] = {
			"funpack.boyfriend",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBoyfriend(); },
			nullptr
	};
	storage["funpack.color"] = {
			"funpack.color",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackColor(); },
			nullptr
	};
	storage["funpack.siblings"] = {
			"funpack.siblings",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackSiblings(); },
			nullptr
	};
	storage["funpack.creator"] = {
			"funpack.creator",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCreator(); },
			nullptr
	};
	storage["funpack.meaningoflife"] = {
			"funpack.meaningoflife",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackMeaningoflife(); },
			nullptr
	};
	storage["funpack.wheredoyoucomefrom"] = {
			"funpack.wheredoyoucomefrom",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWheredoyoucomefrom(); },
			nullptr
	};
	storage["funpack.language"] = {
			"funpack.language",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackLanguage(); },
			nullptr
	};
	storage["funpack.alexa"] = {
			"funpack.alexa",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackAlexa(); },
			nullptr
	};
	storage["funpack.siri"] = {
			"funpack.siri",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackSiri(); },
			nullptr
	};
	storage["funpack.cortana"] = {
			"funpack.cortana",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCortana(); },
			nullptr
	};
	storage["funpack.google"] = {
			"funpack.google",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGoogle(); },
			nullptr
	};
	storage["funpack.bigsby"] = {
			"funpack.bigsby",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBigsby(); },
			nullptr
	};
	storage["funpack.freetime"] = {
			"funpack.freetime",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFreetime(); },
			nullptr
	};
	storage["funpack.whatsup"] = {
			"funpack.whatsup",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatsup(); },
			nullptr
	};
	storage["funpack.married"] = {
			"funpack.married",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackMarried(); },
			nullptr
	};
	storage["funpack.beyourboyfriend"] = {
			"funpack.beyourboyfriend",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBeyourboyfriend(); },
			nullptr
	};
	storage["funpack.changename"] = {
			"funpack.changename",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackChangename(); },
			nullptr
	};
	storage["funpack.calldifferently"] = {
			"funpack.calldifferently",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCalldifferently(); },
			nullptr
	};
	storage["funpack.piratetalk"] = {
			"funpack.piratetalk",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackPiratetalk(); },
			nullptr
	};
	storage["funpack.whatdoyoudo"] = {
			"funpack.whatdoyoudo",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatdoyoudo(); },
			nullptr
	};
	storage["funpack.howdidyoulearnenglish"] = {
			"funpack.howdidyoulearnenglish",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHowdidyoulearnenglish(); },
			nullptr
	};
	storage["funpack.whoispresident"] = {
			"funpack.whoispresident",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhoispresident(); },
			nullptr
	};
	storage["funpack.howwasyourday"] = {
			"funpack.howwasyourday",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHowwasyourday(); },
			nullptr
	};
	storage["funpack.offense"] = {
			"funpack.offense",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackOffense(); },
			nullptr
	};
	storage["funpack.favouritemovie"] = {
			"funpack.favouritemovie",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFavouritemovie(); },
			nullptr
	};
	storage["funpack.newonnetflix"] = {
			"funpack.newonnetflix",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackNewonnetflix(); },
			nullptr
	};
	storage["funpack.areyouok"] = {
			"funpack.areyouok",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackAreyouok(); },
			nullptr
	};
	storage["funpack.findrecipe"] = {
			"funpack.findrecipe",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFindrecipe(); },
			nullptr
	};
	storage["funpack.findphone"] = {
			"funpack.findphone",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFindphone(); },
			nullptr
	};
	storage["funpack.longtimenosee"] = {
			"funpack.longtimenosee",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackLongtimenosee(); },
			nullptr
	};
	storage["funpack.tellstory"] = {
			"funpack.tellstory",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackTellstory(); },
			nullptr
	};
	storage["funpack.whatsoundfiretruck"] = {
			"funpack.whatsoundfiretruck",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatsoundfiretruck(); },
			nullptr
	};
	storage["funpack.catsounds"] = {
			"funpack.catsounds",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCatsounds(); },
			nullptr
	};
	storage["funpack.dogsound"] = {
			"funpack.dogsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackDogsound(); },
			nullptr
	};
	storage["funpack.horsesound"] = {
			"funpack.horsesound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHorsesound(); },
			nullptr
	};
	storage["funpack.goatsheepsound"] = {
			"funpack.goatsheepsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGoatsheepsound(); },
			nullptr
	};
	storage["funpack.pigsound"] = {
			"funpack.pigsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackPigsound(); },
			nullptr
	};
	storage["funpack.cowsound"] = {
			"funpack.cowsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCowsound(); },
			nullptr
	};
	storage["funpack.donkeysound"] = {
			"funpack.donkeysound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackDonkeysound(); },
			nullptr
	};
	storage["funpack.chikensound"] = {
			"funpack.chikensound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackChikensound(); },
			nullptr
	};
	storage["funpack.roostersound"] = {
			"funpack.roostersound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackRoostersound(); },
			nullptr
	};
	storage["funpack.birdsound"] = {
			"funpack.birdsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBirdsound(); },
			nullptr
	};
	storage["funpack.owlsound"] = {
			"funpack.owlsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackOwlsound(); },
			nullptr
	};
	storage["funpack.duckgeesesound"] = {
			"funpack.duckgeesesound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackDuckgeesesound(); },
			nullptr
	};
	storage["funpack.turkeysound"] = {
			"funpack.turkeysound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackTurkeysound(); },
			nullptr
	};
	storage["funpack.frogsound"] = {
			"funpack.frogsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFrogsound(); },
			nullptr
	};
	storage["funpack.lionsound"] = {
			"funpack.lionsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackLionsound(); },
			nullptr
	};
	storage["funpack.truck"] = {
			"funpack.truck",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackTruck(); },
			nullptr
	};
	storage["funpack.angrycrowd"] = {
			"funpack.angrycrowd",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackAngrycrowd(); },
			nullptr
	};
	storage["funpack.ghost"] = {
			"funpack.ghost",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGhost(); },
			nullptr
	};
	storage["funpack.whoiswithyou"] = {
			"funpack.whoiswithyou",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhoiswithyou(); },
			nullptr
	};
	storage["funpack.playagame"] = {
			"funpack.playagame",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackPlayagame(); },
			nullptr
	};
	storage["funpack.singmeasong"] = {
			"funpack.singmeasong",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackSingmeasong(); },
			nullptr
	};
	storage["funpack.beatbox"] = {
			"funpack.beatbox",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBeatbox(); },
			nullptr
	};
	storage["funpack.favoritefood"] = {
			"funpack.favoritefood",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFavoritefood(); },
			nullptr
	};
	storage["funpack.believeinlove"] = {
			"funpack.believeinlove",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBelieveinlove(); },
			nullptr
	};
	storage["funpack.believeinaliens"] = {
			"funpack.believeinaliens",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBelieveinaliens(); },
			nullptr
	};
	storage["funpack.goodmorning"] = {
			"funpack.goodmorning",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGoodmorning(); },
			nullptr
	};
	storage["funpack.goodevening"] = {
			"funpack.goodevening",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGoodevening(); },
			nullptr
	};
	storage["funpack.goodday"] = {
			"funpack.goodday",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGoodday(); },
			nullptr
	};
	storage["funpack.goodnight"] = {
			"funpack.goodnight",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGoodnight(); },
			nullptr
	};
	storage["funpack.hi"] = {
			"funpack.hi",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHi(); },
			nullptr
	};
	storage["funpack.isthisreallife"] = {
			"funpack.isthisreallife",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackIsthisreallife(); },
			nullptr
	};
	storage["funpack.callmom"] = {
			"funpack.callmom",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCallmom(); },
			nullptr
	};
	storage["funpack.turnlights"] = {
			"funpack.turnlights",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackTurnlights(); },
			nullptr
	};
	storage["funpack.settemprature"] = {
			"funpack.settemprature",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackSettemprature(); },
			nullptr
	};
	storage["funpack.tv"] = {
			"funpack.tv",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackTv(); },
			nullptr
	};
	storage["funpack.buyaboat"] = {
			"funpack.buyaboat",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBuyaboat(); },
			nullptr
	};
	storage["funpack.serande"] = {
			"funpack.serande",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackSerande(); },
			nullptr
	};
	storage["funpack.happybirthday"] = {
			"funpack.happybirthday",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHappybirthday(); },
			nullptr
	};
	storage["funpack.celebritycrush"] = {
			"funpack.celebritycrush",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCelebritycrush(); },
			nullptr
	};
	storage["funpack.merrychristmas"] = {
			"funpack.merrychristmas",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackMerrychristmas(); },
			nullptr
	};
	storage["funpack.pickupline"] = {
			"funpack.pickupline",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackPickupline(); },
			nullptr
	};
	storage["funpack.compliment"] = {
			"funpack.compliment",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCompliment(); },
			nullptr
	};
	storage["funpack.umbrella"] = {
			"funpack.umbrella",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackUmbrella(); },
			nullptr
	};
	storage["funpack.secret"] = {
			"funpack.secret",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackSecret(); },
			nullptr
	};
	storage["funpack.whatdoyouthinkofme"] = {
			"funpack.whatdoyouthinkofme",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatdoyouthinkofme(); },
			nullptr
	};
	storage["funpack.favoritesong"] = {
			"funpack.favoritesong",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFavoritesong(); },
			nullptr
	};
	storage["funpack.highfive"] = {
			"funpack.highfive",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHighfive(); },
			nullptr
	};
	storage["funpack.orderuber"] = {
			"funpack.orderuber",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackOrderuber(); },
			nullptr
	};
	storage["funpack.whereispassport"] = {
			"funpack.whereispassport",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhereispassport(); },
			nullptr
	};
	storage["funpack.whatispassword"] = {
			"funpack.whatispassword",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatispassword(); },
			nullptr
	};
	storage["funpack.package"] = {
			"funpack.package",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackPackage(); },
			nullptr
	};
	storage["funpack.lonely"] = {
			"funpack.lonely",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackLonely(); },
			nullptr
	};
	storage["funpack.dislike"] = {
			"funpack.dislike",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackDislike(); },
			nullptr
	};
	storage["funpack.like"] = {
			"funpack.like",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackLike(); },
			nullptr
	};
	storage["funpack.scarystory"] = {
			"funpack.scarystory",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackScarystory(); },
			nullptr
	};
	storage["funpack.readapoem"] = {
			"funpack.readapoem",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackReadapoem(); },
			nullptr
	};
	storage["funpack.whatisyourquest"] = {
			"funpack.whatisyourquest",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatisyourquest(); },
			nullptr
	};
	storage["funpack.iamyourfather"] = {
			"funpack.iamyourfather",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackIamyourfather(); },
			nullptr
	};
	storage["funpack.areyouskynet"] = {
			"funpack.areyouskynet",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackAreyouskynet(); },
			nullptr
	};
	storage["funpack.makesandwitch"] = {
			"funpack.makesandwitch",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackMakesandwitch(); },
			nullptr
	};
	storage["funpack.cheatcode"] = {
			"funpack.cheatcode",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCheatcode(); },
			nullptr
	};
	storage["funpack.doabarrelroll"] = {
			"funpack.doabarrelroll",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackDoabarrelroll(); },
			nullptr
	};
	storage["funpack.notbirthday"] = {
			"funpack.notbirthday",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackNotbirthday(); },
			nullptr
	};
	storage["funpack.didyoufart"] = {
			"funpack.didyoufart",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackDidyoufart(); },
			nullptr
	};
	storage["funpack.beammeupscotty"] = {
			"funpack.beammeupscotty",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBeammeupscotty(); },
			nullptr
	};


}

const IntentInfo* IntentStore::findIntent(const char* intent){
	auto foundIntent = storage.find(intent);
	if(foundIntent == storage.end()) return nullptr;
	return &foundIntent->second;
}
