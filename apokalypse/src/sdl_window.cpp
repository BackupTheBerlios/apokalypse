
#include "sdl_window.h"

SDL_Window::SDL_Window(Screen *screen, int flags = 0){
	SetClassName("SDL_Window");
	this->flags = flags;
	this->screen = screen;
	bkgnd = 0;
	scr = 0;
	visible = false;
	x = y = w = h = 0;
}

SDL_Window::~SDL_Window(){
	if (bkgnd)
		SDL_FreeSurface(bkgnd);
}

void SDL_Window::setGeometry(int x, int y, int w, int h){
	if (bkgnd){
		if (this->x != x || this->y != y || bkgnd->w != w ||
				bkgnd->h != h || !(flags & WND_SAVE_BKGND)){
			SDL_FreeSurface(bkgnd);
			bkgnd = 0;
			} else return;
		}

	if (!scr) scr = screen->getScreen();
	if (flags & WND_SAVE_BKGND){
		bkgnd = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, scr->format->BitsPerPixel,
			scr->format->Rmask, scr->format->Gmask, scr->format->Bmask, scr->format->Amask);
		SDL_Rect r,dest;
		r.x = x;
		r.y = y;
		r.w = w;
		r.h = h;
		/*dest.x = 0;
		dest.y = 0;
		dest.w = w;
		dest.h = h;*/
		SDL_BlitSurface(scr, &r, bkgnd, NULL);
		}
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

void SDL_Window::resize(int w, int h){
	if (bkgnd && bkgnd->w == w && bkgnd->h == h) return;
	if (bkgnd){
		SDL_FreeSurface(bkgnd);
		bkgnd = 0;
		}
	if (!scr) scr = screen->getScreen();
	if (flags & WND_SAVE_BKGND){
		bkgnd = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, scr->format->BitsPerPixel,
			scr->format->Rmask, scr->format->Gmask, scr->format->Bmask, scr->format->Amask);
		SDL_Rect r,dest;
		r.x = x;
		r.y = y;
		r.w = w;
		r.h = h;
		/*dest.x = 0;
		dest.y = 0;
		dest.w = w;
		dest.h = h;*/
		SDL_BlitSurface(scr, &r, bkgnd, NULL);
		}
	this->w = w;
	this->h = h;
}

void SDL_Window::show(bool s){
	if (s == visible) return;
	visible = s;
	update();
}

void SDL_Window::update(){
	if (!scr) scr = screen->getScreen();
	if ((flags & WND_SAVE_BKGND) && bkgnd){
		SDL_Rect r;
		r.x = x;
		r.y = y;
		r.w = w;
		r.h = h;
		SDL_BlitSurface(bkgnd, NULL, scr, &r);
		}
}

int SDL_Window::checkEvent(SDL_Event *event){
	return 0;
}

const TString& SDL_Window::getCaption(){
	return caption;
}

void SDL_Window::setCaption(const TString& caption){
	this->caption = caption;
}

void SDL_Window::setScreenChanged(){
	scr = 0;
	if (bkgnd) {
		SDL_FreeSurface(bkgnd);
		bkgnd = 0;
		}
}


