
#include "font.h"
#include "logging.h"
#include <SDL.h>

bool ttf_initialized = false;


Font::Font(const TString& filename, int pitch) : CStatus(){
	SetClassName("Font");
	font = 0;
	if (!ttf_initialized)
		if (TTF_Init() != 0){
			SetStatus(STATUS_ERROR);
			LogWarning("Could not initialize libSDL_ttf");
			return;
			}
	ttf_initialized = true;

	font = TTF_OpenFont(filename.text(),pitch);
	if (!font){
			SetStatus(STATUS_ERROR);
			LogWarning("Could not load font %s",filename.text());
			return;
			}

	setColor(255,255,255);
}

Font::~Font(){
	if (font)
		TTF_CloseFont(font);
}

void Font::getSize(const TString& str, int *w, int *h){
	TTF_SizeText(font, str.text(), w, h);
}

void Font::printstr(int x, int y, const TString& str, SDL_Surface* dest){
	if (str.isEmpty()) return;
	
	SDL_Surface *text = TTF_RenderText_Solid(font,str.text(), color);
	SDL_Surface *src = SDL_DisplayFormat(text);
	if(!src) {
		LogDebug("Cant convert Text to Displayformant.");
		src = text;
	} else {
		SDL_FreeSurface(text);
	}

	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = src->w;
	r.h = src->h;

	SDL_BlitSurface(src, NULL, dest, &r);
	SDL_FreeSurface(src);
}

void Font::setColor(Uint8 r, Uint8 g, Uint8 b){
	color.r = r;
	color.g = g;
	color.b = b;
	color.unused = 255;
}

void Font::setStyle(int style){
	TTF_SetFontStyle(font,style);
}


