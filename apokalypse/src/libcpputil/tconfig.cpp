
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tconfig.h"
#include "tconfigstring.h"
#include "tconfigentry.h"

TConfig::TConfig(){
}

TConfig::TConfig(const TConfigFile&){
}

TConfig::~TConfig(){
}

void TConfig::operator << (TConfigFile& cf){
	sectionlist.clear();
	sectionlist << new TSection("");
	TConfigString cs;
	TSection *section = sectionlist.getFirst();

	for (TString *s = cf.getText()->getFirst(); s != 0; s = cf.getText()->getNext()){
		cs.parse(*s);
		if (cs.isSection()){
			section = findSection(cs.getName());
			if (!section){ //Sektion ex. nicht --> erzeugen
				section = sectionlist << new TSection(cs.getName(),cs.getComment());
				}else{//eventuellen Kommentar hinzufügen
				if (cs.hasComment())
					section->setComment(section->getComment() + "," + cs.getComment());
				}
			}else{
			//wir verarbeiten auch Leerzeilen als Items
			section->itemList()->append(new TConfigItem(cs.getName(),cs.getValue(),cs.getComment()));
			}
		}
}

void TConfig::operator >> (TConfigFile& cf){
	TList<TString> *cflist = cf.clearText();
	//die erste Section ("[]") separat behandeln
	TSection *section = sectionlist.getFirst();
	for (TConfigItem *item = section->itemList()->getFirst(); item != 0; item = section->itemList()->getNext()){
		cflist->append(new TString(item->getString().text()));
		}
	//jetzt kommen alle anderen
	for (section = sectionlist.getNext(); section != 0; section = sectionlist.getNext()){
		cflist->append(new TString(section->getString().text()));
		for (TConfigItem *item = section->itemList()->getFirst(); item != 0; item = section->itemList()->getNext()){
			cflist->append(new TString(item->getString().text()));
			}
		}
	cf.save();
}

void TConfig::print(){
	for (TSection *section = sectionlist.getFirst(); section != 0; section = sectionlist.getNext()){
		printf("%s\n",section->getString().text());
		for (TConfigItem *item = section->itemList()->getFirst(); item != 0; item = section->itemList()->getNext()){
			printf("%s\n",item->getString().text());
			}
		}
}

TSection* TConfig::findSection(const TString& name){
	//evtl. von aktueller Section beginnen
	if (sectionlist.getCurrent()){
		TSection *oldcuritem = sectionlist.getCurrent();
		//Liste beginnend von aktuellem durchsuchen
		for (TSection *s = sectionlist.getCurrent(); s != 0; s = sectionlist.getNext()){
			if (s->getName() == name) return s;
			}
		//nicht gefunden --> nochmal vom Anfang bis max oldcuritem suchen
		for (TSection *s = sectionlist.getFirst(); s != 0 && s != oldcuritem; s = sectionlist.getNext()){
			if (s->getName() == name) return s;
			}
		return 0; //nicht gefunden
		}

	for (TSection* s=sectionlist.getFirst(); s != 0; s = sectionlist.getNext())
		if (s->getName() == name) return s;
	return 0;
}

TConfigItem* TConfig::findEntry(const TString& e){
	if (!sectionlist.getCurrent()) return 0;

	TList<TConfigItem> *il = sectionlist.getCurrent()->itemList();
	if (!il->getCurrent()){
		for (TConfigItem *i = il->getFirst(); i != 0; i = il->getNext()){
			if (i->getName() == e) return i;
			}
		return 0; //nicht gefunden
		}

	TConfigItem *oldcuritem = il->getCurrent();
	//Liste beginnend von aktuellem durchsuchen
	for (TConfigItem *i = il->getCurrent(); i != 0; i = il->getNext()){
		if (i->getName() == e) return i;
		}
	//nicht gefunden --> nochmal vom Anfang bis max oldcuritem suchen
	for (TConfigItem *i = il->getFirst(); i != 0 && i != oldcuritem; i = il->getNext()){
		if (i->getName() == e) return i;
		}
	return 0; //nicht gefunden
}

TConfigItem* TConfig::getItem(const TString& name){
	if (!sectionlist.getCurrent()) findSection("");
	return findEntry(name);
}

TConfigItem* TConfig::getItem(const TString& section, const TString& name){
	if (findSection(section))
		return findEntry(name);
	return 0;
}

TSection* TConfig::setSection(const TString& section){
	return findSection(section);
}

TConfigEntry TConfig::getEntry(const TString& name){
	TString section = "";
	TConfigItem *i = getItem(name);
	if (!sectionlist.getCurrent())
		findSection("");
		else
		section=sectionlist.getCurrent()->getName();
	if (i){
		TConfigEntry entry(this,section,name,i->getValue());
		entry.setComment(i->getComment());
		return entry;
		}
	TConfigEntry entry(this,section,name);
	return entry;
}

TConfigEntry TConfig::getEntry(const TString& section, const TString& name){
	TConfigItem *i = getItem(section,name);
	if (i){
		TConfigEntry entry(this,section,name,i->getValue());
		entry.setComment(i->getComment());
		return entry;
		}
	TConfigEntry entry(this,section,name);
	return entry;
}

void TConfig::setEntry(const TConfigEntry& entry){
	TSection *s = findSection(entry.getSection());
	if (!s){
		s = (sectionlist << new TSection(entry.getSection(),""));
		s->itemList()->append(new TConfigItem(entry.getName(),entry.getValue(),entry.getComment()));
		}else{
		TConfigItem *i = findEntry(entry.getName());
		if (!i){
			s->itemList()->prepend(new TConfigItem(entry.getName(),entry.getValue(),entry.getComment()));
			}else{
			i->setValue(entry.getValue());
			i->setComment(entry.getComment());
			}
		}
}




