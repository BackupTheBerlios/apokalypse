
#include "intro.h"
#include "screen.h"
#include "logging.h"
#include "font.h"
#include "libcpputil/tlist.h"
#include "libcpputil/tstringentry.h"
#include "libcpputil/tintentry.h"
#include <SDL_timer.h>
#include <SDL_mixer.h>
#include "apokalypseapp.h"

//wie lange soll das intro laufen (ms)
#define INTRO_TIME 100000

Intro::Intro(Screen *screen) : CStatus(){
	SetClassName("Intro");
	this->screen = screen;
	if (!screen){
		LogWarning("No Screen");
		SetStatus(STATUS_ERROR);
		}
	textsurface = 0;
}

Intro::~Intro(){
	if (textsurface)
		SDL_FreeSurface(textsurface);
}

void Intro::run(){
	LogDebug("running Intro");
	LogDebug("hiding mouse");
	SDL_ShowCursor(0);

	Font font(TStringEntry(application->getDataConfig().getEntry("INTRO","font1")).getString().text(),
				TIntEntry(application->getDataConfig().getEntry("INTRO","font1_size")).getInt(24));
	if (font.Status() != STATUS_OK){
		LogWarning("unable to run intro without font.");
		SDL_ShowCursor(1); //im Fehlerfall brauch wir wieder einen Mauscursor
		return;
		}

	Mix_Music *music = 0;
	if (application->haveAudio())
		music = Mix_LoadMUS(TStringEntry(application->getDataConfig().getEntry("INTRO","music")).getString().text());
	if (!music){
		LogWarning("Could not load backgroundsound.");
		}else{
		Mix_PlayMusic(music,-1);
		}

	renderText(&font);
	SDL_SetColorKey(textsurface,SDL_SRCCOLORKEY,0);

	SDL_Surface *scr = screen->getScreen();
	Uint32 t0 = SDL_GetTicks();
	Uint32 t = t0;
	screen->update();
	for (int y= scr->h; y > -textsurface->h; y = scr->h-(((t-t0)*(scr->h+textsurface->h))/INTRO_TIME)){
		//blit the text
		SDL_Rect r;
		r.x = (scr->w-textsurface->w)/2;
		r.y = y;
		r.w = textsurface->w;
		r.h = textsurface->h;

		SDL_BlitSurface(textsurface, NULL, scr, &r);
		screen->update(r.x,0,textsurface->w,scr->h);
		scr = screen->getScreen();
		if (checkEvents() != 0) break;
		t = SDL_GetTicks();
		}
	screen->update();

	if (music){
		Mix_FadeOutMusic(1000);
		SDL_Delay(1000);
		Mix_FreeMusic(music);
		}

	LogDebug("showing Mouse");
	SDL_ShowCursor(1);
}

int Intro::checkEvents(){
	SDL_Event event;
	int res = 0;
	if (!SDL_PollEvent(&event)) return res;
	switch (event.type){
		case SDL_KEYDOWN:{
			Uint8 *keys = SDL_GetKeyState(NULL);
			if ( keys[SDLK_ESCAPE] == SDL_PRESSED ) {
				LogDebug("killing intro");
				res = 1;
				}
			}break;
		case SDL_QUIT: {
			LogDebug("Quit requested, killing intro.\n");
			res = -1;
			}break;
		};

	return res;
}

void Intro::renderText(Font *font){
	font->setColor(0,255,0);
	//calc number of lines
	TString text;
	FILE *f = fopen(TStringEntry(application->getDataConfig().getEntry("INTRO","text")).getString().text(),"r");
	if (!f){
		LogWarning("Could not load introtext");
		}else{
		char buf[1024];
		while (!feof(f)){
			text += (const char*)fgets(buf, 1024, f);
			}
		fclose(f);
		}
	text.stripWhiteSpace();
	TList<TString> lines;
	int i = 0, start;
	while (text[i] != 0){
		start = i;
		while (text[i] != '\n' && text[i] != 0){
			i++;
			}
		if (i > start){
			lines.append(new TString(text.first(i-start, start)));
			i++;
			}else if (text[i] != 0){
					lines.append(new TString(" "));
					i++;
					}
		}

	//calc Surface height and width
	int height = 0, width = 0,w,h;
	for (TString *s = lines.getFirst(); s != 0; s = lines.getNext()){
		font->getSize(*s,&w,&h);
		if (width < w) width = w;
		height += h;
		}

	//create Surface and blit text
	SDL_Surface *img = SDL_CreateRGBSurface(SDL_SWSURFACE|SDL_SRCALPHA, width, height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	textsurface = SDL_DisplayFormat(img);
	SDL_FreeSurface(img);
	int x = 0, y = 0;
	for (TString *s = lines.getFirst(); s != 0; s = lines.getNext()){
		font->getSize(*s,&w,&h);
		font->printstr(x,y,*s,textsurface);
		y += h;
		}
}

