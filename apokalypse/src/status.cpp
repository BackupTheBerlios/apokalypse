#include <cstdarg>
#include <stdio.h>
#include "status.h"
#include "logging.h"

CStatus::CStatus()
{
	SetStatus(STATUS_OK);
}

CStatus::CStatus(status_code code, const char *message)
{
	SetStatus(code, message);
}

void CStatus::SetStatus(status_code code, const char *fmt, ...)
{
	va_list ap;
	char message[1024];

	m_code = code;
	va_start(ap, fmt);
	vsprintf(message, fmt, ap);
	va_end(ap);
	LogDebug("%s: %s", (const char*)m_classname, message);
	m_message = message;
}


