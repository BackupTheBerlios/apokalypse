
#include "tconfigitem.h"

#define PRECOMMENTSTRING "\t;"

TConfigItem::TConfigItem(const char* name = 0, const char* value = 0, const char* comment = 0){
	setName(name);
	setValue(value);
	setComment(comment);
}

TConfigItem::TConfigItem(const TString& name, const TString& value, const TString& comment){
	setName(name);
	setValue(value);
	setComment(comment);
}

TConfigItem::~TConfigItem(){
}

void TConfigItem::setName(const char* name){
	this->name = name;
	this->name.stripWhiteSpace();
}

void TConfigItem::setName(const TString& name){
	this->name = name;
	this->name.stripWhiteSpace();
}

TString TConfigItem::getName() const{
	return name;
}

void TConfigItem::setComment(const char* comment){
	this->comment = comment;
}

void TConfigItem::setComment(const TString& comment){
	this->comment = comment;
}

TString TConfigItem::getComment() const{
	return comment;
}

void TConfigItem::setValue(const char* value){
	this->value = value;
	this->value.stripWhiteSpace();
}

void TConfigItem::setValue(const TString& value){
	this->value = value;
	this->value.stripWhiteSpace();
}

TString TConfigItem::getValue() const{
	return value;
}

TString TConfigItem::getString() const{
	TString str;
	if (!name.isEmpty()){
		str = name + " = " + value;
		if (!comment.isEmpty()){
			str += PRECOMMENTSTRING + comment;
			}
		}else
		if (!comment.isEmpty()){
			str = "#" + comment;
			}
	//in TConfigFile haben die Zeilen kein NewLine am Ende!
	//str += "\n";
	return str;
}


