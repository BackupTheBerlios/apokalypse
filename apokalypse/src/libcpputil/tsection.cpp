
#include "tsection.h"

#define PRECOMMENTSTRING "\t\t\t;"

TSection::TSection(const char* name = 0, const char* comment = 0){
	setName(name);
	setComment(comment);
}

TSection::TSection(const TString& name, const TString& comment){
	setName(name);
	setComment(comment);
}

TSection::~TSection(){
}

void TSection::setName(const char* name){
	this->name = name;
	this->name.stripWhiteSpace();
}

void TSection::setName(const TString& name){
	this->name = name;
	this->name.stripWhiteSpace();
}

TString TSection::getName() const{
	return name;
}

void TSection::setComment(const char* comment){
	this->comment = comment;
}

void TSection::setComment(const TString& comment){
	this->comment = comment;
}

TString TSection::getComment() const{
	return comment;
}

TString TSection::getString() const{
	TString str = "[" + name + "]";
	if (!comment.isEmpty()){
		str += PRECOMMENTSTRING + comment;
		}
	//in TConfigFile haben die Zeilen kein NewLine am Ende!
	//str += "\n";
	return str;
}

TList<TConfigItem>* TSection::itemList(){
	return &itemlist;
}

