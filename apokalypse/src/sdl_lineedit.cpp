
#include "sdl_lineedit.h"
#include "screen.h"
#include "logging.h"
#include <SDL_image.h>
#include <SDL_timer.h>


SDL_LineEdit::SDL_LineEdit(Screen *screen, const TString &font, int fontsize, const TString &imgfile)
	: SDL_Label(screen,font,fontsize){
	SetClassName("SDL_LineEdit");
	SDL_EnableUNICODE(true);
	fontheight = fontsize;
	img = IMG_Load(imgfile.text());
	if (!img){
		LogWarning("could not load image %s",imgfile.text());
		}
	cursorpos = 0;
	cursoron = false;
	havefocus = false;
	starttime = 0;
}

SDL_LineEdit::~SDL_LineEdit(){
	if (img){
		SDL_FreeSurface(img);
		}
}

void SDL_LineEdit::update(){
	SDL_Window::update();

	int tx=x,ty=y+((h-fontheight)/2);
	if (visible){
		if (img){
			SDL_Rect r;
			r.x = x+((w-img->w)/2);
			r.y = y+((h-img->h)/2);
			r.w = img->w;
			r.h = img->h;
			tx = r.x+((img->h-fontheight)/2);
			ty = r.y+((img->h-fontheight)/2);
			SDL_BlitSurface(img,NULL,screen->getScreenSurface(),&r);
			}
		if (font){
			font->printstr(tx,ty,text,screen->getScreenSurface());
			//jetzt noch den cursor malen
			if (cursoron){
				int th,tw;
				font->getSize(text.first(cursorpos).text(),&tw,&th);
				SDL_Rect r;
				r.x = tx + tw;
				r.y = ty;
				r.h = fontheight;
				r.w = 1; //nur ein senkrechter strich
				SDL_FillRect(screen->getScreenSurface(), &r, fontcolor);
				}
			}
		}
	screen->update(x,y,w,h);
}

void SDL_LineEdit::setFocus(bool focus){
	if (havefocus == focus) return;
	if (focus && !visible){
		LogWarning("SDL_LineEdit: can not get focus on invisible widget");
		return;
		}
	if (havefocus){
		cursoron = false;
		havefocus = false;
		}else{
		cursoron = true;
		havefocus = true;
		starttime = SDL_GetTicks();
		}
	update();
}

int SDL_LineEdit::checkEvent(SDL_Event *event){
	bool do_update = false;
	if (!visible || !havefocus) return 0;
	if (SDL_GetTicks()-starttime >= 500){
		starttime = SDL_GetTicks();
		cursoron = !cursoron;
		do_update = true;
		}

	if (event && event->type == SDL_KEYDOWN){
		switch (event->key.keysym.sym){
			case SDLK_LEFT: if (cursorpos > 0){
								cursorpos--;
								do_update = true;
								}break;
			case SDLK_RIGHT: if (cursorpos < text.length()){
								cursorpos++;
								do_update = true;
								}break;
			case SDLK_HOME:	cursorpos = 0;
							do_update = true;
							break;
			case SDLK_END:	cursorpos = text.length();
							do_update = true;
							break;
			case SDLK_BACKSPACE:
							if (cursorpos > 0){
								TString s = text.first(cursorpos-1);
								s += text.first(text.length(),cursorpos);
								text = s;
								cursorpos--;
								do_update = true;
								}
							break;
			case SDLK_DELETE:
							if (cursorpos < text.length()){
								TString s = text.first(cursorpos);
								s += text.first(text.length(),cursorpos+1);
								text = s;
								do_update = true;
								}
							break;
			case SDLK_RETURN:
			case SDLK_KP_ENTER: return 1;
			case SDLK_ESCAPE: return 2;
			default:{
					if ( (event->key.keysym.unicode & 0xFF80) == 0 &&
						(event->key.keysym.unicode & 0x7F) != 0 &&
						(event->key.keysym.unicode & 0x7F) >= ' ') {
						char ch[2];
						ch[1] = 0;
						ch[0] = event->key.keysym.unicode & 0x7F;
						TString s = text.first(cursorpos);
						s += (const char*) ch;
						s += text.first(text.length(),cursorpos);
						//prüfen, ob der text noch in die box passt
						if (font && img){
							int tw,th;
							font->getSize(s.text(),&tw,&th);
							if (tw <= img->w-(img->h-fontheight)){//rand soll auch noch bleiben
								text = s;
								cursorpos++;
								}
							}else{
							text = s;
							cursorpos++;
							}
						do_update = true;
						}
					}break;
			};
		}

	if (do_update) update();
	return 0;
}


