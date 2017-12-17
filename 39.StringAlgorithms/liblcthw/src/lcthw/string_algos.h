#ifndef LCTHW_STRING_ALGOS_H
#define LCTHW_STRING_ALGOS_H

#include <lcthw/bstrlib.h>
#include <lcthw/darray.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct StringScanner {
	bstring input;
	const unsigned char *text;
	ssize_t textLength;
	const unsigned char *term;
	ssize_t termLength;
	size_t skip_chars[UCHAR_MAX + 1];
} StringScanner;

int String_find(bstring in, bstring what);
StringScanner *StringScanner_create(bstring in);
int StringScanner_scan(StringScanner *scan, bstring toFind);
void StringScanner_destroy(StringScanner *scan);

#endif // LCTHW
