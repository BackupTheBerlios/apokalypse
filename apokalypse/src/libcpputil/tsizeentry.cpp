
#include "tsizeentry.h"
#include "stdio.h"

TSizeEntry::TSizeEntry(const TConfigEntry& e)
	: TConfigEntry(e){
}

TSizeEntry::TSizeEntry(TConfig *cfg, const TString& section, const TString& name, int w, int h)
	: TConfigEntry(cfg,section,name){
	setValue("("+TString().setNumber(w)+","+TString().setNumber(h)+")");
}

TSizeEntry::~TSizeEntry(){
}

int TSizeEntry::getWidth(int defval) const{
	int w,h;
	if (sscanf(getValue().text(),"(%d,%d)",&w,&h) != 2) return defval;
	return w;
}

int TSizeEntry::getHeight(int defval) const{
	int w,h;
	if (sscanf(getValue().text(),"(%d,%d)",&w,&h) != 2) return defval;
	return h;
}

void TSizeEntry::setSize(int w, int h){
	setValue("("+TString().setNumber(w)+","+TString().setNumber(h)+")");
}



