
#ifndef __TSECTION_H
#define __TSECTION_H

#include "tstring.h"
#include "tlist.h"
#include "tconfigitem.h"

/**
* Implementiert einen Eintrag in der Sektion-Liste von @ref TConfig.
* TSection ist vorrangig für die interne Verarbeitung gedacht und sollte
* nicht in Programmen verwendet werden.
*/
class TSection{
public:
	/**
	* Constructor. Erzeugt ein TSection-Objekt und setzt dessen Namen auf name
	* bzw. bedeutet name = NULL oder name = "" dass es sich um die globale Section
	* "[]" handelt.
	*/
	TSection(const char* name = 0, const char* comment = 0);
	/**
	* Constructor. Erzeugt ein TSection-Objekt und setzt dessen Namen auf name
	* bzw. bedeutet name = "" dass es sich um die globale Section
	* "[]" handelt.
	*/
	TSection(const TString& name, const TString& comment);
	~TSection();
	/**
	* Setzt den Namen auf name bzw. bedeutet name = NULL oder name = ""
	* dass es sich um die globale Section "[]" handelt.
	*/
	void setName(const char* name);
	/**
	* Setzt den Namen auf name bzw. bedeutet name = ""
	* dass es sich um die globale Section "[]" handelt.
	*/
	void setName(const TString& name);
	/**
	* @return der Name der Section bzw. "" falls es sich um die globale
	* Section "[]" handelt.
	*/
	TString getName() const;
	/**
	* Setzt den Kommentar auf comment.
	*/
	void setComment(const char* comment);
	/**
	* Setzt den Kommentar auf comment.
	*/
	void setComment(const TString& comment);
	/**
	* liefert den Kommentar zurück.
	*/
	TString getComment() const;
	/**
	* liefert den Section-String, wie er in @ref TConfig geschrieben werden kann.
	*/
	TString getString() const;
	/**
	* liefert die Liste, die die wertorientierten Einträge (Items) bezüglich der Section hält.
	*/
	TList<TConfigItem>* itemList();

protected:
	TString name;
	TString comment;
	TList<TConfigItem> itemlist;
};

#endif

