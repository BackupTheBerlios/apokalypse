
#ifndef APOKALYPSEAPP_H
#define APOKALYPSEAPP_H

#include "status.h"
#include "libcpputil/tstring.h"
#include "libcpputil/tconfig.h"

class ApokalypseApp;
extern ApokalypseApp *application;

class Screen;

class ApokalypseApp : public CStatus{
public:
	ApokalypseApp();
	virtual ~ApokalypseApp();

	void readConfig(const TString &filename);
	void readDataConfig(const TString &filename);
	int init();
	int run();
	TConfig& getAppConfig();
	TConfig& getDataConfig();
	bool haveAudio();

protected:
	TString configfile;
	TConfig appconfig;
	TConfig dataconfig;
	Screen *screen;
	bool audiook;

	void saveConfig();

};

#endif

