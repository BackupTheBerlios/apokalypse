
#ifndef RESOURCECACHE_H
#define RESOURCECACHE_H

#include "libcpputil/tlist.h"
#include "libcpputil/tstring.h"
#include "status.h"
#include "logging.h"

template<class T> class ResourceCache : public CStatus{
public:
	ResourceCache() : CStatus() {
		SetClassName("ResourceCache");
		}

	~ResourceCache() {
		flush();
		}

	T *request(const TString &name) {
		T *data = 0;
		if (!name.isEmpty()) {
			data = find(name);
			if (!data) {
				data = load(name);
				}
			if (data){
				data->addRef();
				}
			}
		return(data);
		}

	void release(T *data) {
		if (data) {
			if (data->refCnt() == 1) {
				LogWarning("Tried to release cached object (%s)", data->getName().text());
				} else {
				data->delRef();
				}
			}
		}

	/** Clear all objects from the cache */
	void flush(){
		list.clear();
		}

	/**
	 * Clear all unused objects from the cache
	 * This could be faster if the link pointer wasn't trashed by
	 * the unload operation...
	*/
	void garbageCollect() {
		T *link;
		int n_collected = 0;

		for (link = list.getFirst(); link != 0; ) {
			if (link->refCnt() == 1) {
				unLoad(link);
				n_collected++;
				link = list.getFirst();
				}else
				link = list.getNext();
			}
		LogDebug("Cache: %d objects garbage collected", n_collected);
        }

protected:
	TList<T> list;

	T *find(const TString &name) {
		T *link = 0;
		T *data = 0;
		for ( link = list.getFirst(); link; link = list.getNext() ) {
			if ( link->getName() == name ) {
				data = link;
				break;
				}
			}
		return(data);
		}

	T *load(const TString &file) {
		T *link = 0;
		link = new T(file);
		if ( link->Status() == STATUS_OK ) {
			list.append(link);
			LogDebug("%s loaded into cache.", file.text());
			} else {
			SetStatusFrom(link);
			delete link;
			link = 0;
			}
		return(link);
		}

	void unLoad(T *link) {
		if (list.getCurrent() == link){
			/* Free the object, if it's not in use */
			if (link->refCnt() != 1) {
				LogWarning("Unloading cached object in use");
				}
			list.remove(link);
			}else{
			if (list.findRev(link) == link){
				/* Free the object, if it's not in use */
				if ( link->refCnt() != 1 ) {
					LogWarning("Unloading cached object in use");
					}
				list.remove(link);
				}else
				LogWarning("Couldn't find object in cache");
			}
		}
};

#endif

