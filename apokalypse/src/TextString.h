#ifndef TEXTSTRING_H
#define TEXTSTRING_H

#include <stdlib.h>
#include <string.h>

class CTextString {
public:
	/* Constructors */
	CTextString() {
		m_string = 0;
	}
	CTextString(const char *string) {
		m_string = 0;
		*this = string;
	}

	/* Destructor */
	~CTextString() {
		if ( m_string ) {
			free(m_string);
		}
	}

	/* Assignment operators */
	const char *operator =(const char *string) {
		if ( m_string ) {
			free(m_string);
			m_string = 0;
		}
		if ( string ) {
			m_string = strdup(string);
		}
		return(string);
	}
	const CTextString &operator =(const CTextString &string) {
		*this = string.m_string;
		return(string);
	}

	/* Conversion operators */
	operator const char *() {
		return(m_string);
	}

protected:
	char *m_string;
};

#endif

