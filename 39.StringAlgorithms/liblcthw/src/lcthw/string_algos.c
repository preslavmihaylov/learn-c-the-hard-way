#include <lcthw/string_algos.h>

static inline void StringScanner_reset(StringScanner *scanner);
static inline void String_setup_skip_chars(
	size_t *skipChars, const unsigned char *term, ssize_t length);

static inline const unsigned char *String_base_search(
	const unsigned char *text, ssize_t textLength,
	const unsigned char *term, ssize_t termLength,
	size_t *skipChars);

int String_find(bstring inputText, bstring inputTerm)
{
	check(inputText != NULL, "input text cannot be NULL");
	check(inputTerm != NULL, "input search term cannot be NULL");

	const unsigned char *text = (const unsigned char *)bdata(inputText);
	ssize_t textLength = blength(inputText);

	const unsigned char *term = (const unsigned char *)bdata(inputTerm);
	ssize_t termLength = blength(inputTerm);

	size_t skipChars[UCHAR_MAX + 1];

	String_setup_skip_chars(skipChars, term, termLength);
	const unsigned char *found =
		String_base_search(text, textLength, term, termLength, skipChars);

	return found != NULL ? found - text : -1;

error:
	return -1;
}

StringScanner *StringScanner_create(bstring inputText)
{
	check(inputText != NULL, "Input string cannot be NULL");

	StringScanner *scanner = malloc(sizeof(StringScanner));
	check_mem(scanner);

	scanner->inputText = bstrcpy(inputText);
	scanner->term = NULL;
	scanner->termLength = 0;

	StringScanner_reset(scanner);

	return scanner;

error:
	StringScanner_destroy(scanner);
	return NULL;
}


int StringScanner_scan(StringScanner *scanner, bstring toFind)
{
	// TODO:
	return 0;
}

void StringScanner_destroy(StringScanner *scanner)
{
	if (scanner)
	{
		bdestroy(scanner->inputText);
		bdestroy(scanner->inputTerm);

		free(scanner);
	}
}

static inline void StringScanner_reset(StringScanner *scanner)
{
	check(scanner != NULL, "Scanner cannot be NULL");
	check(scanner->inputText != NULL, "Scanner text cannot be NULL");

	scanner->text = (const unsigned char *)bdata(scanner->inputText);
	scanner->textLength = blength(scanner->inputText);

error: // fallthrough
	return;
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
