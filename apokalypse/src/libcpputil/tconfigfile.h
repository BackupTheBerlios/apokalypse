
#ifndef __TCONFIGFILE_H
#define __TCONFIGFILE_H

#include "ttextfile.h"

/**
*TConfigFile ist im wesentlichen ein @ref TTextFile, welches jedoch beim Laden des
*Textes bereits ein TString::stripWhiteSpace() f�r jede Zeile ausf�hrt.
*Dadurch wird auch ein eventuelles \n am Ende einer Zeile gel�scht.
*/
class TConfigFile : public TTextFile{
public:
	/**
	*Constructor. Erzeugt ein leeres TConfigFile-Objekt. Die Daten m�ssen sp�ter mit
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
	*Constructor. Erzeugt ein leeres TConfigFile-Objekt. Die Daten m�ssen sp�ter mit
	*load();
	*geladen werden.
	*/
	TConfigFile(TString path);
	~TConfigFile();

protected:
	virtual void appendLine(const char*);
	/**
	* Wird beim Speichern verwendet um eine Textzeile (text.getCurrent())
	* so anzupassen, da� sie ins Configfile geschrieben werden kann.
	* Diese Implemantation �berschreibt die von @ref TTextFile dahingehend, da�
	* eine Kopie von text.getCurrent() mit angeh�ngtem NewLine zur�ckgegeben wird.
	*/
	virtual TString prepareLine();

};

#endif

