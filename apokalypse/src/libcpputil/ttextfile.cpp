
#include "ttextfile.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define MAXLINESIZE 1024

TTextFile::TTextFile(TString path){
	this->path = path;
	loaded = false;
	clearErr();
}

TTextFile::TTextFile(){
	loaded = false;
	clearErr();
}

TTextFile::~TTextFile(){
}

void TTextFile::setPath(TString path){
	this->path = path;
	loaded = false;
}

TString TTextFile::getHomeDir(){
	const char* homedir = getenv("HOME");
	TString path;
	if (homedir) path = homedir;
	if (path[path.length()-1] != '/') path += "/";
	return path;
}

TString TTextFile::getErrString(int errcode){
	TString s = strerror(errcode);
	return s;
}

const TString& TTextFile::getPath() const{
	return path;
}

int TTextFile::save(TString path){
	setPath(path);
	return save();
}

int TTextFile::save(){
	FILE* f;
	if (!path.isEmpty()){
		f = fopen(path.text(),"w");
		if (!f){
			lasterr = errno;
			return lasterr;
			}
		}
		else
		f = stdout;

	for(TString *s = text.getFirst(); s != 0; s = text.getNext()){
		TString line = prepareLine();
		if (fwrite(line.text(),1,line.length(),f) != line.length()){
			lasterr = errno;
			fclose(f);
			return lasterr;
			}
		}

	if (f != stdout)
		fclose(f);
	loaded = true;
	lasterr = 0;
	return 0;
}

int TTextFile::load(TString path){
	setPath(path);
	return load();
}

int TTextFile::load(){
	loaded = false;
	text.clear();
	FILE* f;
	if (!path.isEmpty()){
		f = fopen(path.text(),"r");
		if (!f){
			lasterr = errno;
			return lasterr;
			}
		}
		else
		f = stdin;

	char curline[MAXLINESIZE];
	char *str;
	int len;
	TString line;
	while (!feof(f)){
		line = "";
		do{	str = fgets(curline,MAXLINESIZE,f);
			if (str) line += (const char*)str;
		}while (str && (len = strlen(str)) > 0 && str[len-1] != '\n');
		if (str || !line.isEmpty())
			appendLine(line.text());
		}
	if (f != stdin)
		fclose(f);
	loaded = true;
	lasterr = 0;
	return 0;
}

TList<TString> *TTextFile::getText(){
	if (!loaded) load();
	return &text;
}

TList<TString> *TTextFile::clearText(){
	loaded = false;
	text.clear();
	return &text;
}

void TTextFile::appendLine(const char* s){
	if (s){
		text << new TString(s);
		}
}

int TTextFile::lastError() const{
	return lasterr;
}

void TTextFile::clearErr(){
	lasterr = 0;
}

TString TTextFile::prepareLine(){
	TString line;
	TString *s = text.getCurrent();
	if (!s) return line;
	line = *s;
	return line;
}
