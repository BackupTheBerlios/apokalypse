
#include "tconfigstring.h"
#ifdef __DEBUG__
#include <stdio.h>
#include <string.h>
#endif

void debugprint(const char* s){
#ifdef __DEBUG__
	printf(s);
#endif
}

TConfigString::TConfigString(){
	name = "";
	value = "";
	comment = "";
}

TConfigString::TConfigString(const char* text){
	name = "";
	value = "";
	comment = "";
	parse(text);
}

TConfigString::TConfigString(const TString &s){
	name = "";
	value = "";
	comment = "";
	parse(s);
}

TConfigString::~TConfigString(){
}

const TString TConfigString::getName(){
	return name;
}

const TString TConfigString::getValue(){
	return value;
}

const TString TConfigString::getComment(){
	return comment;
}

bool TConfigString::isComment() const{
	return (!comment.isEmpty() && name.isEmpty() && !isasection);
	//wenn kein name ex. kann auch kein value ex.
}

bool TConfigString::isSection() const{
	return isasection;
}

bool TConfigString::hasComment() const{
	return !comment.isEmpty();
}

bool TConfigString::isItem() const{
	return !(isasection || name.isEmpty());
}

void TConfigString::parse(const TString &s){
	data = (const unsigned char*)s.text();
	parse();
	data = 0;
}

void TConfigString::parse(const char* s){
	data = (const unsigned char*)s;
	parse();
	data = 0;
}

void TConfigString::parse(){
	debugprint("parse()\n");
	isasection = false;
	name = "";
	value = "";
	comment = "";
	if (data){
		int i = 0;
		if (data[0] == '#'){ //nur wenn an erster stelle ein # steht ist's ein kommentar
			parsecomment(1);
			return;
			}
		while (data[i] <= ' ' && data[i] != 0) i++;
		if (data[i] == 0) return;
		switch (data[i]){
			case '[': parsesection(i); break;
			case ';': parsecomment(i+1); break;
			default: parseitem(i); break;
			};
		}
}

void TConfigString::parsesection(int i){
	//data ist nicht null!!! und i >= 0, data[i] = '['
	debugprint("parsesection()\n");
	int j = i+1;
	int k,x;
	while (data[j] <= ' ' && data[j] != 0) j++;
	if (data[j] == 0) return;
	//bei j startet der sektionname
	x = j;
	while (data[x] != ']' && data[x] != 0) x++;
	if (data[x] == 0){ //interpretiere als kommentar falls falsch formatiert
		parsecomment(0); //wir wollen den gesamten string als kommentar
		return;
		}
	k = x-1; //am ende beginnen
	isasection = true; //wir wollen auch "[]" als section interpretieren
	while (data[k] <= ' ') k--;
	if (j > k){ //ein zeichen sollte schon drin sein
		parsecomment(x+1); //wir wollen den reststring als kommentar
		return;
		}
	x++;
	while (data[x] <= ' ' && data[x] != 0) x++;
	if (data[x] != 0)
		if (data[x] == ';') parsecomment(x+1);
			else parsecomment(x);
	name = (const char*)data;
	name = name.first(k-j+1,j);
}

void TConfigString::parsecomment(int i){
	//data,data[i] ist nicht null!!! und i >= 0
	//der gesamte string ab data[i] ist kommentar
	debugprint("parsecomment()\n");
	if (data[i])
		comment.setText((const char*)data+i);
}

void TConfigString::parseitem(int i){
	//data,data[i] ist nicht null!!! und i >= 0
	//suche ein '='...
	debugprint("parseitem()\n");
	int k = i;
	int j;
	int mode = 0;
	while (data[k] != '=' && data[k] != 0) k++;
	if (data[k] == 0){
		parsecomment(i);
		return;
		}
	j = k;
	j--;
	while (data[j] <= ' ') j--; //zum ende des namens gehen
	name = (const char*)data;
	name = name.first(j-i+1,i);
	i = k+1; //zum anfang der value gehen
	while (data[i] <= ' ' && data[i] != 0) i++;
	if (data[i] == 0) return; //value ist null
	if (data[i] == ';'){ //hier startet ein kommentar, value ist null
		parsecomment(i+1);
		return;
		}
	//data[i] ist jetzt anfang des strings, ende ist ';' oder null
	k = i;
	switch(data[i]){
		case '"':	mode=1;break;//formatierter string
		case '(':	if (parsevektor(i))
					{mode=2;return;}else mode=0;break;//vektor
		default:	mode=0;break;//zahl oder unformatierter string
		};

	if (mode == 0){ //ist's ein formatierter string oder ein vektor?
		while (data[k] != ';' && data[k] != 0) k++;
		if (data[k] == ';') parsecomment(k+1);
		k--;
		while (data[k] <= ' ') k--;
		value = (const char*)data;
		value = value.first(k-i+1,i);
		}else{
		//wir haben's mit einem formatierten string oder vektor zu tun --> ende (='"' oder ')') suchen
		bool atend = false;
		k++;
		while (!atend){
			while (data[k] != '\\' && data[k] != '"' && data[k] != 0) k++;
			//wir haben einen backslash gefunden -- steuerzeichen?
			switch(data[k]){
				case 0:		atend = true;break;
				case '\\':	if (data[k+1] == '\\' || data[k+1] == '"')
								//da ist nur ein backslash oder '"' gemeint
								k+=2; else k++; //sonst interpretieren wir nichts
							break;
				case '"':	atend = true;break;
				default:	k++;break;
				};
			}
		if (data[k] == '"'){ //das Ende wurde gefunden
			//das beginnende '"' gehört zum string
			//...ebenso das abschließende, entsprechend muß tstringentry parsen
			value = (const char*)data;
			value = value.first(k-i+1,i);
			//nun noch den kommentar suchen
			k++;
			while (data[k] <= ' ' && data[k] != 0) k++;
			if (data[k] != 0) parsecomment(data[k]==';'?k+1:k); //kommentar gefunden
			}else{ //ende nicht gefunden --> war vielleicht doch ein unformatierter string
			k = i; //machen weiter wie oben als unformatierter string, das beginnende '"' gehört nun aber dazu
			while (data[k] != ';' && data[k] != 0) k++;
			if (data[k] == ';') parsecomment(k+1);
			k--;
			while (data[k] <= ' ') k--;
			value = (const char*)data;
			value = value.first(k-i+1,i);
			}
		}
}

bool TConfigString::parsevektor(int i){
	//data[i] == '('
	int stringstart = i;
	i++;
	int vektordepth = 1;
	while (vektordepth > 0 && data[i] != 0){
		while (data[i] <= ' ' && data[i] != 0) i++; //zum anfang des nächsten wertes gehen
		if (data[i] == 0) break;
		if (data[i] == '"'){ //Anfang eines String gefunden?
			int k = i;
			bool atend = false;
			k++;
			while (!atend){
				while (data[k] != '\\' && data[k] != '"' && data[k] != 0) k++;
				//wir haben einen backslash gefunden -- steuerzeichen?
				switch(data[k]){
					case 0:		atend = true;break;
					case '\\':	if (data[k+1] == '\\' || data[k+1] == '"')
									//da ist nur ein backslash oder '"' gemeint
									k+=2; else k++; //sonst interpretieren wir nichts
								break;
					case '"':	atend = true;break;
					default:	k++;break;
					};
				}
			if (data[k] == '"'){ //Ende des strings gefunden
				i = k;
				i++;
				while (data[i] <= ' ' && data[i] != 0) i++; //zum anfang des nächsten komma gehen
				if (data[i] == ','){
					i++; //jetzt kann der nächste wert kommen
					continue;
					}else
				if (data[i] == ')') {
					vektordepth--;
					i++;
					continue;
					}else
				return false; //separator war nicht ',' und auch keine schließende klammer gefunden
				}
			//sonst machen wir als unformatierter string weiter...
			}
		if (data[i] == ')'){ //schließende klammer
			vektordepth--;
			i++;
			if (vektordepth > 0){//komma suchen
				while(data[i] <= ' ' && data[i] != 0) i++;
				if (data[i] == ',') i++;
					else
					if (data[i] != ')'){ //Fehler
						return false;
						}
				}
			continue;
			}
		if (data[i] == '('){ //öffnende klammer
			vektordepth++;
			i++;
			continue;
			}
		if (data[i] == ','){ //da war ein leerer string drin
			i++;
			continue;
			}
		//dann suchen wir jetzt ein komma, welches das ende,
		//bzw. den anfang des nächsten kennzeichnet
		while (data[i] != ',' && data[i] != ')' && data[i] != 0) i++; //zum anfang des nächsten komma gehen
		if (data[i] == ')'){ //schließende klammer
			vektordepth--;
			i++;
			if (vektordepth > 0){//komma suchen
				while(data[i] <= ' ' && data[i] != 0) i++;
				if (data[i] == ',') i++;
					else
					if (data[i] != ')'){ //Fehler
						return false;
						}
				}
			continue;
			}
		if (data[i] == ','){ //da war ein normaler string oder eine zahl drin
			i++;
			continue;
			}
		return false; //fehler, sind zum ende gekommen, aber der vektor war nicht zuende
		}

	if (vektordepth > 0) return false;
	value = (const char*)data;
	value = value.first(i-stringstart,stringstart);
	while (data[i] <= ' ' && data[i] != 0) i++;
	if (data[i] != 0) parsecomment(data[i]==';'?i+1:i); //kommentar gefunden
	return true;
}

