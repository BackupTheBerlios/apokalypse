
#ifndef FONT_H
#define FONT_H
#include "status.h"
#include "libcpputil/tstring.h"
#include <SDL_ttf.h>

#define FONT_STYLE_NORMAL	0x00
#define FONT_STYLE_BOLD		0x01
#define FONT_STYLE_ITALIC	0x02
#define FONT_STYLE_UNDERLINE	0x04

class Font: public CStatus{
public:
	Font(const TString& filename, int pitch = 16);
	~Font();

	void getSize(const TString& str, int *w, int *h);
	void setColor(Uint8 r, Uint8 g, Uint8 b);
	void setStyle(int style);
	void printstr(int x, int y, const TString& str, SDL_Surface* dest);

protected:
	TTF_Font* font;
	SDL_Color color;
};

#endif


