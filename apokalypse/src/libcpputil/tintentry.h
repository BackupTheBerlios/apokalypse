
#ifndef TINTENTRY_H
#define TINTENTRY_H

#include "tconfig.h"
#include "tstring.h"
#include "tconfigentry.h"

class TIntEntry : public TConfigEntry{
public:
	TIntEntry(const TConfigEntry&);
	TIntEntry(TConfig *cfg, const TString& section="" , const TString& name = "XXX", int value = 0);
	~TIntEntry();

	int getInt(int defval = 0) const;
	void setInt(int value);
};

#endif

