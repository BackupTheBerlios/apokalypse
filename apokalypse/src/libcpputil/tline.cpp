
#include "tline.h"

TLine::TLine(const char* text = 0, TLine *prev = 0, TLine *next = 0){
	data = "";
	if (text) setText(text);
	this->prev = prev;
	this->next = next;
	isparsed = false;
}

TLine::TLine(TString& s, TLine *prev = 0, TLine *next = 0){
	data = s;
	this->prev = prev;
	this->next = next;
	isparsed = false;
}

TLine::~TLine(){
}

void TLine::setText(const char* text){
	isparsed = false;
	if (text) data = text;
		else data = "";
}

void TLine::setText(TString& text){
	isparsed = false;
	data = text;
}

const char* TLine::getText() const{
	return data.text();
}

TLine* TLine::getPrev() const{
	return prev;
}

TLine* TLine::getNext() const{
	return next;
}

void TLine::setNext(TLine* next){
	this->next = next;
}

void TLine::setPrev(TLine* prev){
	this->prev = prev;
}

void TLine::parse(){
}


