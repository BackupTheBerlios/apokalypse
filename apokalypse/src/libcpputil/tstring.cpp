
#include <string.h>
#include <stdlib.h>
#include "tstring.h"
#include "utils.h"

TString::TString(){
	data = 0;
}

TString::TString(const char* text){
	data = 0;
	setText(text);
}

TString::TString(const TString &s){
	data = 0;
	setText(s.text());
}

TString::~TString(){
	if (data)
		free(data);
}

const char* TString::text() const{
	if (data) return data;
	return "";
}

int TString::length() const{
	if (!data) return 0;
	return strlen(data);
}

bool TString::isEmpty() const{
	return ((data == 0) || (data[0] == 0));
}

TString TString::first(int n, int startpos) const{
	TString str;
	if (!data || n <= 0 || startpos < 0 || startpos >= length()) return str;
	int mylen = length() - startpos;
	char *dummy = (char*)malloc(MIN(n,mylen)+1);
	if (dummy){
		strncpy(dummy,text()+startpos,MIN(n,mylen));
		dummy[MIN(n,mylen)] = 0;
		str = (const char*)dummy;
		free(dummy);
		}
	return str;
}

TString TString::last(int n) const{
	TString str;
	if (!data || n <= 0) return str;
	int mylen = length();
	char *dummy = (char*)malloc(MIN(n,mylen)+1);
	if (dummy){
		if (n<length())
			strcpy(dummy,text()+(mylen-n));else
			strcpy(dummy,text());
		str = (const char*)dummy;
		free(dummy);
		}
	return str;
}

void TString::setText(const char* text){
	if (data) free(data);
	data = 0;
	if (text && text[0] != 0){
		data = (char*)malloc(strlen(text)+1);
		if (data)
			strcpy(data,text);
		}
}

char TString::operator[](int i) const{
	if (i < 0) return 0;
	return data[i];
}

TString& TString::stripWhiteSpace(){
	int i = 0;
	unsigned char curchar;
	if (!data || data[0] == 0) return *this;
	while ((curchar = ((unsigned char*)data)[i]) <= ' ' && curchar != 0) i++;

	if (curchar == 0){ //nothing but spaces
		setText("");
		return *this;
		}

	if (i != 0) setText(last(length()-i).text());
	i = length();
	do{
		data[i] = 0;
		i--;
	}while (((unsigned char*)data)[i] <= ' ');
	return *this;
}

TString& TString::operator = (const TString& s){
	setText(s.text());
	return *this;
}

TString& TString::operator = (const char* s){
	setText(s);
	return *this;
}

TString& TString::operator += (const TString& s){
	if (data){
		char* dummy = (char*)malloc(length()+s.length()+1);
		if (dummy){
			strcpy(dummy,data);
			strcat(dummy,s.text());
			free(data);
			data = dummy;
			}
		}else setText(s.text());
	return *this;
}

TString& TString::operator += (const char* s){
	if (!s || s[0] == 0) return *this;
	if (data){
		char* dummy = (char*)malloc(length()+strlen(s)+1);
		if (dummy){
			strcpy(dummy,data);
			strcat(dummy,s);
			free(data);
			data = dummy;
			}
		}else setText(s);
	return *this;
}

TString& TString::setNumber(int i){
	char buffer[100];
	sprintf(buffer,"%d",i);
	setText(buffer);
	return *this;
}

TString& TString::setNumber(double d, char mod, unsigned int prec){
	char buffer[100];
	char dummy[100];
	sprintf(dummy,"%%.%d%c",prec,mod);
	sprintf(buffer,dummy,d);
	setText(buffer);
	return *this;
}

int TString::toInt(bool *ok, int base){
	char *endp = 0;
	if (isEmpty()){
		if (ok) *ok = false;
		return 0;
		}
	int i = strtol(text(),&endp,base);
	if (ok) *ok=false;
	if (endp && *endp == 0 && ok) *ok = true;
	return i;
}

double TString::toDouble(bool *ok){
	char *endp = 0;
	if (isEmpty()){
		if (ok) *ok = false;
		return 0.0;
		}
	double d = strtod(text(),&endp);
	if (ok) *ok=false;
	if (endp && *endp == 0 && ok) *ok = true;
	return d;
}



TString strUpper(const TString& s){
	TString str = "";
	if (s.isEmpty()) return str;

	char* dummy = (char*)malloc(s.length()+1);
	if (!dummy) return str = s;
	for (int i = 0; i <= s.length(); i++){
		dummy[i] = upperChar(s[i]);
		}
	str = (const char*)dummy;
	free(dummy);
	return str;
}

TString strLower(const TString& s){
	TString str = "";
	if (s.isEmpty()) return str;

	char* dummy = (char*)malloc(s.length()+1);
	if (!dummy) return str = s;
	for (int i = 0; i <= s.length(); i++){
		dummy[i] = lowerChar(s[i]);
		}
	str = (const char*)dummy;
	free(dummy);
	return str;
}

char upperChar(char c){
	if (c >= 'a' && c <= 'z')
		return c-'a'+'A';
	return c;
}

char lowerChar(char c){
	if (c >= 'A' && c <= 'Z')
		return c-'A'+'a';
	return c;
}

TString operator + (const TString& s1, const char* s){
	TString str(s1);
	if (s) str += s;
	return str;
}

TString operator + (const TString& s1, const TString& s){
	TString str(s1);
	str += s;
	return str;
}

TString operator + (const char* s1, TString &s2){
	TString str(s1);
	str += s2;
	return str;
}

bool operator == (const TString& s1, const TString& s2){
	return strcmp(s1.text(),s2.text()) == 0;
}

bool operator == (const TString& s1, const char* s2){
	return strcmp(s1.text(),s2) == 0;
}

bool operator == (const char* s1, TString& s2){
	return strcmp(s1,s2.text()) == 0;
}

bool operator != (const TString& s1, const TString& s2){
	return strcmp(s1.text(),s2.text()) != 0;
}

bool operator != (const TString& s1, const char* s2){
	return strcmp(s1.text(),s2) != 0;
}

bool operator != (const char* s1, TString& s2){
	return strcmp(s1,s2.text()) != 0;
}



