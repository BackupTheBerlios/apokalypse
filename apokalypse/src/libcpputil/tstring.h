
#ifndef __TSTRING_H
#define __TSTRING_H

/**
* Implementiert eine leicht handhabbare Stringklasse.
* TString überläd dabei viele Operatoren um die Klasse verständlicher
* benutzen zu können. Codebeispiel:
*<pre>
* TString a = "Hallo";
* TString b;
* TString c("Welt");
* b = " ";
* //hier könnte auch b << c << "...\n" stehen
* b += c + "...\n";
* a = a + b;
* printf("%s",a->text());
*</pre>
*/
class TString{
public:
	/**
	* Constructor. Erzeugt ein TString-Objekt und setzt den String auf "".
	*/
	TString();
	/**
	* Constructor. Erzeugt ein TString-Objekt und erzeugt eine Kopie von text.
	*/
	TString(const char* text);
	/**
	* Constructor. Erzeugt ein TString-Objekt und setzt dessen Text auf s.
	*/
	TString(const TString &s);
	/**
	* Destructor. Entfernt alle benutzten Ressourcen.
	*/
	~TString();
	/**
	* @return den aktuell gesetzten String nullterminiert, gibt niemals NULL zurück.
	*/
	const char* text() const;
	/**
	* setzt den String auf text (kopie)
	*/
	virtual void setText(const char* text);
	/**
	* @return Länge des String ohne abschließendes NULL
	*/
	int length() const;
	/**
	* @return true, falls text="" oder text = NULL
	*/
	bool isEmpty() const;
	/**
	* Äquivalent zu @ref setText()
	*/
	virtual TString& operator = (const TString&);
	/**
	* Äquivalent zu @ref setText()
	*/
	virtual TString& operator = (const char*);
	/**
	* Fügt s an den String an, s wird nicht verändert.
	*/
	virtual TString& operator += (const TString& s);
	/**
	* Fügt text an den String an, text wird nicht verändert.
	*/
	virtual TString& operator += (const char* text);
	/**
	* Liefert einen String mit den ersten n Zeichen, wobei bei der Position
	* startpos begonnen wird. Sollte n größer als der String sein oder
	* startpos zu groß, so wird entsprechend verkürzt.
	*/
	TString first(int n = 1, int startpos = 0) const;
	/**
	* Liefert einen String mit den letzten n Zeichen
	* Sollte n größer als der String sein, so wird entsprechend verkürzt.
	*/
	TString last(int n = 1) const;
	/**
	* Liefert das i-te Element des Strings. Es wird dem Programmierer überlassen
	* sicherzustellen, daß i < @ref length()
	*/
	char operator[](int i) const;
	/**
	* entfernt alle Leer- und Steuerzeichen vor und hindem dem String.
	* Leer- und Steuerzeichen innerhalb des Strings werden nicht berührt.
	*/
	virtual TString& stripWhiteSpace();

	TString& setNumber(int i);
	TString& setNumber(double d, char mod = 'g', unsigned int prec = 6);
	int toInt(bool *ok = 0, int base = 10);
	double toDouble(bool *ok = 0);

protected:

	char* data;
};

/**
* Liefert einen String, bei dem die Buchstaben mit @ref upperChar() konvertiert wurden.
*/
TString strUpper(const TString& s);
/**
* Liefert einen String, bei dem die Buchstaben mit @ref lowerChar() konvertiert wurden.
*/
TString strLower(const TString& s);
/**
* Falls c = a..z wird der entsprechende Großbuchstabe zurückgeliefert,
* sonst c.
*/
char upperChar(char c);
/**
* Falls c = A..Z wird der entsprechende Kleinbuchstabe zurückgeliefert,
* sonst c.
*/
char lowerChar(char c);
/**
* Liefert einen String, bei dem a und b konkateniert sind.
* a und b werden nicht verändert.
*
* Siehe auch: @ref TString
*/
TString operator + (const TString& a, const TString& b);
/**
* Liefert einen String, bei dem a und b konkateniert sind.
* a und b werden nicht verändert.
*
* Siehe auch: @ref TString
*/
TString operator + (const TString&, const char*);
/**
* Liefert einen String, bei dem a und b konkateniert sind.
* a und b werden nicht verändert.
*
* Siehe auch: @ref TString
*/
TString operator + (const char*, TString&);
/**
* @return true, falls beide Strings völlig gleich sind (d.h. auch gleiche Länge).
*
* Siehe auch: @ref TString
*/
bool operator == (const TString&, const TString&);
/**
* @return true, falls beide Strings völlig gleich sind (d.h. auch gleiche Länge).
*
* Siehe auch: @ref TString
*/
bool operator == (const TString&, const char*);
/**
* @return true, falls beide Strings völlig gleich sind (d.h. auch gleiche Länge).
*
* Siehe auch: @ref TString
*/
bool operator == (const char*, TString&);
/**
* @return true, falls die Strings unterschiedlich sind.
*
* Siehe auch: @ref TString
*/
bool operator != (const TString&, const TString&);
/**
* @return true, falls die Strings unterschiedlich sind.
*
* Siehe auch: @ref TString
*/
bool operator != (const TString&, const char*);
/**
* @return true, falls die Strings unterschiedlich sind.
*
* Siehe auch: @ref TString
*/
bool operator != (const char*, TString&);

#endif


