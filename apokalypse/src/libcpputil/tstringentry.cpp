
#include "tstringentry.h"
#include <stdlib.h>
#include <stdio.h>

TStringEntry::TStringEntry(const TConfigEntry& e)
	: TConfigEntry(e){
}

//ACHTUNG!! value sollte in formatierter form vorliegen
TStringEntry::TStringEntry(TConfig *cfg, const TString& section, const TString& name, const TString& value)
	: TConfigEntry(cfg,section,name){
	setValue(value);
}

TStringEntry::~TStringEntry(){
}

const TString TStringEntry::getString() const{
	TString ostr = "";
	if (value.isEmpty()) return ostr;

	if (value[0] == '"'){ //haben wir einen formatierten string?
		unsigned char* dummy = (unsigned char*)malloc(value.length()+1);
		if (!dummy) return ostr; //zur Sicherheit
		int i = 1, j = 0;
		bool atend = false, formatok = true;
		//jetzt kann's losgehen...

		while (!atend){ //...bis zum bitteren ende...
			switch (value[i]){
				case 0:		atend = true;//Ende erreicht, aber abschlieﬂendes '"' nicht gefunden
							formatok = false;
							dummy[j] = 0; //zur Sicherheit abschlieﬂen
							break;
				case '"':	atend = true;//Ende erreicht, format ist ok
							formatok = true;
							dummy[j] = 0; //String abschlieﬂen
							j++;
							break;
				case '\\':	//Steuerzeichen interpretieren
							switch (value[i+1]){
								case '\\':	dummy[j] = '\\';j++;break;
								case '"':	dummy[j] = '"';j++;break;
								case 'n':	dummy[j] = '\n';j++;break;
								case 'r':	dummy[j] = '\r';j++;break;
								case 't':	dummy[j] = '\t';j++;break;
								case 'f':	dummy[j] = '\f';j++;break;
								case 'v':	dummy[j] = '\v';j++;break;
								case '?':	dummy[j] = '\?';j++;break;
								case '\'':	dummy[j] = '\'';j++;break;
								default:	dummy[j] = '\\';j++;
											dummy[j] = value[i+1];j++;break;
								};
							i += 2;
							break;
				default:	dummy[j] = value[i];
							j++;
							i++;
							break;
				};
			}
		if (formatok){
			ostr = (const char*)dummy;
			free(dummy);
			return ostr; //fertig, hat alles geklappt
			}
		free(dummy);
		}
	//hier kommen wir nur hin, wenn string nicht formatiert ist
	ostr = value;
	return ostr;
}

void TStringEntry::setString(const TString& value){
	//hier erzeugen wir einen formatierten pendanten zu value
	unsigned char* dummy = (unsigned char*)malloc((value.length()*2)+3);//es kann max doppelt so lang werden
	if (!dummy){ //zur Sicherheit
		setValue(value);
		return;
		}
	int i = 0, j = 1;
	dummy[0] = '"';

	while (value[i]){
		switch (value[i]){
			case '"':	dummy[j] = '\\'; j++;
						dummy[j] = '"'; j++;
						break;
			case '\\':	dummy[j] = '\\'; j++;
						dummy[j] = '\\'; j++;
						break;
			case '\n':	dummy[j] = '\\'; j++;
						dummy[j] = 'n'; j++;
						break;
			case '\r':	dummy[j] = '\\'; j++;
						dummy[j] = 'r'; j++;
						break;
			case '\t':	dummy[j] = '\\'; j++;
						dummy[j] = 't'; j++;
						break;
			case '\f':	dummy[j] = '\\'; j++;
						dummy[j] = 'f'; j++;
						break;
			case '\v':	dummy[j] = '\\'; j++;
						dummy[j] = 'v'; j++;
						break;
			case '\?':	dummy[j] = '\\'; j++;
						dummy[j] = '?'; j++;
						break;
			case '\'':	dummy[j] = '\\'; j++;
						dummy[j] = '\''; j++;
						break;
			default:	dummy[j] = value[i]; j++;
						break;
			};
		i++;
		}
	//dummy noch abschlieﬂen, dann sind wir fertig
	dummy[j] = '\"'; j++;
	dummy[j] = 0;
	setValue((const char*)dummy);
	free(dummy);
}
