#ifndef LCTHW_STRING_ALGOS_H
#define LCTHW_STRING_ALGOS_H

#include <lcthw/bstrlib.h>
#include <lcthw/darray.h>

typedef struct StringScanner {
	bstring in;
	const unsigned char *haystack;
	ssize_t hlen;
	const unsigned char *needle;
	ssize_t nlen;
	size_t skip_chars[UCHAR_MAX + 1];
} StringScanner;

StringScanner *StringScanner_create(bstring in);
int String_find(bstring in, bstring what);
int StringScanner_scan(StringScanner *scan, bstring toFind);
void StringScanner_destroy(StringScanner *scan);

#endif // LCTHW
