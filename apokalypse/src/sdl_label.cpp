
#include "sdl_label.h"
#include "screen.h"
#include "logging.h"

SDL_Label::SDL_Label(Screen * screen, const TString &font, int fontsize) : SDL_Window(screen, WND_SAVE_BKGND){
	SetClassName("SDL_Label");
	this->font = new Font(font,fontsize);
	if (this->font->Status() != STATUS_OK){
		LogWarning("unable to load font.");
		delete this->font;
		this->font = 0;
		}
	align = LABEL_ALIGN_LEFT | LABEL_ALIGN_TOP;
	fontcolor = 0;
}

SDL_Label::~SDL_Label(){
	if (font) delete font;
}

void SDL_Label::update(){
	SDL_Window::update();

	if (visible){
		if (font){
			int tw,th,tx,ty;
			font->getSize(text,&tw,&th);
			switch (align & LABEL_ALIGN_HMASK){
				case LABEL_ALIGN_LEFT: tx=0;break;
				case LABEL_ALIGN_RIGHT: tx=w-tw;break;
				case LABEL_ALIGN_HCENTER: tx=(w-tw)/2;break;
				};
			switch (align & LABEL_ALIGN_VMASK){
				case LABEL_ALIGN_TOP: ty=0;break;
				case LABEL_ALIGN_BOTTOM: ty=h-th;break;
				case LABEL_ALIGN_VCENTER: ty=(h-th)/2;break;
				};
			font->printstr(x+tx,y+ty,text,screen->getScreenSurface());
			}
		}
	screen->update(x,y,w,h);
}

void SDL_Label::setColor(Uint8 r, Uint8 g, Uint8 b){
	if (font) font->setColor(r,g,b);
	fontcolor = SDL_MapRGB(screen->getScreenSurface()->format,r,g,b);
}

void SDL_Label::setAlign(int align){
	this->align=align;
}

const TString& SDL_Label::getText(){
	return text;
}

void SDL_Label::setText(const TString& t){
	text = t;
}

