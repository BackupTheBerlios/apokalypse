
#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "status.h"

class Screen;

class MenuScreen: public CStatus{
public:
	MenuScreen(Screen *screen);
	virtual ~MenuScreen();

	int run();

protected:
	int run_main();
	int run_newgame();
	int run_options();
	int run_options_video();
	int run_options_video_res();
	int run_options_video_depth();
	int run_options_video_disp();

	Screen *screen;
};

#endif

