
#include "tconfigfile.h"
#include "utils.h"

TConfigFile::TConfigFile() : TTextFile(){
}

TConfigFile::TConfigFile(TString path) : TTextFile(path){
}

TConfigFile::~TConfigFile(){
}

void TConfigFile::appendLine(const char* s){
	CHECKPTR(s);
	if (s[0] != 0){ //wenigstens ein newline sollte da sein
		TString *str = new TString(s);
		str->stripWhiteSpace();
		text << str;
		}
}

TString TConfigFile::prepareLine(){
	TString line;
	TString *s = text.getCurrent();
	if (!s) return line;
	line = *s + "\n";
	return line;
}
