
#ifndef TVECTORENTRY_H
#define TVECTORENTRY_H

#include "tconfig.h"
#include "tstring.h"
#include "tconfigentry.h"

class TVectorEntry : public TConfigEntry{
public:
	TVectorEntry(const TConfigEntry&);
	TVectorEntry(TConfig *cfg, const TString& section="" , const TString& name = "XXX", const TString& value = "()");
	~TVectorEntry();

	int getVector(int n, TConfigEntry* entrys[]) const;
	void setVector(int n, TConfigEntry* entrys[]);

};

#endif

