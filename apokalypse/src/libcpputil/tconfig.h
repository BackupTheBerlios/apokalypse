
#ifndef __TCONFIG_H
#define __TCONFIG_H

#define __TCONFIG_VERSION 0
#include "tconfigfile.h"
#include "tsection.h"

class TConfigEntry;
/**
*TConfig diehnt als Wrapper für @ref TConfigFile. Codebeispiel:
*<pre>
*TConfigFile cff("/etc/meinconfigfile");
*TConfig cfg;
*cfg << cff;
*</pre>
*TConfig kann nun zum direkten Zugriff auf die Konfigurationsdaten verwendet werden ohne die eigentliche
*Datei (TConfigFile) zu verändern. Demnach kann das TConfigFile-Objekt auch für weitere TConfig-Objekte
*genutzt werden oder auch zum Rückgängigmachen von Änderungen.*/

class TConfig{
public:
	/**
	*Constructor.
	*Erzeugt ein leeres TConfig-Objekt.
	*/
	TConfig();
	/**
	*Constructor.
	*Erzeugt ein TConfig-Objekt, das sofort die Daten cfgfile zugewiesen bekommt.
	*@param cfgfile Das @ref TConfigFile -Objekt, welches die bereits geladenen Daten liefert.
	*/
	TConfig(const TConfigFile& cfgfile);
	~TConfig();
	/**
	*Die Daten aus cfgfile werden zugewiesen.
	*Falls die Datei noch nicht geladen wurde, wird dies nachgeholt (implementiert in TConfigFile)
	*@param cfgfile Das @ref TConfigFile -Objekt, welches die bereits geladenen Daten liefert.
	*/
	void operator << (TConfigFile& cfgfile);
	/**
	*Die Daten werden dem @ref TConfigFile zurückgegeben und dort sofort in die zugewiesene
	*Datei per save() geschrieben.
	*/
	void operator >> (TConfigFile& cfgfile);
	/**
	* print() gibt die gespeicherten Daten lesbar auf stdout aus.
	* Dies macht vor allem (und fast nur) zum Debuggen Sinn.
	*/
	void print();

	TConfigItem* getItem(const TString& name);
	TConfigItem* getItem(const TString& section, const TString& name);
	TSection* setSection(const TString& section);

	TConfigEntry getEntry(const TString& name);
	TConfigEntry getEntry(const TString& section, const TString& name);
	void setEntry(const TConfigEntry&);

protected:
	TList<TSection> sectionlist;

	TSection* findSection(const TString& s);
	TConfigItem* findEntry(const TString& e);
};

#endif

