
#ifndef SDL_BUTTON_H
#define SDL_BUTTON_H

#include "sdl_window.h"
#include "libcpputil/tstring.h"
#include <SDL.h>
#include <SDL_mixer.h>

class SDL_Button: public SDL_Window{
public:
	SDL_Button(Screen *screen, const TString &datasection);
	virtual ~SDL_Button();
	virtual void update();
	virtual int checkEvent(SDL_Event *event);
protected:
	SDL_Surface *normal;
	SDL_Surface *active;
	SDL_Surface *pressed;
	bool isactive;
	bool ispressed;
	Mix_Music *sound_pressed;
	Mix_Music *sound_activated;
};

#endif


