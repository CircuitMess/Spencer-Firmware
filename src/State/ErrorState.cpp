#include "ErrorState.h"
#include <Audio/Playback.h>
#include <LEDmatrix/LEDmatrix.h>
#include "IdleState.h"
#include "SetupState.h"

ErrorState::ErrorState(ErrorType type) : type(type){ }

void ErrorState::enter(){
	switch(type){
		case WIFI:
			doWifi();
			break;

		case NETWORK:
			doNetwork();
			break;

		case JSON:
			doJson();
			break;

		case APIKEY:
			doApiKey();
			break;
	}
}

void ErrorState::exit(){

}

void ErrorState::doWifi(){
	LEDmatrix.startAnimation(new Animation("GIF-noWifi.gif"), true);
	Playback.playMP3(SampleStore::load(Error, "wifi"));

	Playback.setPlaybackDoneCallback([](){
		changeState(new SetupState());
	});
}

void ErrorState::doNetwork(){
	NetImpl::NetError error = Net.getLastError();

	switch(error){
		case NetImpl::NetError::WIFI:
			doWifi();
			break;

		case NetImpl::NetError::NET:
			LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
			Playback.playMP3(SampleStore::load(Error, "net"));

			Playback.setPlaybackDoneCallback([](){
				changeState(new SetupState());
			});
			break;

		case NetImpl::NetError::SERVICE:
			LEDmatrix.startAnimation(new Animation("GIF-error.gif"), true);
			Playback.playMP3(SampleStore::load(Error, "service"));

			Playback.setPlaybackDoneCallback([](){
				changeState(new IdleState());
			});
			break;

		case NetImpl::NetError::OK:
		default:
			doJson();
			break;
	}
}

void ErrorState::doJson(){
	LEDmatrix.startAnimation(new Animation("GIF-error500.gif"), true);
	Playback.playMP3(SampleStore::load(Error, "mess"));

	Playback.setPlaybackDoneCallback([](){
		changeState(new IdleState());
	});
}

void ErrorState::doApiKey(){
	LEDmatrix.startAnimation(new Animation("GIF-talk.gif"), true);
	Playback.playMP3(SampleStore::load(Error, "apiKey"));

	Playback.setPlaybackDoneCallback([](){
		changeState(new SetupState());
	});
}
