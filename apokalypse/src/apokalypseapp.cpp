
#include "apokalypseapp.h"
#include "logging.h"
#include "screen.h"
#include "libcpputil/tconfigfile.h"
#include "libcpputil/tconfig.h"
#include "libcpputil/tboolentry.h"
#include "libcpputil/tintentry.h"
#include "libcpputil/tstringentry.h"

#include <SDL_image.h>
#include <SDL_mixer.h>
#include "sdl_utils.h"
#include "intro.h"
#include "menuscreen.h"

ApokalypseApp *application = 0;

ApokalypseApp::ApokalypseApp() : CStatus(){
	application = this;
	SetClassName("ApokalypseApp");
	screen = 0;
	audiook = false;
}

ApokalypseApp::~ApokalypseApp(){
	if (screen) delete screen;
	if (!configfile.isEmpty())
		saveConfig();
}

void ApokalypseApp::readConfig(const TString &filename){
	configfile = filename;
	TConfigFile cf(configfile);
	appconfig << cf;
	LogDebug("ApokalypseApp: config loaded from %s",configfile.text());
}

void ApokalypseApp::readDataConfig(const TString &filename){
	TConfigFile cf(filename);
	dataconfig << cf;
	LogDebug("ApokalypseApp: dataconfig loaded from %s",filename.text());
}

int ApokalypseApp::init(){
	screen = new Screen();
	if (screen->Status() != STATUS_OK){
		SetStatusFrom(screen);
		return -1;
		}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 512) != 0){
		LogWarning("Could not init audiomixer");
		}else audiook = true;

	return 0;
}

int ApokalypseApp::run(){
	LogDebug("Hallo Welt");

	SDL_Surface *img = IMG_Load(TStringEntry(application->getDataConfig().getEntry("","backgroundimg")).getString().text());
	screen->setBackground(img);
	if (!img){
		LogWarning("Could not load image: %s",SDL_GetError());
		}else{
		SDL_FreeSurface(img);
		}

	Intro *intro = new Intro(screen);
	intro->run();
	delete intro;

	MenuScreen *menu = new MenuScreen(screen);
	int menuresult = menu->run();
	switch (menuresult){
		case 0:		break;
		default:	{LogWarning("invalid menuresult, bailing out");
					return 0;
					}break;

		};
	delete menu;

	return 0;
}

void ApokalypseApp::saveConfig(){
	TConfigFile cf(configfile);
	appconfig >> cf;
	LogDebug("ApokalypseApp: config saved to %s",configfile.text());
}

TConfig& ApokalypseApp::getAppConfig(){
	return appconfig;
}

TConfig& ApokalypseApp::getDataConfig(){
	return dataconfig;
}

bool ApokalypseApp::haveAudio(){
	return audiook;
}




