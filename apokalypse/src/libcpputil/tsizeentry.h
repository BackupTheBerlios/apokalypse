
#ifndef TSIZEENTRY_H
#define TSIZEENTRY_H

#include "tconfig.h"
#include "tstring.h"
#include "tconfigentry.h"

class TSizeEntry : public TConfigEntry{
public:
	TSizeEntry(const TConfigEntry&);
	TSizeEntry(TConfig *cfg, const TString& section="" , const TString& name = "XXX", int w = 0, int h = 0);
	~TSizeEntry();

	int getWidth(int defval = 0) const;
	int getHeight(int defval = 0) const;
	void setSize(int w, int h);
};

#endif

