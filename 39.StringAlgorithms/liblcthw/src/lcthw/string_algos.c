#include <lcthw/string_algos.h>

static inline void String_setup_skip_chars(
	size_t *skip_chars, const unsigned char *searchedTerm, ssize_t length)
{
	int i;

	for (i = 0; i < UCHAR_MAX + 1; i++)
	{
		skip_chars[i] = length;
	}

	for (i = 0; i < length; i++)
	{
		skip_chars[searchedTerm[i]] = length - i - 1;
	}
}

StringScanner *StringScanner_create(bstring in)
{
	// TODO:
	return NULL;
}

int String_find(bstring in, bstring what)
{
	// TODO:
	return 0;
}

int StringScanner_scan(StringScanner *scan, bstring toFind)
{
	// TODO:
	return 0;
}

void StringScanner_destroy(StringScanner *scan)
{
	// TODO:
}

