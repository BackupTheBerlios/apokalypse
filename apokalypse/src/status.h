#ifndef STATUS_H
#define STATUS_H

#include "TextString.h"

typedef enum {
	STATUS_ERROR = -1,
	STATUS_OK = 0
} status_code;

class CStatus
{
public:
	CStatus();
	CStatus(status_code code, const char *message = 0);
	virtual ~CStatus() { }

	void SetStatus(status_code code, const char *fmt, ...);
	void SetStatus(status_code code) {
		m_code = code;
		m_message = 0;
	}
	void SetStatusFrom(CStatus &object) {
		m_code = object.Status();
		m_message = object.StatusMessage();
	}
	void SetStatusFrom(CStatus *object) {
		SetStatusFrom(*object);
	}

   void SetClassName(const char *classname){
       if(classname)
          m_classname = strdup(classname);
   }

	status_code Status(void) {
		return(m_code);
	}
	const char *StatusMessage(void) {
		return(m_message);
	}

protected:
	status_code m_code;
	CTextString m_message;
   CTextString m_classname;
};

#endif

