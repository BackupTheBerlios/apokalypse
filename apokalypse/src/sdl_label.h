
#ifndef SDL_LABEL_H
#define SDL_LABEL_H

#include "sdl_window.h"
#include "libcpputil/tstring.h"
#include <SDL.h>
#include <font.h>

typedef enum{
	LABEL_ALIGN_LEFT=1,
	LABEL_ALIGN_RIGHT=2,
	LABEL_ALIGN_HCENTER=3,
	LABEL_ALIGN_HMASK=3,
	LABEL_ALIGN_TOP=4,
	LABEL_ALIGN_BOTTOM=8,
	LABEL_ALIGN_VCENTER=12,
	LABEL_ALIGN_VMASK=12
} Label_Align;

class SDL_Label: public SDL_Window{
public:
	SDL_Label(Screen *screen, const TString &font, int fontsize);
	virtual ~SDL_Label();
	virtual void update();
	void setColor(Uint8 r, Uint8 g, Uint8 b);
	void setAlign(int align);
	const TString& getText();
	void setText(const TString& t);
protected:
	TString text;
	Font *font;
	int align;
	Uint32 fontcolor;
};

#endif



