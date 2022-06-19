#include "IntentStore.h"
#include "TimeIntent.h"
#include "JokeIntent.h"
#include "StopwatchIntent.h"
#include "WeatherIntent.h"
#include "VolumeIntent.h"
#include "BrightnessIntent.h"
#include "FunpackInclude.hpp"

std::map<const char*, IntentInfo, IntentStore::CStrCompare> IntentStore::storage;

void IntentStore::fillStorage(){
	storage["Time"] = {
			"time",
			[](const std::map<std::string, std::string>& params) -> Intent*{
				return new TimeIntent(TimeIntentType::TIME);
			},
			nullptr
	};

	storage["Date"] = {
			"date",
			[](const std::map<std::string, std::string>& params) -> Intent*{
				return new TimeIntent(TimeIntentType::DATE);
			},
			nullptr
	};

	storage["Joke"] = {
			"joke",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new JokeIntent(); },
			nullptr
	};

	storage["Stopwatch"] = {
			"stopwatch",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new StopwatchIntent(); },
			nullptr
	};

	storage["Weather"] = {
			"weather",
			[](const std::map<std::string, std::string>& params) -> Intent*{
				WeatherIntentParam launchParams = WeatherIntentParam::TODAY;
				if(params.find("time") != params.end()){
					if(params.at("time") == "tomorrow"){
						launchParams = WeatherIntentParam::TOMORROW;
					}else if(params.at("time") == "this week" || params.at("time") == "week" || params.at("time") == "weekly"){
						launchParams = WeatherIntentParam::WEEK;
					}
				}
				return new WeatherIntent(launchParams);
			},
			nullptr
	};

	storage["Volume"] = {
			"volume",
			[](const std::map<std::string, std::string>& params) -> Intent*{
				AudioValue value = AudioValue::A_NONE;
				if(params.find("level") == params.end()){
					value = AudioValue::A_NONE;
				}else{
					std::string param = params.at("level");

					if(param == "low" || param == "min" || param == "minimum" || param == "lowest" || param == "quietest" || param == "quiet"){
						value = AudioValue::A_LO;
					}else if(param == "medium" || param == "mid"){
						value = AudioValue::A_MEDIUM;
					}else if(param == "high" || param == "max" || param == "maximum" || param == "highest" || param == "loudest" || param == "loud"){
						value = AudioValue::A_HI;
					}else if(param == "down" || param == "decrease"){
						value = AudioValue::A_DECREASE;
					}else if(param == "up" || param == "increase"){
						value = AudioValue::A_INCREASE;
					}
				}
				return new VolumeIntent(value);
			},
			nullptr
	};

	storage["Brightness"] = {
			"brightness",
			[](const std::map<std::string, std::string>& params) -> Intent*{
				BrightnessValue value = BrightnessValue::B_NONE;
				if(params.find("level") == params.end()){
					value = BrightnessValue::B_NONE;
				}else{
					std::string param = params.at("level");

					if(param == "low" || param == "min" || param == "minimum"){
						value = BrightnessValue::B_LO;
					}else if(param == "medium"){
						value = BrightnessValue::B_MEDIUM;
					}else if(param == "high" || param == "max" || param == "maximum" || param == "brightest"){
						value = BrightnessValue::B_HI;
					}else if(param == "down" || param == "decrease"){
						value = BrightnessValue::B_DECREASE;
					}else if(param == "up" || param == "increase"){
						value = BrightnessValue::B_INCREASE;
					}
				}
				return new BrightnessIntent(value);
			},
			nullptr
	};

	storage["funpack_name"] = {
		"funpack_name",
		[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackName(); },
		nullptr
	};
	storage["funpack_feeling"] = {
			"funpack_feeling",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFeeling(); },
			nullptr
	};
	storage["funpack_whatcanyoudo"] = {
			"funpack_whatcanyoudo",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatcanyoudo(); },
			nullptr
	};
	storage["funpack_help"] = {
			"funpack_help",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHelp(); },
			nullptr
	};
	storage["funpack_hello"] = {
			"funpack_hello",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHello(); },
			nullptr
	};
	storage["funpack_horoscope"] = {
			"funpack_horoscope",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHoroscope(); },
			nullptr
	};
	storage["funpack_age"] = {
			"funpack_age",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackAge(); },
			nullptr
	};
	storage["funpack_girlfriend"] = {
			"funpack_girlfriend",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGirlfriend(); },
			nullptr
	};
	storage["funpack_boyfriend"] = {
			"funpack_boyfriend",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBoyfriend(); },
			nullptr
	};
	storage["funpack_color"] = {
			"funpack_color",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackColor(); },
			nullptr
	};
	storage["funpack_siblings"] = {
			"funpack_siblings",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackSiblings(); },
			nullptr
	};
	storage["funpack_creator"] = {
			"funpack_creator",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCreator(); },
			nullptr
	};
	storage["funpack_meaningoflife"] = {
			"funpack_meaningoflife",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackMeaningoflife(); },
			nullptr
	};
	storage["funpack_wheredoyoucomefrom"] = {
			"funpack_wheredoyoucomefrom",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWheredoyoucomefrom(); },
			nullptr
	};
	storage["funpack_language"] = {
			"funpack_language",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackLanguage(); },
			nullptr
	};
	storage["funpack_alexa"] = {
			"funpack_alexa",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackAlexa(); },
			nullptr
	};
	storage["funpack_siri"] = {
			"funpack_siri",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackSiri(); },
			nullptr
	};
	storage["funpack_cortana"] = {
			"funpack_cortana",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCortana(); },
			nullptr
	};
	storage["funpack_google"] = {
			"funpack_google",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGoogle(); },
			nullptr
	};
	storage["funpack_bigsby"] = {
			"funpack_bigsby",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBigsby(); },
			nullptr
	};
	storage["funpack_freetime"] = {
			"funpack_freetime",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFreetime(); },
			nullptr
	};
	storage["funpack_whatsup"] = {
			"funpack_whatsup",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatsup(); },
			nullptr
	};
	storage["funpack_married"] = {
			"funpack_married",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackMarried(); },
			nullptr
	};
	storage["funpack_beyourboyfriend"] = {
			"funpack_beyourboyfriend",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBeyourboyfriend(); },
			nullptr
	};
	storage["funpack_changename"] = {
			"funpack_changename",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackChangename(); },
			nullptr
	};
	storage["funpack_calldifferently"] = {
			"funpack_calldifferently",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCalldifferently(); },
			nullptr
	};
	storage["funpack_piratetalk"] = {
			"funpack_piratetalk",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackPiratetalk(); },
			nullptr
	};
	storage["funpack_whatdoyoudo"] = {
			"funpack_whatdoyoudo",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatdoyoudo(); },
			nullptr
	};
	storage["funpack_howdidyoulearnenglish"] = {
			"funpack_howdidyoulearnenglish",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHowdidyoulearnenglish(); },
			nullptr
	};
	storage["funpack_whoispresident"] = {
			"funpack_whoispresident",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhoispresident(); },
			nullptr
	};
	storage["funpack_howwasyourday"] = {
			"funpack_howwasyourday",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHowwasyourday(); },
			nullptr
	};
	storage["funpack_offense"] = {
			"funpack_offense",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackOffense(); },
			nullptr
	};
	storage["funpack_favouritemovie"] = {
			"funpack_favouritemovie",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFavouritemovie(); },
			nullptr
	};
	storage["funpack_newonnetflix"] = {
			"funpack_newonnetflix",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackNewonnetflix(); },
			nullptr
	};
	storage["funpack_areyouok"] = {
			"funpack_areyouok",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackAreyouok(); },
			nullptr
	};
	storage["funpack_findrecipe"] = {
			"funpack_findrecipe",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFindrecipe(); },
			nullptr
	};
	storage["funpack_findphone"] = {
			"funpack_findphone",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFindphone(); },
			nullptr
	};
	storage["funpack_longtimenosee"] = {
			"funpack_longtimenosee",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackLongtimenosee(); },
			nullptr
	};
	storage["funpack_tellstory"] = {
			"funpack_tellstory",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackTellstory(); },
			nullptr
	};
	storage["funpack_whatsoundfiretruck"] = {
			"funpack_whatsoundfiretruck",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatsoundfiretruck(); },
			nullptr
	};
	storage["funpack_catsounds"] = {
			"funpack_catsounds",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCatsounds(); },
			nullptr
	};
	storage["funpack_dogsound"] = {
			"funpack_dogsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackDogsound(); },
			nullptr
	};
	storage["funpack_horsesound"] = {
			"funpack_horsesound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHorsesound(); },
			nullptr
	};
	storage["funpack_goatsheepsound"] = {
			"funpack_goatsheepsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGoatsheepsound(); },
			nullptr
	};
	storage["funpack_pigsound"] = {
			"funpack_pigsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackPigsound(); },
			nullptr
	};
	storage["funpack_cowsound"] = {
			"funpack_cowsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCowsound(); },
			nullptr
	};
	storage["funpack_donkeysound"] = {
			"funpack_donkeysound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackDonkeysound(); },
			nullptr
	};
	storage["funpack_chikensound"] = {
			"funpack_chikensound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackChikensound(); },
			nullptr
	};
	storage["funpack_roostersound"] = {
			"funpack_roostersound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackRoostersound(); },
			nullptr
	};
	storage["funpack_birdsound"] = {
			"funpack_birdsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBirdsound(); },
			nullptr
	};
	storage["funpack_owlsound"] = {
			"funpack_owlsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackOwlsound(); },
			nullptr
	};
	storage["funpack_duckgeesesound"] = {
			"funpack_duckgeesesound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackDuckgeesesound(); },
			nullptr
	};
	storage["funpack_turkeysound"] = {
			"funpack_turkeysound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackTurkeysound(); },
			nullptr
	};
	storage["funpack_frogsound"] = {
			"funpack_frogsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFrogsound(); },
			nullptr
	};
	storage["funpack_lionsound"] = {
			"funpack_lionsound",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackLionsound(); },
			nullptr
	};
	storage["funpack_truck"] = {
			"funpack_truck",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackTruck(); },
			nullptr
	};
	storage["funpack_angrycrowd"] = {
			"funpack_angrycrowd",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackAngrycrowd(); },
			nullptr
	};
	storage["funpack_ghost"] = {
			"funpack_ghost",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGhost(); },
			nullptr
	};
	storage["funpack_whoiswithyou"] = {
			"funpack_whoiswithyou",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhoiswithyou(); },
			nullptr
	};
	storage["funpack_playagame"] = {
			"funpack_playagame",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackPlayagame(); },
			nullptr
	};
	storage["funpack_singmeasong"] = {
			"funpack_singmeasong",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackSingmeasong(); },
			nullptr
	};
	storage["funpack_beatbox"] = {
			"funpack_beatbox",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBeatbox(); },
			nullptr
	};
	storage["funpack_favoritefood"] = {
			"funpack_favoritefood",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFavoritefood(); },
			nullptr
	};
	storage["funpack_believeinlove"] = {
			"funpack_believeinlove",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBelieveinlove(); },
			nullptr
	};
	storage["funpack_believeinaliens"] = {
			"funpack_believeinaliens",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBelieveinaliens(); },
			nullptr
	};
	storage["funpack_goodmorning"] = {
			"funpack_goodmorning",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGoodmorning(); },
			nullptr
	};
	storage["funpack_goodevening"] = {
			"funpack_goodevening",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGoodevening(); },
			nullptr
	};
	storage["funpack_goodday"] = {
			"funpack_goodday",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGoodday(); },
			nullptr
	};
	storage["funpack_goodnight"] = {
			"funpack_goodnight",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackGoodnight(); },
			nullptr
	};
	storage["funpack_hi"] = {
			"funpack_hi",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHi(); },
			nullptr
	};
	storage["funpack_isthisreallife"] = {
			"funpack_isthisreallife",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackIsthisreallife(); },
			nullptr
	};
	storage["funpack_callmom"] = {
			"funpack_callmom",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCallmom(); },
			nullptr
	};
	storage["funpack_turnlights"] = {
			"funpack_turnlights",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackTurnlights(); },
			nullptr
	};
	storage["funpack_settemprature"] = {
			"funpack_settemprature",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackSettemprature(); },
			nullptr
	};
	storage["funpack_tv"] = {
			"funpack_tv",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackTv(); },
			nullptr
	};
	storage["funpack_buyaboat"] = {
			"funpack_buyaboat",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBuyaboat(); },
			nullptr
	};
	storage["funpack_serande"] = {
			"funpack_serande",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackSerande(); },
			nullptr
	};
	storage["funpack_happybirthday"] = {
			"funpack_happybirthday",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHappybirthday(); },
			nullptr
	};
	storage["funpack_celebritycrush"] = {
			"funpack_celebritycrush",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCelebritycrush(); },
			nullptr
	};
	storage["funpack_merrychristmas"] = {
			"funpack_merrychristmas",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackMerrychristmas(); },
			nullptr
	};
	storage["funpack_pickupline"] = {
			"funpack_pickupline",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackPickupline(); },
			nullptr
	};
	storage["funpack_compliment"] = {
			"funpack_compliment",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCompliment(); },
			nullptr
	};
	storage["funpack_umbrella"] = {
			"funpack_umbrella",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackUmbrella(); },
			nullptr
	};
	storage["funpack_secret"] = {
			"funpack_secret",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackSecret(); },
			nullptr
	};
	storage["funpack_whatdoyouthinkofme"] = {
			"funpack_whatdoyouthinkofme",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatdoyouthinkofme(); },
			nullptr
	};
	storage["funpack_favoritesong"] = {
			"funpack_favoritesong",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackFavoritesong(); },
			nullptr
	};
	storage["funpack_highfive"] = {
			"funpack_highfive",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackHighfive(); },
			nullptr
	};
	storage["funpack_orderuber"] = {
			"funpack_orderuber",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackOrderuber(); },
			nullptr
	};
	storage["funpack_whereispassport"] = {
			"funpack_whereispassport",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhereispassport(); },
			nullptr
	};
	storage["funpack_whatispassword"] = {
			"funpack_whatispassword",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatispassword(); },
			nullptr
	};
	storage["funpack_package"] = {
			"funpack_package",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackPackage(); },
			nullptr
	};
	storage["funpack_lonely"] = {
			"funpack_lonely",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackLonely(); },
			nullptr
	};
	storage["funpack_dislike"] = {
			"funpack_dislike",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackDislike(); },
			nullptr
	};
	storage["funpack_like"] = {
			"funpack_like",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackLike(); },
			nullptr
	};
	storage["funpack_scarystory"] = {
			"funpack_scarystory",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackScarystory(); },
			nullptr
	};
	storage["funpack_readapoem"] = {
			"funpack_readapoem",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackReadapoem(); },
			nullptr
	};
	storage["funpack_whatisyourquest"] = {
			"funpack_whatisyourquest",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackWhatisyourquest(); },
			nullptr
	};
	storage["funpack_iamyourfather"] = {
			"funpack_iamyourfather",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackIamyourfather(); },
			nullptr
	};
	storage["funpack_areyouskynet"] = {
			"funpack_areyouskynet",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackAreyouskynet(); },
			nullptr
	};
	storage["funpack_makesandwitch"] = {
			"funpack_makesandwitch",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackMakesandwitch(); },
			nullptr
	};
	storage["funpack_cheatcode"] = {
			"funpack_cheatcode",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackCheatcode(); },
			nullptr
	};
	storage["funpack_doabarrelroll"] = {
			"funpack_doabarrelroll",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackDoabarrelroll(); },
			nullptr
	};
	storage["funpack_notbirthday"] = {
			"funpack_notbirthday",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackNotbirthday(); },
			nullptr
	};
	storage["funpack_didyoufart"] = {
			"funpack_didyoufart",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackDidyoufart(); },
			nullptr
	};
	storage["funpack_beammeupscotty"] = {
			"funpack_beammeupscotty",
			[](const std::map<std::string, std::string>&) -> Intent*{ return new FunpackBeammeupscotty(); },
			nullptr
	};


}

const IntentInfo* IntentStore::findIntent(const char* intent){
	auto foundIntent = storage.find(intent);
	if(foundIntent == storage.end()) return nullptr;
	return &foundIntent->second;
}
