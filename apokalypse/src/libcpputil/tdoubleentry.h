
#ifndef TDOUBLEENTRY_H
#define TDOUBLEENTRY_H

#include "tconfig.h"
#include "tstring.h"
#include "tconfigentry.h"

class TDoubleEntry : public TConfigEntry{
public:
	TDoubleEntry(const TConfigEntry&);
	TDoubleEntry(TConfig *cfg, const TString& section="" , const TString& name = "XXX", double value = 0.0);
	~TDoubleEntry();

	double getDouble(double defval = 0.0);
	void setDouble(double value);
};

#endif

