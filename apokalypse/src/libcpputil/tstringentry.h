
#ifndef TSTRINGENTRY_H
#define TSTRINGENTRY_H

#include "tconfig.h"
#include "tstring.h"
#include "tconfigentry.h"

class TStringEntry : public TConfigEntry{
public:
	TStringEntry(const TConfigEntry&);
	TStringEntry(TConfig *cfg, const TString& section="" , const TString& name = "XXX", const TString& value = "");
	~TStringEntry();

	const TString getString() const;
	void setString(const TString& value);
};

#endif

