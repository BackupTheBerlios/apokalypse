
#ifndef SCREEN_H
#define SCREEN_H

#include "status.h"
#include <SDL.h>

class Screen : public CStatus{
public:
	Screen();
	virtual ~Screen();

	SDL_Surface *getScreen();
	SDL_Surface *getScreenSurface();
	void setBackground(SDL_Surface *bg);
	void update(int x = 0, int y = 0, int w = 0, int h = 0);
	int getWidth();
	int getHeight();
	bool getFullScreen();
	int getbpp();
	bool setVideoMode(int w, int h, int bpp, bool fs);

protected:

	SDL_Surface *screen;
	SDL_Surface *scaledbg;
	SDL_Surface *bkgnd;
	int width;
	int height;
	int bpp;
	bool fullscreen;
};


#endif


