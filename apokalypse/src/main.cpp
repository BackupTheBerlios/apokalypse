/*
   Apokalypse
   Copyright (C) 2002

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   file COPYING for details.
*/

#include <iostream.h>
#include <string.h>
#include "apokalypseapp.h"
#include "libcpputil/tconfigfile.h"
#include "libcpputil/tstring.h"

int ParseCmdLine(int argc, char *argv[]) {
	// When no args passed - simply return success
	if(argc < 2) return(1);

	if(argc == 2) {
		if(strcmp(argv[1], "--version") == 0) {
			cout << "Apokalypse 0.1\n";
			cout << "\nWARNING: This Program is Alpha. Use on your own Risk.\n\n";
			return(0);
		} else {
			cout << "Usage: apokalypse [--help|--version]\n";
			cout << "\n";
			cout << "--help     \tShows Help (this Message).\n";
			cout << "--version  \tShows the Version of Apokalypse.\n";
			cout << "\n";

			// Return 0 to shutdown the Program
			return(0);
		}
	}

	// If we are here - return success
	return(1);
}

int main (int argc, char* argv[]) {
	if(!ParseCmdLine(argc, argv)) {
		return(0);
	}

	ApokalypseApp app;
	int result = -1;

#ifndef __win32__
	app.readConfig(TConfigFile::getHomeDir()+".apokalypserc");
#else
	app.readConfig("C:\\eigene dateien\\apokalypse\\apokalypserc");
#endif

	app.readDataConfig("data/data.conf");
	app.init();

	if (app.Status() == STATUS_OK)
		result = app.run();

	return result;
}

