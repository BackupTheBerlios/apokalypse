
#include "tboolentry.h"

TBoolEntry::TBoolEntry(const TConfigEntry& e)
	: TConfigEntry(e){
}

TBoolEntry::TBoolEntry(TConfig *cfg, const TString& section, const TString& name, bool value)
	: TConfigEntry(cfg,section,name){
	setValue(TString().setNumber(value));
}

TBoolEntry::~TBoolEntry(){
}

bool TBoolEntry::getBool(bool defval){
	TString s = strLower(getValue());
	if (defval){
		if (s == "false") return false;
		if (s == "no") return false;
		}else{
		if (s == "true") return true;
		if (s == "yes") return true;
		}
	return defval;
}

void TBoolEntry::setBool(bool value){
	if (value)
		setValue("true");
		else
		setValue("false");
}


