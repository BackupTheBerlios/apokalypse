
#ifndef __TCONFIG_STRING_H
#define __TCONFIG_STRING_H

#include "tstring.h"

/**
*TConfigString diehnt zum parsen einzelner Zeilen eines @ref TConfigFiles.
*Es wird von @ref TConfig verwendet um die aus der Datei gelesenen Daten
*in die eigene Baumstruktur umzuwandeln.
*TConfigString ist für die interne Verarbeitung in libcpputil und nicht
*für dei Verwendung in Programmen gedacht.
*/
class TConfigString{
public:
	/**
	*Constructor. Erzeugt ein leeres TConfigString-Objekt.
	*/
	TConfigString();
	/**
	*Constructor. Erzeugt ein TConfigString-Objekt mit den Daten aus text.
	*text wird sofort geparst.
	*@param text die eingelesene Textzeile oder 0
	*/
	TConfigString(const char* text);
	/**
	*Constructor. Erzeugt ein TConfigString-Objekt mit den Daten aus text.
	*text wird sofort geparst.
	*@param text die eingelesene Textzeile
	*/
	TConfigString(const TString & text);
	~TConfigString();
	/**
	*Weist dem TConfigString-Objekt text als neue Eingabe zu.
	*text wird sofort geparst.
	*@param text die eingelesene Textzeile
	*/
	void parse(const TString &text);
	/**
	*Weist dem TConfigString-Objekt text als neue Eingabe zu.
	*text wird sofort geparst.
	*@param text die eingelesene Textzeile oder 0
	*/
	void parse(const char* text);
	/**
	*@return true, falls die aktuell zugewiesene Textzeile nur einen Kommentar
	*enthält, sonst false
	*/
	bool isComment() const; //Zeile ist nur ein Kommentar
	/**
	*@return true, falls die aktuell zugewiesene Textzeile eine Sektion beschreibt
	*/
	bool isSection() const; //Zeile ist Sektion-Beschreiber + evtl Kommentar
	/**
	*@return true, falls die aktuell zugewiesene Textzeile einen Kommentar enthält
	*/
	bool hasComment() const; //Zeile enthält einen Kommentar
	/**
	*@return true, falls die aktuell zugewiesene Textzeile ein Item beschreibt,
	*d.h. in der Form ITEMNAME = WERT ;KOMMENTAR ist.
	*/
	bool isItem() const; //Zeile ist Item + evtl. Kommentar
	/**
	*@return der aktuelle Name der Sektion (isSection()==true) bzw. der
	*aktuelle ItemName (isItem()==true), sonst wird ein leerer String zurückgeliefert.
	*/
	const TString getName();
	/**
	*@return der aktuelle Wert eines Item (isItem()==true), sonst wird ein leerer String zurückgeliefert.
	*/
	const TString getValue();
	/**
	*@return der aktuelle Kommentar einer Zeile (hasComment()==true), sonst wird ein leerer String zurückgeliefert.
	*/
	const TString getComment();


protected:
	/**
	*intern! Parst die eingegebene Textzeile in ihre Bestandteile.
	*Dazu werden auch parsesection(), parsecomment() und parseitem() verwendet.
	*/
	virtual void parse();
	/**
	*intern! Parst die eingegebene Textzeile in ihre Bestandteile, falls
	*bereits feststeht, dass es sich um eine Sektion (der String beginnt mit '[')
	*handelt. Falls kein abschließendes ']' gefunden wird, wird parsecomment() aufgerufen.
	*/
	virtual void parsesection(int);
	/**
	*intern! Parst die eingegebene Textzeile in ihre Bestandteile, falls
	*bereits feststeht, dass es sich um einen Kommentar handelt.
	*@param i der Kommentar beginnt an der Stelle i (nach einem ';' oder '#')
	*/
	virtual void parsecomment(int i);
	/**
	*intern! Parst die eingegebene Textzeile in ihre Bestandteile, falls
	*bereits feststeht, dass es sich um ein Item (der String beginnt mit keinem '[',';' oder '#')
	*handelt. Falls kein '=' gefunden wird, wird parsecomment() aufgerufen.
	*/
	virtual void parseitem(int);
	/**
	*intern! Parst die eingegebene Value in ihre Bestandteile, falls
	*bereits feststeht, dass es sich um einen Vektor (der String beginnt mit '(')
	*handelt. Falls kein ')' gefunden wird, wird mit parseitem() fortgefahren.
	*/
	virtual bool parsevektor(int);

	/**
	*intern! Zeigt auf den im Moment zu parsenden String.
	*/
	const unsigned char* data;
	/**
	*intern! Enthält den Sektion bzw. Itemnamen (falls vorhanden)
	*Siehe auch: getName()
	*/
	TString name; //section oder itemname
	/**
	*intern! true, falls es sich im eine Sektion handelt.
	*Sie auch: isSection()
	*/
	bool isasection; //
	/**
	*intern! Enthält den Itemwert (falls vorhanden)
	*Siehe auch: getValue(), isItem()
	*/
	TString value; //bei section leer
	/**
	*intern! Enthält den Kommentar (falls vorhanden)
	*Siehe auch: getComment(), hasComment(), isComment()
	*/
	TString comment; //kommentar
};

#endif

