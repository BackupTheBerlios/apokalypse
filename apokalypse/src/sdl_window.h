
#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include "status.h"
#include "screen.h"
#include <SDL.h>
#include "libcpputil/tstring.h"

class Screen;
typedef enum {
	WND_SAVE_BKGND = 1,
	WND_MOVEABLE = 2
} window_flags;

class SDL_Window: public CStatus{
public:
	SDL_Window(Screen *screen, int flags = 0);
	virtual ~SDL_Window();

	virtual void setGeometry(int x, int y, int w, int h);
	virtual void resize(int w, int h);
	virtual void show(bool s = true);
	virtual void update();
	virtual int checkEvent(SDL_Event *event);
	void setScreenChanged();
	const TString& getCaption();
	void setCaption(const TString& caption);

protected:
	Screen *screen;
	SDL_Surface *bkgnd;
	SDL_Surface *scr;
	TString caption;
	bool visible;
	int flags;
	int x,y,w,h;
};

#endif


