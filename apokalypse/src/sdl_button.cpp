
#include "sdl_button.h"
#include "screen.h"
#include "apokalypseapp.h"
#include "libcpputil/tconfig.h"
#include "libcpputil/tstringentry.h"
#include "logging.h"
#include <SDL_image.h>

SDL_Button::SDL_Button(Screen * screen, const TString &datasection) : SDL_Window(screen, WND_SAVE_BKGND){
	normal = 0;
	active = 0;
	pressed = 0;
	sound_pressed = 0;
	sound_activated = 0;
	setCaption(datasection);

	normal = IMG_Load(TStringEntry(application->getDataConfig().getEntry(datasection,"normal")).getString().text());
	if (!normal){
		LogWarning("Could not load normal-image for %s",datasection.text());
		SetStatus(STATUS_ERROR);
		}
	active = IMG_Load(TStringEntry(application->getDataConfig().getEntry(datasection,"active")).getString().text());
	if (!active){
		LogWarning("Could not load active-image for %s",datasection.text());
		}
	pressed = IMG_Load(TStringEntry(application->getDataConfig().getEntry(datasection,"pressed")).getString().text());
	if (!pressed){
		LogWarning("Could not load pressed-image for %s",datasection.text());
		}

	sound_pressed = Mix_LoadMUS(TStringEntry(application->getDataConfig().getEntry(datasection,"sound_pressed")).getString().text());
	sound_activated = Mix_LoadMUS(TStringEntry(application->getDataConfig().getEntry(datasection,"sound_activated")).getString().text());

	isactive = false;
	ispressed = false;
}

SDL_Button::~SDL_Button(){
	if (normal) SDL_FreeSurface(normal);
	if (active) SDL_FreeSurface(active);
	if (pressed) SDL_FreeSurface(pressed);
	if (sound_pressed) Mix_FreeMusic(sound_pressed);
	if (sound_activated) Mix_FreeMusic(sound_activated);
}

void SDL_Button::update(){
	SDL_Window::update();

	//welches bild soll angezeigt werden?
	SDL_Surface *cursf = normal;
	if (isactive && active) cursf = active;
	if (ispressed){
		if (pressed)
			cursf = pressed;
			else
			if (active)
				cursf = active;
		}

	if (visible){
		SDL_Rect r;
		r.x = x + ((w - cursf->w)/2);
		r.y = y + ((h - cursf->h)/2);
		r.w = cursf->w;
		r.h = cursf->h;
		SDL_BlitSurface(cursf, NULL, scr, &r);
		}
	screen->update(x,y,w,h);
}

int SDL_Button::checkEvent(SDL_Event *event){
	int result = 0;
	switch (event->type){
		case SDL_MOUSEMOTION:{
			if (!isactive){
				if (event->motion.x >= x && event->motion.y >= y &&
					event->motion.x <= x+w && event->motion.y <= y+h){
					if (sound_activated) Mix_PlayMusic(sound_activated, 0);
					isactive = true;
					update();
					}
				}else{
				if (!(event->motion.x >= x && event->motion.y >= y &&
					event->motion.x <= x+w && event->motion.y <= y+h)){
					isactive = false;
					ispressed = false;
					update();
					}
				}
			}break;
		case SDL_MOUSEBUTTONDOWN:{
			if (isactive){ //pressed nur mit active möglich
				if (sound_pressed) Mix_PlayMusic(sound_pressed, 0);
				ispressed = true;
				update();
				}
			}break;
		case SDL_MOUSEBUTTONUP:{
			if (isactive){ //pressed nur mit active möglich
				if (ispressed) result = 1; //schalter wurde betätigt
				ispressed = false;
				update();
				}else{
				if (ispressed){
					ispressed = false;
					update();
					}
				}
			}break;
		};
	return result;
}


