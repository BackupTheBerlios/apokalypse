
#include "tdoubleentry.h"

TDoubleEntry::TDoubleEntry(const TConfigEntry& e)
	: TConfigEntry(e){
}

TDoubleEntry::TDoubleEntry(TConfig *cfg, const TString& section, const TString& name, double value)
	: TConfigEntry(cfg,section,name){
	setValue(TString().setNumber(value));
}

TDoubleEntry::~TDoubleEntry(){
}

double TDoubleEntry::getDouble(double defval){
	bool ok;
	double val = getValue().toDouble(&ok);
	if (ok) return val;
	return defval;
}

void TDoubleEntry::setDouble(double value){
	setValue(TString().setNumber(value));
}


