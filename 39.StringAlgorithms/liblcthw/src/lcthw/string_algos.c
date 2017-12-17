#include <lcthw/string_algos.h>

static inline void String_setup_skip_chars(
	size_t *skipChars, const unsigned char *term, ssize_t length);

static inline const unsigned char *String_base_search(
	const unsigned char *text, ssize_t textLength,
	const unsigned char *term, ssize_t termLength,
	size_t *skipChars);

int String_find(bstring in, bstring what)
{
	// TODO: Add safety checks
	const unsigned char *text = (const unsigned char *)bdata(in);
	ssize_t textLength = blength(in);

	const unsigned char *term = (const unsigned char *)bdata(what);
	ssize_t termLength = blength(what);

	size_t skipChars[UCHAR_MAX + 1];

	String_setup_skip_chars(skipChars, term, termLength);
	const unsigned char *found =
		String_base_search(text, textLength, term, termLength, skipChars);

	return found != NULL ? found - text : -1;
}

StringScanner *StringScanner_create(bstring in)
{
	// TODO:
	return NULL;
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

static inline void String_setup_skip_chars(
	size_t *skipChars, const unsigned char *term, ssize_t length)
{
	int i;

	for (i = 0; i < UCHAR_MAX + 1; i++)
	{
		skipChars[i] = length;
	}

	for (i = 0; i < length - 1; i++)
	{
		skipChars[term[i]] = length - i - 1;
	}
}

static inline const unsigned char *String_base_search(
	const unsigned char *text, ssize_t textLength,
	const unsigned char *term, ssize_t termLength,
	size_t *skipChars)
{
	int termIndex = 0;
	while (textLength >= termLength)
	{
		termIndex = termLength - 1;

		while (termIndex >= 0)
		{
			if (term[termIndex] != text[termIndex]) break;
			--termIndex;
		}

		if (termIndex < 0) return text;

		int indicesToSkip = skipChars[text[termLength - 1]];
		text += indicesToSkip;
		textLength -= indicesToSkip;
	}

	return NULL;
}
