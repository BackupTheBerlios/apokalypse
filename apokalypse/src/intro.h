
#ifndef INTRO_H
#define INTRO_H

#include "status.h"
#include <SDL.h>

class Screen;
class Font;

class Intro : public CStatus{
public:
	Intro(Screen *screen);
	~Intro();

	void run();

protected:
	int checkEvents();
	void renderText(Font *font);

	Screen * screen;
	SDL_Surface *textsurface;
};

#endif


