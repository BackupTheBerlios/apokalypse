
#include "tconfigentry.h"

TConfigEntry::TConfigEntry(const TConfigEntry& entry)
	: TConfigItem(entry.getName(),entry.getValue(),entry.getComment()){
	section = entry.section;
	cfg = entry.cfg;
}

TConfigEntry::TConfigEntry(TConfig *cfg, const TString& section, const TString& name, const TString& value)
	: TConfigItem(name,value,""){
	this->section = section;
	this->cfg = cfg;
}

TConfigEntry::~TConfigEntry(){
}

const TString& TConfigEntry::getSection() const{
	return section;
}

void TConfigEntry::setValue(const TString& value){
	TConfigItem::setValue(value);
	if (cfg) cfg->setEntry(*this);
}

TConfigEntry& TConfigEntry::operator = (const TConfigEntry& e){
	setName(e.getName());
	setValue(e.getValue());
	setComment(e.getComment());
	section = e.getSection();
	cfg = e.cfg;
	return *this;
}
