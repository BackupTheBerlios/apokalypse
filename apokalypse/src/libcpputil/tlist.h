
#ifndef __TList_H
#define __TList_H

class TListItem;

/**
*TPtrList implementiert eine doppelt verkettete Liste von Zeigern.
*TPtrList sollte nicht in Programmen verwendet werden, da dazu TList
*wesentlich besser geeignet ist. TList erweitert diese Klasse.
*/
class TPtrList{
public:
	/**
	*Constructor. Erzeugt eine leere Liste. Falls autodelete==true gilt,
	*werden Einträge die mit ptr_remove() entfernt werden über deleteitem()
	*gelöscht(free()). Sonst wird nur der Listeneintrag gelöscht.
	*/
	TPtrList(bool autodelete);
	/**
	*Constructor. Wie oben, jedoch wird autodelete defaultmässig auf true gesetzt.
	*/
	TPtrList();
	/**
	*Destruktor. Ruft ptr_clear() auf.
	*/
	~TPtrList();
	/**
	*Setzt das autodelete-Flag auf autodelete. Falls autodelete==true gilt,
	*werden Einträge die mit ptr_remove() entfernt werden über deleteitem()
	*gelöscht(free()). Sonst wird nur der Listeneintrag gelöscht.
	*/
	void setAutoDelete(bool autodelete = true);
	/**
	*@return die Anzahl der Momentan in der Liste vorhandenen Einträge.
	*/
	int getCount() const{ return count; };

protected:
	/**
	*Sucht item in der Liste und entfernt es. Falls autodelete==true
	*wird item über deleteitem() gelöscht und NULL zurückgeliefert.
	*Sonst wird nur der Listeneintrag gelöscht aber der Zeiger auf
	*die Daten (item) bleibt erhalten und wird entsprechend zurückgeliefert.
	*Wenn item nicht gefunden wurde, wird in jedem Fall NULL zurückgeliefert.
	*Falls Current momentan auf item zeigt, wird Current auf NULL gesetzt.
	*@param item Zeiger auf das Datenobjekt, nicht den Listeneintrag!
	*@return NULL, falls autodelete==true, sonst item
	*/
	void* ptr_remove(void *item);
	/**
	*Löscht die gesamte Liste per ptr_remove() für jeden Eintrag.
	*Falls autodelete==false wird dabei kein deleteitem() aufgerufen!
	*/
	void ptr_clear();
	/**
	*Fügt das Datenobjekt item nach allen anderen Einträgen in die Liste ein.
	*item sollte nicht NULL sein, es wird aber auch nicht verhindert.
	*/
	void ptr_append(void *item);
	/**
	*Fügt das Datenobjekt item vor allen anderen Einträgen in die Liste ein.
	*item sollte nicht NULL sein, es wird aber auch nicht verhindert.
	*/
	void ptr_prepend(void *item);
	/**
	* Fügt item nach prev in die Liste ein.
	*/
	void ptr_append(void *item, void *prev);
	/**
	* Fügt item vor next in die Liste ein.
	*/
	void ptr_prepend(void *item, void *next);
	/**
	*@return ein Zeiger auf das erste Datenobjekt in der Liste
	*/
	void* ptr_getFirst();
	/**
	*@return ein Zeiger auf das letzte Datenobjekt in der Liste
	*/
	void* ptr_getLast();
	/**
	*@return ein Zeiger auf das Datenobjekt in der Liste, welches
	*vor dem zuletzt mit ptr_getPrev(),ptr_Next(),ptr_getFirst()...
	*gelesenen steht.
	*/
	void* ptr_getPrev();
	/**
	*@return ein Zeiger auf das Datenobjekt in der Liste, welches
	*nach dem zuletzt mit ptr_getPrev(),ptr_Next(),ptr_getFirst()...
	*gelesenen steht.
	*/
	void* ptr_getNext();
	/**
	*@return ein Zeiger auf das Datenobjekt in der Liste, welches
	*zuletzt mit ptr_getPrev(),ptr_Next(),ptr_getFirst()... gelesen wurde.
	*/
	void* ptr_getCurrent();
	/**
	* Sucht item in der Liste. Current wird entsprechend gesetzt.
	*@return item, falls item in der Liste zu finden ist, sonst NULL.
	*/
	void* ptr_findRev(void *item);
	/**
	*Löscht den Eintrag item mit free(item).
	*/
	virtual void deleteitem(void* item);

	bool autodelete;
	int count;
	TListItem *first;
	TListItem *last;
	TListItem *current;
};

/**
 * Template-Klasse für Listen von Zeigern.
 * Codebeispiel:
 *<pre>
 * TList&lt;TString&gt; persons;
 * persons << new TString("Jon");
 * persons << new TString("Bob");
 * persons << new TString("Maria");
 * for (TString* s = persons.getFirst(); s != 0; s = persons.getNext())
 *	printf("Person: %s\n",s->text());
 *</pre>
 * Dieses Beispiel zeigt das Erzeugen eines Listenobjektes für @ref TString,
 * das einfache Einfügen von Einträgen in die Liste und wie man sich den Inhalt
 * der Liste wieder anzeigen lassen kann.
 *
 * Die Listeneinträge müssen nach Verwendung von "persons" nicht explizit gelöscht werden,
 * da dies der Destruktor von TList automatisch übernimmt.
 */
template<class T> class TList : public TPtrList{
public:
	/**
	* Constructor. Erzeugt ein leeres Listenobjekt und setzt das Autodelete-Flag
	* auf autodelete.
	*/
	TList(bool autodelete) : TPtrList(autodelete) {};
	/**
	* Constructor. Erzeugt ein leeres Listenobjekt und setzt das Autodelete-Flag
	* auf true.
	*/
	TList() : TPtrList() {};
	/**
	* Löscht alle Listeneinträge, falls autodelete=true
	*/
	~TList(){};
	/**
	* Löscht alle Einträge und verwendet dazu @ref TPtrList::ptr_clear()
	*/
	void clear() {ptr_clear();};
	/**
	* Entfernt das Element item aus der Liste und verwendet dazu @ref TPtrList::ptr_remove()
	*/
	T* remove(T *item) {return (T*)ptr_remove(item);};
	/**
	* Fügt item als letztes Element an die Liste an.
	*/
	void append(T *item) {ptr_append(item);};
	/**
	* Fügt item als erstes Element an die Liste an.
	*/
	void prepend(T *item) {ptr_prepend(item);};
	/**
	* Fügt item nach prev in die Liste ein.
	*/
	void append(T *item, T *prev) {ptr_append(item,prev);};
	/**
	* Fügt item vor next in die Liste ein.
	*/
	void prepend(T *item, T *next) {ptr_prepend(item,next);};
	/**
	*Liefert das erste Element der Liste. Current wird entsprechend gesetzt.
	*
	*siehe auch: @ref TPtrList::ptr_getFirst(), @ref getLast()
	*@return das erste Element der Liste, oder NULL falls keines existiert.
	*/
	T* getFirst() {return (T*)ptr_getFirst();};
	/**
	*Liefert das letzte Element der Liste. Current wird entsprechend gesetzt.
	*
	*siehe auch: @ref TPtrList::ptr_getLast(), @ref getFirst()
	*@return das erste Element der Liste, oder NULL falls keines existiert.
	*/
	T* getLast() {return (T*)ptr_getLast();};
	/**
	*Liefert das Element, welches in der Liste vor dem zuletzt
	*mit getNext(),getPref()... gelesenen Eintrag ist.
	*Current wird entsprechend gesetzt.
	*
	*siehe auch: @ref TPtrList::ptr_getPrev(), @ref getNext()
	*@return s.o oder NULL falls keines existiert.
	*/
	T* getPrev() {return (T*)ptr_getPrev();};
	/**
	*Liefert das Element, welches in der Liste nach dem zuletzt
	*mit getNext(),getPref()... gelesenen Eintrag ist.
	*Current wird entsprechend gesetzt.
	*
	*siehe auch: @ref TPtrList::ptr_getNext(), @ref getPrev()
	*@return s.o oder NULL falls keines existiert.
	*/
	T* getNext() {return (T*)ptr_getNext();};
	/**
	*Liefert das Element, zuletzt
	*mit getNext(),getPref()... gelesen wurde.
	*
	*siehe auch: @ref TPtrList::ptr_getCurrent()
	*@return Current oder NULL falls Current nicht entsprechend gesetzt wurde.
	*/
	T* getCurrent() {return (T*)ptr_getCurrent();};
	/**
	*siehe auch: @ref TPtrList::ptr_findRev()
	*@return item oder NULL falls item nicht in der Liste existiert.
	*/
	T* findRev(T* item) {return (T*)ptr_findRev(item);};
	/**
	* Äquivalent zu append()
	*
	* siehe auch: append()
	*/
	T* operator << (T *item) {append(item); return item;};

protected:
	virtual void deleteitem(void *item){delete (T*)item;}
};

/**
 * Erweitert die Klasse @ref TList.
 * Zusätzlich werden die Methoden @ref push() und @ref pop() entsprechend
 * der Semantik eines Stack implementiert.
 * Wichtig ist hierbei, daß ein Stack i.Allg. nur mit autodelete=false Sinn macht.
 */
template<class T> class TStack : public TList<T>{
public:
	/**
	* Construktor. Erzeugt einen leeren Stack. Autodelete wird auf false gesetzt.
	*
	* Siehe auch: @ref TList::TList()
	*/
	TStack() : TList<T>(false) {};
	/**
	* Destruktor. Zerstört den Stack.
	* Falls die Datenelemente mitgelöscht werden sollen muss das
	* Autodeleteflag mit @ref TPtrList::setAutoDelete() auf true gesetzt werden.
	*
	* Siehe auch: @ref TList::~TList()
	*/
	~TStack(){};
	/**
	* Entfernt das oberste Element vom Stack und gibt einen Zeiger darauf zurück.
	*/
	T* pop() {return remove(getLast());};
	/**
	* Legt item als oberstes Element auf den Stack.
	*/
	void push(T* item) {append(item);};
};

/**
 * Erweitert die Klasse @ref TList.
 * Zusätzlich werden die Methoden @ref push() und @ref pop() entsprechend
 * der Semantik eines Fifo implementiert.
 * Wichtig ist hierbei, daß ein Fifo (Warteschlange) i.Allg. nur mit autodelete=false Sinn macht.
 */
template<class T> class TFifo : public TList<T>{
public:
	/**
	* Construktor. Erzeugt einen leeren Fifo. Autodelete wird auf false gesetzt.
	*
	* Siehe auch: @ref TList::TList()
	*/
	TFifo() : TList<T>(false) {};
	/**
	* Destruktor. Zerstört den Fifo.
	* Falls die Datenelemente mitgelöscht werden sollen muss das
	* Autodeleteflag mit @ref TPtrList::setAutoDelete() auf true gesetzt werden.
	*
	* Siehe auch: @ref TList::~TList()
	*/
	~TFifo(){};
	/**
	* Entfernt das als erstes hinzugefügte (und noch nicht "gepopte")
	* Element vom Fifo und gibt einen Zeiger darauf zurück.
	*/
	T* pop() {return remove(getFirst());};
	/**
	* Fügt item als neues Element an die Warteschlange an.
	*/
	void push(T* item) {append(item);};
};

#endif


