#include <cstdarg>
#include <cstdlib>
#include <stdio.h>
#include "config.h"
#include "logging.h"

void LogAbort(const char *fmt, ...)
{
	va_list ap;

	fprintf(stderr, "ABORT: ");
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	abort();
}

void LogWarning(const char *fmt, ...)
{
	va_list ap;

	fprintf(stderr, "WARNING: ");
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
}

void LogDebug(const char *fmt, ...)
{
#ifdef DEBUG
	va_list ap;

	fprintf(stderr, "DEBUG: ");
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fprintf(stderr, "\n");
#endif
}


