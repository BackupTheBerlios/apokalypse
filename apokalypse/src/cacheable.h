
#ifndef CACHEABLE_H
#define CACHEABLE_H

#include "libcpputil/tstring.h"
#include "status.h"
#include "logging.h"

/**
 * Cacheable ist die Basisklasse für alle mit dem Ressourcenmanager
 * behandelbaren Objekte (Images, Sounds, ...)
 */
class Cacheable : public CStatus{
public:
	Cacheable(const TString& name);
	virtual ~Cacheable();
	const TString& getName() const;
	int refCnt() const;
	void addRef();
	void delRef();

private:
	int ref_cnt;
	TString name;
};

#endif


