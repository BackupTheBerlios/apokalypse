
#include "tvectorentry.h"
#include "tlist.h"
#include <stdlib.h>
#include <stdio.h>

TVectorEntry::TVectorEntry(const TConfigEntry& e)
	: TConfigEntry(e){
}

//ACHTUNG!! value sollte in formatierter form vorliegen
TVectorEntry::TVectorEntry(TConfig *cfg, const TString& section, const TString& name, const TString& value)
	: TConfigEntry(cfg,section,name){
	setValue(value);
}

TVectorEntry::~TVectorEntry(){
}

int TVectorEntry::getVector(int n, TConfigEntry* entrys[]) const{
	if (n == 0) return 0;
	if (value[0] != '('){
		if (n >= 1)
			entrys[0]->setValue(getValue());
		return 1;
		}

	int i = 1;
	int vektordepth = 1;
	TList<TString> elist;
	int k = i;
	while (vektordepth > 0 && value[i] != 0){
		while (((unsigned char)value[i]) <= ' ' && value[i] != 0) i++; //zum anfang des nächsten wertes gehen
		if (value[i] == 0) break;
		if (value[i] == '"'){ //Anfang eines String gefunden?
			int orgpos = i;
			bool atend = false;
			i++;
			while (!atend){
				while (value[i] != '\\' && value[i] != '"' && value[i] != 0) i++;
				//wir haben einen backslash gefunden -- steuerzeichen?
				switch(value[i]){
					case 0:		atend = true;break;
					case '\\':	if (value[i+1] == '\\' || value[i+1] == '"')
									//da ist nur ein backslash oder '"' gemeint
									i+=2; else i++; //sonst interpretieren wir nichts
								break;
					case '"':	atend = true;break;
					default:	i++;break;
					};
				}
			if (value[i] == '"'){ //Ende des strings gefunden
				if (vektordepth == 1)
					elist << new TString(value.first(i-k+1,k));
				i++;
				while (((unsigned char)value[i]) <= ' ' && value[i] != 0) i++; //zum anfang des nächsten komma gehen
				if (value[i] == ','){
					i++; //jetzt kann der nächste wert kommen
					if (vektordepth == 1) k = i;
					continue;
					}else
				if (value[i] == ')') {
					vektordepth--;
					if (vektordepth == 1){
						elist << new TString(value.first(i-k+1,k));
						i++;
						k = i;
						}else i++;
					continue;
					}else
				if (n >= 1)
					entrys[0]->setValue(getValue());
				return 1;//separator war nicht ',' und auch keine schließende klammer gefunden
				}
			//sonst machen wir als unformatierter string weiter...
			i = orgpos;
			}
		if (value[i] == ')'){ //schließende klammer
			vektordepth--;
			if (vektordepth == 0){
				if (i != k)
					elist << new TString(value.first(i-k,k));
				}
			if (vektordepth == 1){
				elist << new TString(value.first(i-k+1,k));
				i++;
				k = i;
				}else i++;
			if (vektordepth > 0){//komma suchen
				while(((unsigned char)value[i]) <= ' ' && value[i] != 0) i++;
				if (value[i] == ',') i++;
					else
					if (value[i] != ')'){ //Fehler
						if (n >= 1)
							entrys[0]->setValue(getValue());
						return 1;
						}
				if (vektordepth == 1) k = i;
				}
			continue;
			}
		if (value[i] == '('){ //öffnende klammer
			vektordepth++;
			if (vektordepth == 2) k = i;
			i++;
			continue;
			}
		if (value[i] == ','){ //da war ein leerer string drin
			i++;
			if (vektordepth == 1){
				elist << new TString("");
				k = i;
				}
			continue;
			}
		//dann suchen wir jetzt ein komma, welches das ende,
		//bzw. den anfang des nächsten kennzeichnet
		while (value[i] != ',' && value[i] != ')' && value[i] != 0) i++; //zum anfang des nächsten komma gehen
		if (value[i] == ')'){ //schließende klammer
			vektordepth--;
			if (vektordepth == 0){
				if (i != k)
					elist << new TString(value.first(i-k,k));
				}
			if (vektordepth == 1){
				elist << new TString(value.first(i-k+1,k));
				i++;
				k = i;
				}else i++;
			if (vektordepth > 0){//komma suchen
				while(((unsigned char)value[i]) <= ' ' && value[i] != 0) i++;
				if (value[i] == ',') i++;
					else
					if (value[i] != ')'){ //Fehler
						if (n >= 1)
							entrys[0]->setValue(getValue());
						return 1;
						}
				if (vektordepth == 1) k = i;
				}
			continue;
			}
		if (value[i] == ','){ //da war ein normaler string oder eine zahl drin
			if (vektordepth == 1){
				elist << new TString(value.first(i-k,k));
				i++;
				k = i;
				}else i++;
			continue;
			}
		if (n >= 1)
			entrys[0]->setValue(getValue());
		return 1;//fehler, sind zum ende gekommen, aber der vektor war nicht zuende
		}

	if (vektordepth > 0){
		if (n >= 1)
			entrys[0]->setValue(getValue());
		return 1;//fehler, sind zum ende gekommen, aber der vektor war nicht zuende
		}

	int entrycnt = 0;
	for (TString *s = elist.getFirst(); s != 0; s = elist.getNext()){
		if (entrycnt < n){
			entrys[entrycnt]->setValue(*s);
			entrycnt++;
			}else break;
		}
	return entrycnt;
}

void TVectorEntry::setVector(int n, TConfigEntry* entrys[]){
}


