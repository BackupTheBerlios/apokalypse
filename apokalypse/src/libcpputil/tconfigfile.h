
#ifndef __TCONFIGFILE_H
#define __TCONFIGFILE_H

#include "ttextfile.h"

/**
*TConfigFile ist im wesentlichen ein @ref TTextFile, welches jedoch beim Laden des
*Textes bereits ein TString::stripWhiteSpace() für jede Zeile ausführt.
*Dadurch wird auch ein eventuelles \n am Ende einer Zeile gelöscht.
*/
class TConfigFile : public TTextFile{
public:
	/**
	*Constructor. Erzeugt ein leeres TConfigFile-Objekt. Die Daten müssen später mit
	*<pre>
	*setPath(TString);
	*load();
	*</pre>
	*oder mit
	*<pre>
	*load(TString);
	*</pre>
	*geladen werden.
	*/
	TConfigFile();
	/**
	*Constructor. Erzeugt ein leeres TConfigFile-Objekt. Die Daten müssen später mit
	*load();
	*geladen werden.
	*/
	TConfigFile(TString path);
	~TConfigFile();

protected:
	virtual void appendLine(const char*);
	/**
	* Wird beim Speichern verwendet um eine Textzeile (text.getCurrent())
	* so anzupassen, daß sie ins Configfile geschrieben werden kann.
	* Diese Implemantation überschreibt die von @ref TTextFile dahingehend, daß
	* eine Kopie von text.getCurrent() mit angehängtem NewLine zurückgegeben wird.
	*/
	virtual TString prepareLine();

};

#endif

