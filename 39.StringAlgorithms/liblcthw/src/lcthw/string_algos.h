#ifndef LCTHW_STRING_ALGOS_H
#define LCTHW_STRING_ALGOS_H

#include <lcthw/bstrlib.h>
#include <lcthw/darray.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct StringScanner {
	bstring inputText;
	const unsigned char *text;
	ssize_t textLength;
	bstring inputTerm;
	const unsigned char *term;
	ssize_t termLength;
	size_t skipChars[UCHAR_MAX + 1];
} StringScanner;

int String_find(bstring inputText, bstring inputTerm);
StringScanner *StringScanner_create(bstring inputText);
int StringScanner_scan(StringScanner *scanner, bstring toFind);
void StringScanner_destroy(StringScanner *scanner);

#endif // LCTHW
