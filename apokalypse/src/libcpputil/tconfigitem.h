
#ifndef __TCONFIGITEM_H
#define __TCONFIGITEM_H
#include "tstring.h"

/**
* Implementiert einen Eintrag innerhalb einer Sektion von @ref TConfig.
* TConfigItem bildet die Basisklasse für alle wertorientierten Einträge.
* TConfigItem sollte primär abgeleitet (z.B. wie @ref TConfigInt) in Programmen verwendet werden.
* Zu beachten ist, daß Name und Value auch leer sein kann, was bedeutet, daß
* es sich im einen Kommentar oder eine Leerzeile handelt.
*/
class TConfigItem{
public:
	/**
	* Constructor. Erzeugt ein TConfigItem-Objekt und setzt dessen Namen auf name,
	* Value auf value und den Kommentar auf comment.
	*/
	TConfigItem(const char* name = 0, const char* value = 0, const char* comment = 0);
	/**
	* Constructor. Erzeugt ein TConfigItem-Objekt und setzt dessen Namen auf name,
	* Value auf value und den Kommentar auf comment.
	*/
	TConfigItem(const TString& name, const TString& value, const TString& comment);
	~TConfigItem();
	/**
	* Setzt den Namen auf name.
	*/
	void setName(const char* name);
	/**
	* Setzt den Namen auf name.
	*/
	void setName(const TString& name);
	/**
	* @return der Name des Item
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
	* Setzt den Kommentar auf comment.
	*/
	virtual void setValue(const char* value);
	/**
	* Setzt den Kommentar auf comment.
	*/
	virtual void setValue(const TString& value);
	/**
	* liefert den Kommentar zurück.
	*/
	TString getValue() const;
	/**
	* liefert den Item-String, wie er in @ref TConfig geschrieben werden kann.
	*/
	TString getString() const;

protected:
	TString name;
	TString value;
	TString comment;
};

#endif


