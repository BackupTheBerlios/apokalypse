
#ifndef __TTEXTFILE_H
#define __TTEXTFILE_H

#include "tstring.h"
#include "tlist.h"

/**
*TTextFile diehnt zum Laden und Speichern normaler Textdateien.
*/
class TTextFile{
public:
	/**
	*Constructor. Erzeugt ein leeres TTextFile-Objekt und setzt den Dateipfad
	*direkt auf path. Zum Laden muss noch load() aufgerufen werden.
	*/
	TTextFile(TString path);
	/**
	*Constructor. Erzeugt ein leeres TTextFile-Objekt.
	*Zum Laden muss noch load(TString) oder setPath(TString);load() aufgerufen werden.
	*/
	TTextFile();
	~TTextFile();
	/**
	*Setzt den Dateipfad.
	*/
	void setPath(TString path);
	/**
	*Liefert das Home-Verzeichnis des Benutzers über getenv($HOME).
	*
	*Es wird sichergestellt, daß ein abschließender '/' evtl. angefügt wird.
	*Dadurch kann z.B. direkt ein setPath(TTextFile::getHomeDir()+"meinfilename")
	*verwendet werden.
	*@return Homeverzeichnis des Benutzers mit abschließendem '/'
	*/
	static TString getHomeDir();
	/**
	*Liefert den zum Errcode mit load() erzeugten Errcode als String.
	*@param errcode der mit load() gelieferte errcode (!=0)
	*@return Fehlercode-Beschreibung zu errcode
	*/
	static TString getErrString(int errcode);
	/**
	*Liefert den aktuell gesetzten Dateipfad.
	*@return der aktuell gesetzte Dateipfad als TString
	*/
	const TString& getPath() const;
	/**
	*Setzt den Dateipfad auf path und ruft dann save() auf.
	*@return 0 bei Erfolg, sonst der Errcode(<0), der mit getErrString() ausgewertet werden kann.
	*/
	int save(TString path);
	/**
	*Speichert die Datei, auf die der aktuelle Dateipfad (getPath()) zeigt.
	*Falls getPath() einen leeren String enthält, wird nach stdout geschrieben.
	*@return 0 bei Erfolg, sonst der Errcode(<0), der mit getErrString() ausgewertet werden kann.
	*/
	int save();
	/**
	*Setzt den Dateipfad auf path und ruft dann load() auf.
	*@return 0 bei Erfolg, sonst der Errcode(<0), der mit getErrString() ausgewertet werden kann.
	*/
	int load(TString path);
	/**
	*Läd die Datei, auf die der aktuelle Dateipfad (getPath()) zeigt.
	*Falls getPath() einen leeren String enthält, wird von stdin gelesen.
	*@return 0 bei Erfolg, sonst der Errcode(<0), der mit getErrString() ausgewertet werden kann.
	*/
	int load();
	/**
	*Liefert die geladenen Textzeilen als Liste. Falls die Datei noch nicht geladen
	*wurde, wird dies nachgeholt. Beachten Sie, daß es dann nur mit lastError() möglich ist einen
	*Fehler beim Laden zu erkennen. Sie sollten sich also sehr sicher sein, daß die
	*Datei existiert, lesbar ist und im korrekten Format vorliegt.
	*@return Zeiger auf eine Liste (@ref TList) von Strings (@ref TString)
	*/
	TList<TString> *getText();
	/**
	* Liefert den Text (wie @ref getText()) jedoch wird vorher die Zeilenliste
	* geleert und das loaded-Flag auf false gesetzt.
	*/
	TList<TString> *clearText();
	/**
	*@return der letzte Fehlercode, der mit @ref load() oder @ref save() gesetzt wurde.
	*/
	int lastError() const;
	/**
	*setzt den aktuellen Fehlercode auf 0
	*/
	void clearErr();

protected:
	/**
	* Wird beim Laden verwendet um eine Textzeile (s) zur Liste (text) hinzuzufügen.
	*/
	virtual void appendLine(const char* s);
	/**
	* Wird beim Speichern verwendet um eine Textzeile (text.getCurrent())
	* so anzupassen, daß sie ins Configfile geschrieben werden kann.
	* Die Default-Implemantation gibt einfach eine Kopie von text.getCurrent() zurück.
	*/
	virtual TString prepareLine();

	TString path;
	TList<TString> text;
	bool loaded;
	int lasterr;
};

#endif

