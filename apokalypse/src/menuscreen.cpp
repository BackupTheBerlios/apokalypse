
#include "menuscreen.h"
#include "screen.h"
#include "logging.h"
#include "libcpputil/tlist.h"
#include "libcpputil/tstringentry.h"
#include "libcpputil/tintentry.h"
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include "apokalypseapp.h"
#include "sdl_button.h"
#include "sdl_label.h"
#include "sdl_lineedit.h"

MenuScreen::MenuScreen(Screen *screen){
	SetClassName("MenuScreen");
	this->screen = screen;
}

MenuScreen::~MenuScreen(){
}

int MenuScreen::run(){
	LogDebug("running MenuScreen");
	return run_main();
}

int MenuScreen::run_main(){
	int buttonwidth = 350;
	int buttonheight = 60;
	int main_numbuttons = 4;
	SDL_Button *bn_ng, *bn_lg, *bn_options, *bn_quit;
	//zum test, ob neuer videomodus gesetzt wurde
	long scrmode_index = screen->getWidth()*screen->getHeight()*screen->getbpp();

	int xstart = (screen->getWidth()-buttonwidth)/2;
	int ystart = (screen->getHeight() - main_numbuttons*buttonheight)/2;
	bn_ng = new SDL_Button(screen, "NEW_GAME_BUTTON");
	bn_ng->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	bn_lg = new SDL_Button(screen, "LOAD_GAME_BUTTON");
	bn_lg->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	bn_options = new SDL_Button(screen, "OPTIONS_BUTTON");
	bn_options->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	bn_quit = new SDL_Button(screen, "QUIT_BUTTON");
	bn_quit->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;

	bn_quit->show();
	bn_ng->show();
	bn_lg->show();
	bn_options->show();

	SDL_Event event;
	bool doexit = false;
	while ( !doexit ) {
		if (SDL_PollEvent(&event)){
			if (bn_ng->checkEvent(&event)){
				screen->getScreen(); //Hintergrund neu zeichnen
				screen->update(); //eventuell nichtaktive bildteile aktualisieren
				run_newgame();
				bn_quit->update();
				bn_ng->update();
				bn_lg->update();
				bn_options->update(); //buttons neu zeichnen
				}
			bn_lg->checkEvent(&event);
			if (bn_options->checkEvent(&event)){ //options anzeigen
				screen->getScreen(); //Hintergrund neu zeichnen
				screen->update(); //eventuell nichtaktive bildteile aktualisieren
				run_options();
				//mal sehen, ob neuer videomodus gesetzt wurde
				if (scrmode_index != screen->getWidth()*screen->getHeight()*screen->getbpp()){
					bn_ng->setScreenChanged();
					bn_lg->setScreenChanged();
					bn_options->setScreenChanged();
					bn_quit->setScreenChanged();
					xstart = (screen->getWidth()-buttonwidth)/2;
					ystart = (screen->getHeight() - main_numbuttons*buttonheight)/2;
					bn_ng->setGeometry(xstart,ystart,buttonwidth,buttonheight);
					ystart += buttonheight;
					bn_lg->setGeometry(xstart,ystart,buttonwidth,buttonheight);
					ystart += buttonheight;
					bn_options->setGeometry(xstart,ystart,buttonwidth,buttonheight);
					ystart += buttonheight;
					bn_quit->setGeometry(xstart,ystart,buttonwidth,buttonheight);
					scrmode_index = screen->getWidth()*screen->getHeight()*screen->getbpp();
					}
				bn_quit->update();
				bn_ng->update();
				bn_lg->update();
				bn_options->update(); //buttons neu zeichnen
				}
			if (bn_quit->checkEvent(&event)) doexit = true;
			switch (event.type){
				case SDL_QUIT: {
					LogDebug("Quit requested, quitting.\n");
					doexit = true;
					}break;
				};
			}else{
			}
		}

	delete bn_ng;
	delete bn_lg;
	delete bn_options;
	delete bn_quit;

	return 0;
}

int MenuScreen::run_newgame(){
	SDL_Label label(screen,"data/arial.ttf",24);
	label.setGeometry((screen->getWidth()/2)-150,screen->getHeight()/2-50,300,50);
	label.setColor(0,255,0);
	label.setText("Enter your name:");
	label.setAlign(LABEL_ALIGN_HCENTER|LABEL_ALIGN_VCENTER);

	SDL_LineEdit ed(screen,"data/arial.ttf",20,"data/lineedit.png");
	ed.setGeometry((screen->getWidth()/2)-150,screen->getHeight()/2,300,60);
	ed.setColor(0,255,0);
	ed.setText((const char*)getenv("USER"));
	label.show();
	ed.show();
	ed.setFocus(true);

	SDL_Event event;
	bool doexit = false;
	while (!doexit){
		if (!SDL_PollEvent(&event)){
			ed.checkEvent(0);
			continue;
			}
		ed.checkEvent(&event);
		switch (event.type){
			case SDL_KEYDOWN:{
				Uint8 *keys = SDL_GetKeyState(NULL);
				if ( keys[SDLK_ESCAPE] == SDL_PRESSED ) {
					doexit = true;
					}
				} break;
			};
		}

	//SDL_FreeSurface(panel);
	screen->getScreen(); //Hintergrund neu zeichnen
	screen->update(); //eventuell nichtaktive bildteile aktualisieren
	return 0;
}

int MenuScreen::run_options(){
	int buttonwidth = 350;
	int buttonheight = 60;
	int numbuttons = 4;
	SDL_Button *bn_video, *bn_audio, *bn_keyboard, *bn_back;
	long scrmode_index = screen->getWidth()*screen->getHeight()*screen->getbpp();

	int xstart = (screen->getWidth() - buttonwidth)/2;
	int ystart = (screen->getHeight() - numbuttons*buttonheight)/2;
	bn_video = new SDL_Button(screen, "VIDEO_BUTTON");
	bn_video->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	bn_audio = new SDL_Button(screen, "AUDIO_BUTTON");
	bn_audio->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	bn_keyboard = new SDL_Button(screen, "KEYBOARD_BUTTON");
	bn_keyboard->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	bn_back = new SDL_Button(screen, "BACK_BUTTON");
	bn_back->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;

	bn_back->show();
	bn_video->show();
	bn_audio->show();
	bn_keyboard->show();

	SDL_Event event;
	bool doexit = false;
	while ( !doexit ) {
		if (SDL_PollEvent(&event)){
			if (bn_video->checkEvent(&event)){ //options anzeigen
				screen->getScreen(); //Hintergrund neu zeichnen
				screen->update(); //eventuell nichtaktive bildteile aktualisieren
				run_options_video();
				//auf veränderten videomodus testen
				if (scrmode_index != screen->getWidth()*screen->getHeight()*screen->getbpp()){
					bn_video->setScreenChanged();
					bn_audio->setScreenChanged();
					bn_keyboard->setScreenChanged();
					bn_back->setScreenChanged();
					xstart = (screen->getWidth() - buttonwidth)/2;
					ystart = (screen->getHeight() - numbuttons*buttonheight)/2;
					bn_video->setGeometry(xstart,ystart,buttonwidth,buttonheight);
					ystart += buttonheight;
					bn_audio->setGeometry(xstart,ystart,buttonwidth,buttonheight);
					ystart += buttonheight;
					bn_keyboard->setGeometry(xstart,ystart,buttonwidth,buttonheight);
					ystart += buttonheight;
					bn_back->setGeometry(xstart,ystart,buttonwidth,buttonheight);
					scrmode_index = screen->getWidth()*screen->getHeight()*screen->getbpp();
					}
				bn_video->update();
				bn_audio->update();
				bn_keyboard->update();
				bn_back->update(); //...ebenso die buttons
				}
			bn_audio->checkEvent(&event);
			bn_keyboard->checkEvent(&event);
			if (bn_back->checkEvent(&event)) doexit = true;
			}else{
			}
		}

	delete bn_back;
	delete bn_video;
	delete bn_audio;
	delete bn_keyboard;

	screen->getScreen(); //Hintergrund neu zeichnen
	screen->update(); //eventuell nichtaktive bildteile aktualisieren
	return 0;
}

int MenuScreen::run_options_video(){
	int buttonwidth = 350;
	int buttonheight = 60;
	int numbuttons = 4;
	int scr_height = screen->getHeight();
	int scr_width = screen->getWidth();
	int scr_bpp = screen->getbpp();
	bool scr_fs = screen->getFullScreen();
	SDL_Button *bn_res, *bn_depth, *bn_display, *bn_ok, *bn_cancel;

	int xstart = (screen->getWidth() - buttonwidth)/2;
	int ystart = (screen->getHeight() - numbuttons*buttonheight)/2;
	bn_res = new SDL_Button(screen, "RESOLUTION_BUTTON");
	bn_res->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	bn_depth = new SDL_Button(screen, "DEPTH_BUTTON");
	bn_depth->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	bn_display = new SDL_Button(screen, "DISPLAY_BUTTON");
	bn_display->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;

	bn_ok = new SDL_Button(screen, "OK_BUTTON");
	bn_ok->setGeometry((screen->getWidth() - 500)/2,ystart,250,buttonheight);

	bn_cancel = new SDL_Button(screen, "CANCEL_BUTTON");
	bn_cancel->setGeometry(250+(screen->getWidth() - 500)/2,ystart,250,buttonheight);

	bn_res->show();
	bn_depth->show();
	bn_ok->show();
	bn_display->show();
	bn_cancel->show();

	SDL_Event event;
	bool doexit = false;
	while ( !doexit ) {
		if (SDL_PollEvent(&event)){
			if (bn_res->checkEvent(&event)){
				screen->getScreen(); //Hintergrund neu zeichnen
				screen->update(); //eventuell nichtaktive bildteile aktualisieren
				switch (run_options_video_res()){
					case 1: scr_width = 640; scr_height = 480; break;
					case 2: scr_width = 800; scr_height = 600; break;
					case 3: scr_width = 1024; scr_height = 768; break;
					};
				bn_res->update();
				bn_depth->update();
				bn_display->update();
				bn_ok->update();
				bn_cancel->update(); //...ebenso die buttons
				}
			if (bn_depth->checkEvent(&event)){
				screen->getScreen(); //Hintergrund neu zeichnen
				screen->update(); //eventuell nichtaktive bildteile aktualisieren
				switch (run_options_video_depth()){
					case 16: scr_bpp = 16; break;
					case 24: scr_bpp = 24; break;
					case 32: scr_bpp = 32; break;
					};
				bn_res->update();
				bn_depth->update();
				bn_display->update();
				bn_ok->update();
				bn_cancel->update(); //...ebenso die buttons
				}
			if (bn_display->checkEvent(&event)){
				screen->getScreen(); //Hintergrund neu zeichnen
				screen->update(); //eventuell nichtaktive bildteile aktualisieren
				switch (run_options_video_disp()){
					case 1: scr_fs = false; break;
					case 2: scr_fs = true; break;
					};
				bn_res->update();
				bn_depth->update();
				bn_display->update();
				bn_ok->update();
				bn_cancel->update(); //...ebenso die buttons
				}
			if (bn_cancel->checkEvent(&event)) doexit = true;
			if (bn_ok->checkEvent(&event)){
				screen->setVideoMode(scr_width, scr_height, scr_bpp, scr_fs);
				doexit = true;
				}
			}else{
			}
		}

	delete bn_res;
	delete bn_display;
	delete bn_depth;
	delete bn_ok;
	delete bn_cancel;

	screen->getScreen(); //Hintergrund neu zeichnen
	screen->update(); //eventuell nichtaktive bildteile aktualisieren
	return 0;
}

int MenuScreen::run_options_video_depth(){
	int buttonwidth = 350;
	int buttonheight = 60;
	int numbuttons = 3;

	int xstart = (screen->getWidth() - buttonwidth)/2;
	int ystart = (screen->getHeight() - numbuttons*buttonheight)/2;
	SDL_Button *bn_16 = new SDL_Button(screen, "16_BPP_BUTTON");
	bn_16->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	SDL_Button *bn_24 = new SDL_Button(screen, "24_BPP_BUTTON");
	bn_24->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	SDL_Button *bn_32 = new SDL_Button(screen, "32_BPP_BUTTON");
	bn_32->setGeometry(xstart,ystart,buttonwidth,buttonheight);

	bn_16->show();
	bn_24->show();
	bn_32->show();

	SDL_Event event;
	bool doexit = false;
	int res = 0;
	while ( !doexit ) {
		if (SDL_PollEvent(&event)){
			if (bn_16->checkEvent(&event)) res = 16;
			if (bn_24->checkEvent(&event)) res = 24;
			if (bn_32->checkEvent(&event)) res = 32;
			if (res) doexit = true;
			}else{
			}
		}

	delete bn_16;
	delete bn_24;
	delete bn_32;

	screen->getScreen(); //Hintergrund neu zeichnen
	screen->update(); //eventuell nichtaktive bildteile aktualisieren
	return res;
}

int MenuScreen::run_options_video_res(){
	int buttonwidth = 350;
	int buttonheight = 60;
	int numbuttons = 3;

	int xstart = (screen->getWidth() - buttonwidth)/2;
	int ystart = (screen->getHeight() - numbuttons*buttonheight)/2;
	SDL_Button *bn_640 = new SDL_Button(screen, "640X480_BUTTON");
	bn_640->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	SDL_Button *bn_800 = new SDL_Button(screen, "800X600_BUTTON");
	bn_800->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	SDL_Button *bn_1024 = new SDL_Button(screen, "1024X768_BUTTON");
	bn_1024->setGeometry(xstart,ystart,buttonwidth,buttonheight);

	bn_640->show();
	bn_800->show();
	bn_1024->show();

	SDL_Event event;
	bool doexit = false;
	int res = 0;
	while ( !doexit ) {
		if (SDL_PollEvent(&event)){
			if (bn_640->checkEvent(&event)) res = 1;
			if (bn_800->checkEvent(&event)) res = 2;
			if (bn_1024->checkEvent(&event)) res = 3;
			if (res) doexit = true;
			}else{
			}
		}

	delete bn_640;
	delete bn_800;
	delete bn_1024;

	screen->getScreen(); //Hintergrund neu zeichnen
	screen->update(); //eventuell nichtaktive bildteile aktualisieren
	return res;
}

int MenuScreen::run_options_video_disp(){
	int buttonwidth = 350;
	int buttonheight = 60;
	int numbuttons = 2;

	int xstart = (screen->getWidth() - buttonwidth)/2;
	int ystart = (screen->getHeight() - numbuttons*buttonheight)/2;
	SDL_Button *bn_win = new SDL_Button(screen, "WINDOWED_BUTTON");
	bn_win->setGeometry(xstart,ystart,buttonwidth,buttonheight);
	ystart += buttonheight;
	SDL_Button *bn_fs = new SDL_Button(screen, "FULLSCREEN_BUTTON");
	bn_fs->setGeometry(xstart,ystart,buttonwidth,buttonheight);

	bn_win->show();
	bn_fs->show();

	SDL_Event event;
	bool doexit = false;
	int res = 0;
	while ( !doexit ) {
		if (SDL_PollEvent(&event)){
			if (bn_win->checkEvent(&event)) res = 1;
			if (bn_fs->checkEvent(&event)) res = 2;
			if (res) doexit = true;
			}else{
			}
		}

	delete bn_win;
	delete bn_fs;

	screen->getScreen(); //Hintergrund neu zeichnen
	screen->update(); //eventuell nichtaktive bildteile aktualisieren
	return res;
}


