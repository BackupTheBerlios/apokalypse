
#ifndef SDL_PANEL_H
#define SDL_PANEL_H

#include "sdl_window.h"

class SDL_Panel : public SDL_Window{
public:
	SDL_Panel(Screen *screen);
	virtual ~SDL_Panel();
	
};

#endif


