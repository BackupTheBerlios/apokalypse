
#ifndef TCONFIGENTRY_H
#define TCONFIGENTRY_H

#include "tconfigitem.h"
#include "tconfig.h"

class TConfigEntry : public TConfigItem{
public:
	TConfigEntry(const TConfigEntry&);
	TConfigEntry(TConfig *cfg, const TString& section="" , const TString& name = "XXX", const TString& value = "");
	~TConfigEntry();

	const TString& getSection() const;
	virtual void setValue(const TString& value);
	virtual TConfigEntry& operator = (const TConfigEntry&);

protected:
	TString section;
	TConfig *cfg;
};

#endif

