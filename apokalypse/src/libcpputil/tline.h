
#ifndef __TLINE_H
#define __TLINE_H

#include "tstring.h"
/**
*Veraltet.
*TLine war urspr�nglich gedacht um Eintr�ge einer doppelt verkettete Liste von Textzeilen
*zu realisiert.
*Momentan wird TLine in libcpputil nicht weiter verwendet, da
*die Klassen @ref TString und @ref TList besser geeignet sind.
*Falls TLine verwendet wird, empfielt es sich eine separate Klasse zu schreiben,
*die die Liste dieser TLine-Objekte verwaltet und eine abstahierte Schnittstelle
*zum Einf�gen und L�schen implementiert.
*/
class TLine{
public:
	/**
	*Constructor. Erzeugt ein TLine-Objekt mit einer Kopie von text
	*und h�lt einen Zeiger mit den in der Zeilenliste vorhergehenden (prev)
	*bzw. nachfolgenden (next) TLine-Objekten.
	*S�mtliche Paramerter d�rfen NULL sein.
	*/
	TLine(const char* text = 0, TLine *prev = 0, TLine *next = 0);
	/**
	*Constructor. Erzeugt ein TLine-Objekt mit einer Kopie von s
	*und h�lt einen Zeiger mit den in der Zeilenliste vorhergehenden (prev)
	*bzw. nachfolgenden (next) TLine-Objekten.
	*prev und next d�rfen NULL sein.
	*/
	TLine(TString& s, TLine *prev = 0, TLine *next = 0);
	~TLine();
	/**
	*Erzeugt eine Kopie von s und speichert diese. Ein vorher bereits gesetzter
	*String wird �berschrieben.
	*/
	void setText(TString& s);
	/**
	*Erzeugt eine Kopie von s und speichert diese. Ein vorher bereits gesetzter
	*String wird �berschrieben.
	*/
	void setText(const char* s);
	/**
	*@return der aktuell gesetzte String.
	*/
	const char* getText() const;

	/**
	*@return der in der Liste vorhergehende Eintrag (Zeiger) oder NULL - entsprechend
	*des mit setPrev() oder mit dem Constructor gesetzten Wertes.
	*/
	TLine* getPrev() const;
	/**
	*@return der in der Liste nachfolgende Eintrag (Zeiger) oder NULL  - entsprechend
	*des mit setNext() oder mit dem Constructor gesetzten Wertes.
	*/
	TLine* getNext() const;
	/**
	*Setzt den in der Liste nachfolgenden Eintrag. Der Benutzer muss selbst pr�fen,
	*ob ein solcher bereits existiert und auch selbst setPrev() f�r diesen aufrufen.
	*/
	void setNext(TLine*);
	/**
	*Setzt den in der Liste vorhergehenden Eintrag. Der Benutzer muss selbst pr�fen,
	*ob ein solcher bereits existiert und auch selbst setNext() f�r diesen aufrufen.
	*/
	void setPrev(TLine*);

protected:
	bool isparsed;
	TString data;
	TLine *prev,*next;

	/**
	*intern! Diese Methode macht nichts!
	*/
	void parse();
};

#endif

