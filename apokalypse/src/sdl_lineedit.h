
#ifndef SDL_LINEEDIT_H
#define SDL_LINEEDIT_H

#include "sdl_label.h"

class SDL_LineEdit: public SDL_Label{
public:
	SDL_LineEdit(Screen *screen, const TString &font, int fontsize, const TString &imgfile);
	virtual ~SDL_LineEdit();
	virtual void update();
	virtual void setFocus(bool focus);
	virtual int checkEvent(SDL_Event *event);
protected:
	SDL_Surface* img;
	int fontheight;
	int cursorpos;
	bool cursoron; //blinkender cursor
	long starttime;
	bool havefocus;
};

#endif

