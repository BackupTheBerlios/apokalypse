
#include "tintentry.h"

TIntEntry::TIntEntry(const TConfigEntry& e)
	: TConfigEntry(e){
}

TIntEntry::TIntEntry(TConfig *cfg, const TString& section, const TString& name, int value)
	: TConfigEntry(cfg,section,name){
	setValue(TString().setNumber(value));
}

TIntEntry::~TIntEntry(){
}

int TIntEntry::getInt(int defval) const{
	bool ok;
	int val = getValue().toInt(&ok);
	if (ok) return val;
	return defval;
}

void TIntEntry::setInt(int value){
	setValue(TString().setNumber(value));
}



