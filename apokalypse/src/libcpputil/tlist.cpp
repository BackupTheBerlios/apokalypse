
#include "tlist.h"
#include <stdlib.h>

class TListItem{
public:
	TListItem();
	~TListItem();

	TListItem* prev;
	TListItem* next;
	void* data;
};

TListItem::TListItem(){
	prev = 0;
	next = 0;
	data = 0;
}

TListItem::~TListItem(){
}

//**************************************************************************

TPtrList::TPtrList(bool autodelete){
	setAutoDelete(autodelete);
	first = 0;
	last = 0;
	current = 0;
	count = 0;
}

TPtrList::TPtrList(){
	setAutoDelete(true);
	first = 0;
	last = 0;
	current = 0;
	count = 0;
}

TPtrList::~TPtrList(){
	ptr_clear();
}

void TPtrList::setAutoDelete(bool autodelete){
	this->autodelete = autodelete;
}

void* TPtrList::ptr_findRev(void *item){
	if (current && current->data == item) return item;
	current = first;
	while (current && current->data != item) current = current->next;
	if (!current) return 0; //nicht gefunden!
	return current->data;
}

void* TPtrList::ptr_remove(void *item){
	TListItem *curitem = first;
	if (!current || current->data != item)
		while (curitem && curitem->data != item) curitem = curitem->next;
		else
		curitem = current;
	if (!curitem) return 0; //nicht gefunden!

	if (curitem->prev)
		curitem->prev->next = curitem->next;
	if (curitem->next)
		curitem->next->prev = curitem->prev;
	if (first == curitem) first = curitem->next;
	if (last == curitem) last = curitem->prev;
	if (current = curitem) current = 0;
	count--;

	void *ptr = curitem->data;
	if (autodelete && curitem->data){
		deleteitem(ptr);
		delete curitem;
		return 0;
		}
	delete curitem;
	return ptr;
}

void TPtrList::ptr_clear(){
	if (!autodelete){
		while (first){
			TListItem *curitem = first->next;
			delete first;
			first = curitem;
			}
		first = 0;
		last = 0;
		current = 0;
		count = 0;
		}else{
		while (first){
			TListItem *curitem = first->next;
			if (autodelete && first->data)
				deleteitem(first->data);
			delete first;
			first = curitem;
			}
		last = 0;
		current = 0;
		count = 0;
		}
}

void TPtrList::ptr_append(void *item){
	TListItem *curitem = new TListItem();
	curitem->data = item;
	if (last){
		curitem->prev = last;
		last->next = curitem;
		last = curitem;
		}else{
		last = curitem;
		first = curitem;
		}
	count++;
}

void TPtrList::ptr_prepend(void *item){
	TListItem *curitem = new TListItem();
	curitem->data = item;
	if (first){
		curitem->next = first;
		first->prev = curitem;
		first = curitem;
		}else{
		last = curitem;
		first = curitem;
		}
	count++;
}

void TPtrList::ptr_append(void *item, void *prev){
	if (!count){ //falls nichts in der Liste ignoriere prev
		first = new TListItem();
		first->data = item;
		last = first;
		count++;
		}else{
		//prev ist hoffentlich in der Liste
		TListItem *oldcurrent = current;
		ptr_findRev(prev);
		if (!current){ // nicht gefunden
			current = oldcurrent;
			return;
			}
		TListItem *newitem = new TListItem();
		newitem->data = item;
		newitem->prev = current;
		newitem->next = current->next;
		current->next = newitem;
		if (last == current) last = newitem;
		count++;
		current = oldcurrent;
		}
}

void TPtrList::ptr_prepend(void *item, void *next){
	if (!count){ //falls nichts in der Liste ignoriere next
		first = new TListItem();
		first->data = item;
		last = first;
		count++;
		}else{
		//next ist hoffentlich in der Liste
		TListItem *oldcurrent = current;
		ptr_findRev(next);
		if (!current){ // nicht gefunden
			current = oldcurrent;
			return;
			}
		TListItem *newitem = new TListItem();
		newitem->data = item;
		newitem->next = current;
		newitem->prev = current->prev;
		current->prev = newitem;
		if (first == current) first = newitem;
		count++;
		current = oldcurrent;
		}
}


void* TPtrList::ptr_getFirst(){
	if (first){
		current = first;
		return current->data;
		}
	return 0;
}

void* TPtrList::ptr_getLast(){
	if (last){
		current = last;
		return current->data;
		}
	return 0;
}

void* TPtrList::ptr_getPrev(){
	if (current){
		current = current->prev;
		if (current) return current->data;
		}
	return 0;
}

void* TPtrList::ptr_getNext(){
	if (current){
		current = current->next;
		if (current) return current->data;
		}
	return 0;
}

void* TPtrList::ptr_getCurrent(){
	if (current)
		return current->data;
	return 0;
}

void TPtrList::deleteitem(void* item){
	if (item) free(item);
}
