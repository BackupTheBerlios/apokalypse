
#ifndef TBOOLENTRY_H
#define TBOOLENTRY_H

#include "tconfig.h"
#include "tstring.h"
#include "tconfigentry.h"

class TBoolEntry : public TConfigEntry{
public:
	TBoolEntry(const TConfigEntry&);
	TBoolEntry(TConfig *cfg, const TString& section="" , const TString& name = "XXX", bool value = false);
	~TBoolEntry();

	bool getBool(bool defval = false);
	void setBool(bool value);
};

#endif

