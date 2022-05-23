#include "ErrorState.h"
#include <Audio/Playback.h>
#include "IdleState.h"
#include "SetupState.h"
#include <Devices/Matrix/MatrixAnimGIF.h>
#include <Devices/SerialFlash/SerialFlashFileAdapter.h>
#include <Spencer.h>

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
	delete anim;
}

void ErrorState::doWifi(){
	anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-noWifi.gif"));
	LEDmatrix.startAnimation(anim);
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
			anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-talk.gif"));
			LEDmatrix.startAnimation(anim);
			Playback.playMP3(SampleStore::load(Error, "net"));

			Playback.setPlaybackDoneCallback([](){
				changeState(new SetupState());
			});
			break;

		case NetImpl::NetError::SERVICE:
			anim = new MatrixAnimGIF(new SerialFlashFileAdapter("GIF-error.gif"));
			LEDmatrix.startAnimation(anim);
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
	anim = new MatrixAnimGIF(new SerialFlashFileAdapter("GIF-error500.gif"));
	LEDmatrix.startAnimation(anim);
	Playback.playMP3(SampleStore::load(Error, "mess"));

	Playback.setPlaybackDoneCallback([](){
		changeState(new IdleState());
	});
}

void ErrorState::doApiKey(){
	anim = new MatrixAnimGIF( new SerialFlashFileAdapter("GIF-talk.gif"));
	LEDmatrix.startAnimation(anim);
	Playback.playMP3(SampleStore::load(Error, "apiKey"));

	Playback.setPlaybackDoneCallback([](){
		changeState(new SetupState());
	});
}
