
#include "screen.h"
#include "logging.h"
#include "apokalypseapp.h"
#include "libcpputil/tboolentry.h"
#include "libcpputil/tsizeentry.h"
#include "libcpputil/tintentry.h"
#include "sdl_utils.h"

Screen::Screen() : CStatus(){
	SetClassName("Screen");
	screen = 0;
	bkgnd = 0;
	scaledbg = 0;

	if (application){
		width = TSizeEntry(application->getAppConfig().getEntry("SCREEN","RESOLUTION")).getWidth(800);
		height = TSizeEntry(application->getAppConfig().getEntry("SCREEN","RESOLUTION")).getHeight(600);
		bpp = TIntEntry(application->getAppConfig().getEntry("SCREEN","BPP")).getInt(16);
		fullscreen = TBoolEntry(application->getAppConfig().getEntry("SCREEN","FULLSCREEN")).getBool(false);
		}else{
		LogWarning("Application not available");
		SetStatus(STATUS_ERROR);
		return;
		}

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0){
		LogWarning("Couldn't initialize SDL: %s", SDL_GetError());
		SetStatus(STATUS_ERROR);
		return;
		}
	SDL_WM_SetCaption("Apokalypse",0);

	if (!setVideoMode(width,height,bpp,fullscreen)){
		SetStatus(STATUS_ERROR);
		return;
		}
}

Screen::~Screen(){
	if (application){
		TBoolEntry(&application->getAppConfig(),"SCREEN","FULLSCREEN").setBool(fullscreen);
		TIntEntry(&application->getAppConfig(),"SCREEN","BPP").setInt(bpp);
		TSizeEntry(&application->getAppConfig(),"SCREEN","RESOLUTION").setSize(width,height);
		}else{
		LogWarning("Application not available");
		}
	if (bkgnd) SDL_FreeSurface(bkgnd);
	if (scaledbg) SDL_FreeSurface(scaledbg);
	SDL_Quit();
}

bool Screen::setVideoMode(int w, int h, int bpp, bool fs){
	SDL_Surface *nscreen = screen;

	if (!screen || w != width || h != height || fs != fullscreen || bpp != this->bpp){
		nscreen = SDL_SetVideoMode(w, h, bpp, SDL_SWSURFACE | (fs)?SDL_FULLSCREEN:0);
		if (nscreen == NULL) {
			LogWarning("Could not set videomode %dx%dx%d: %s",w,h,bpp,SDL_GetError());
			SetStatus(STATUS_ERROR);
			return false;
			}
		LogDebug("Set new Videomode (%dx%dx%d, %s)",w,h,bpp,(fs)?"fullscreen":"windowed");

		//if (screen) SDL_FreeSurface(screen);
		width = w;
		height = h;
		fullscreen = fs;
		this->bpp = bpp;
		screen = nscreen;

		setBackground(bkgnd);
		}else
		LogDebug("Videomode already set.");

	return true;
}

SDL_Surface* Screen::getScreen(){
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = scaledbg->w;
	r.h = scaledbg->h;
	SDL_BlitSurface(scaledbg, NULL, screen, &r);
	return screen;
}

SDL_Surface* Screen::getScreenSurface(){
	return screen;
}

void Screen::setBackground(SDL_Surface *bg){
	if (bkgnd && bkgnd != bg){
		SDL_FreeSurface(bkgnd);
		bkgnd = 0;
		}
	if (scaledbg){
		SDL_FreeSurface(scaledbg);
		scaledbg = 0;
		}
	if (bg){
		SDL_Surface *oldbg = bkgnd;
		SDL_Surface *img1 = SDL_CreateRGBSurface(SDL_SWSURFACE, bg->w, bg->h, bg->format->BitsPerPixel,
			bg->format->Rmask, bg->format->Gmask, bg->format->Bmask, bg->format->Amask);

		SDL_Rect drect;
		drect.x = 0;
		drect.y = 0;
		drect.w = bg->w;
		drect.h = bg->h;
		SDL_BlitSurface(bg, &drect, img1, NULL);
		bkgnd = SDL_DisplayFormat(img1);
		SDL_FreeSurface(img1);
		if (oldbg)
			SDL_FreeSurface(oldbg);

		scaledbg = SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, screen->format->BitsPerPixel,
			screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);
		scalesurface(scaledbg,bkgnd);
		}
}

void Screen::update(int x = 0, int y = 0, int w = 0, int h = 0){
	SDL_UpdateRect(screen, x, y, w, h);
}

int Screen::getWidth(){
	return width;
}

int Screen::getHeight(){
	return height;
}

bool Screen::getFullScreen(){
	return fullscreen;
}

int Screen::getbpp(){
	return bpp;
}


