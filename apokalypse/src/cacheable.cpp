
#include "cacheable.h"

Cacheable::Cacheable(const TString& name) : CStatus() {
	ref_cnt = 1;
	this->name = name;
	SetClassName("Cacheable");
}

Cacheable::~Cacheable(){
}

void Cacheable::addRef(){
	++ref_cnt;
}

void Cacheable::delRef(){
	/* Free this object when it has a count of 0 */
	if ( --ref_cnt == 0 ) {
		delete this;
		}
}

int Cacheable::refCnt() const{
	return(ref_cnt);
}

const TString& Cacheable::getName() const{
	return name;
}


