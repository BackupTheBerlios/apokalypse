
#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <stdlib.h>

#ifndef MIN
/**
* @return Minimum von a und b
*/
inline int MIN(int a, int b){
	return (a < b) ? a : b;
	}
#endif


#ifndef MAX
/**
* @return Maximum von a und b
*/
inline int MAX(int a, int b){
	return (a > b) ? a : b;
	}
#endif

#define CHECKPTR(ptr) if (!ptr){fprintf(stderr,"\nERROR, POINTER IS NULL!!!\n");exit(1);}

#endif

