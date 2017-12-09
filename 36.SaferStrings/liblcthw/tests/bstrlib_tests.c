#include "minunit.h"
#include <lcthw/bstrlib.h>
#include <stdio.h>
#include <stdbool.h>

char *bfromcstr_test()
{
	bstring bstr;
	char *cstr;
	
	bstr = bfromcstr("Hello world!");
	cstr = bstr2cstr(bstr, 'a');
	mu_assert(strcmp("Hello world!", cstr) == 0, 
			  "failed to return proper cstring in normal case");
	
	mu_assert(blength(bstr) == 12, 
			  "blength failed");
	
	bcstrfree(cstr);
	bdestroy(bstr);

	bstr = bfromcstr("");
	cstr = bstr2cstr(bstr, 'a');
	mu_assert(strcmp("", cstr) == 0, 
			  "failed to return proper empty cstring");

	bcstrfree(cstr);
	bdestroy(bstr);

	return NULL;
}

char *bfromcstralloc_test()
{
	bstring bstr;
	char *cstr;
	
	bstr = bfromcstralloc(5, "Hello world");
	cstr = bstr2cstr(bstr, 0);
	mu_assert(strcmp("Hello world", cstr) == 0, 
			  "failed bfromcstralloc normal case");
	
	bcstrfree(cstr);
	bdestroy(bstr);
	
	bstr = bfromcstralloc(5, "Hell");
	cstr = bstr2cstr(bstr, 0);
	mu_assert(strcmp("Hell", cstr) == 0, 
			  "failed bfromcstralloc edge case");
	
	bcstrfree(cstr);	
	bdestroy(bstr);

	return NULL;
}

char *blk2bstr_test()
{
	bstring bstr;
	char *cstr;
	
	bstr = blk2bstr("Hello world", 12);
	cstr = bstr2cstr(bstr, 0);
	mu_assert(strcmp("Hello world", cstr) == 0, 
			  "failed blk2bstr normal case");
	
	bcstrfree(cstr);
	bdestroy(bstr);
	
	bstr = blk2bstr("Hello world", 5);
	cstr = bstr2cstr(bstr, 0);
	mu_assert(strcmp("Hello", cstr) == 0, 
			  "failed blk2bstr edge case");
	
	bcstrfree(cstr);
	bdestroy(bstr);
	
	return NULL;
}

char *bstrcpy_test()
{
	bstring bstr;
	bstring bstr2;
	char *cstr;
	
	bstr = bfromcstr("Hello world");
	bstr2 = bstrcpy(bstr);
	cstr = bstr2cstr(bstr2, 0);
	mu_assert(strcmp("Hello world", cstr) == 0, 
			  "failed bstrcpy normal case");
	
	bcstrfree(cstr);
	bdestroy(bstr);
	bdestroy(bstr2);
	
	return NULL;
}

char *bassign_funcs_test()
{
	bstring bstr;
	bstring bstr2;
	char *cstr;
	
	bstr = bfromcstr("Hello world");
	bstr2 = bfromcstr("");
	bassign(bstr2, bstr);
	bdestroy(bstr);

	cstr = bstr2cstr(bstr2, 0);
	mu_assert(strcmp("Hello world", cstr) == 0, 
			  "failed bassign normal case");

	bcstrfree(cstr);
	bdestroy(bstr2);

	bstr = bfromcstr("");
	bassigncstr(bstr, "hello");
	
	cstr = bstr2cstr(bstr, 0);
	mu_assert(strcmp("hello", cstr) == 0, 
			  "failed bassigncstr normal case");
	
	bdestroy(bstr);
	bcstrfree(cstr);

	bstr = bfromcstr("");
	bassignblk(bstr, "hello", 2);
	
	cstr = bstr2cstr(bstr, 0);
	mu_assert(strcmp("he", cstr) == 0, 
			  "failed bassignblk normal case");
	
	bdestroy(bstr);
	bcstrfree(cstr);
	
	return NULL;
}

char *bconcat_test()
{
	bstring bstr;
	bstring bstr2;
	char *cstr;
	
	bstr = bfromcstr("Hello");
	bstr2 = bfromcstr(" world");
	bconcat(bstr, bstr2);

	cstr = bstr2cstr(bstr, 0);
	mu_assert(strcmp("Hello world", cstr) == 0, 
			  "failed bconcat normal case");

	bcstrfree(cstr);
	bdestroy(bstr);
	bdestroy(bstr2);

	return NULL;
}

char *bscan_funcs_test()
{
	bstring bstr;
	bstring bstr2;
	//char *cstr;
	
	// bstricmp test
	bstr = bfromcstr("Hello");
	bstr2 = bfromcstr("Hello");
	mu_assert(bstricmp(bstr, bstr2) == 0,
			  "failed bstricmp true case");

	bassigncstr(bstr2, "Hell");
	mu_assert(bstricmp(bstr, bstr2) != 0,
			  "failed bstricmp false case");

	bdestroy(bstr);
	bdestroy(bstr2);

	// biseq test
	bstr = bfromcstr("Hello");
	bstr2 = bfromcstr("Hello");
	mu_assert(biseq(bstr, bstr2) == true,
			  "failed biseq true case");

	bassigncstr(bstr2, "Hell");
	mu_assert(biseq(bstr, bstr2) == false,
			  "failed biseq false case");

	bdestroy(bstr);
	bdestroy(bstr2);

	// binstr test
	bstr = bfromcstr("Hello world");
	bstr2 = bfromcstr("Hello");
	mu_assert(binstr(bstr, 0, bstr2) == 0,
			  "failed binstr true case");

	bassigncstr(bstr2, "Tell");
	mu_assert(binstr(bstr, 0, bstr2) == BSTR_ERR,
			  "failed binstr false case");

	bdestroy(bstr);
	bdestroy(bstr2);
	
	return NULL;
}

char *bfindreplace_test()
{
	bstring bstr;
	bstring bstr2;
	bstring replace;
	char *cstr;
	
	bstr = bfromcstr("Hello world");
	bstr2 = bfromcstr("world");
	replace = bfromcstr("everybody");

	bfindreplace(bstr, bstr2, replace, 0);
	cstr = bstr2cstr(bstr, 0);

	mu_assert(strcmp("Hello everybody", cstr) == 0,
			  "failed bfindreplace true case");

	bdestroy(bstr);
	bdestroy(bstr2);
	bdestroy(replace);
	bcstrfree(cstr);

	bstr = bfromcstr("Hello world");
	bstr2 = bfromcstr("nothing");
	replace = bfromcstr("everybody");

	bfindreplace(bstr, bstr2, replace, 0);
	cstr = bstr2cstr(bstr, 0);

	mu_assert(strcmp("Hello world", cstr) == 0,
			  "failed bfindreplace false case");

	bdestroy(bstr);
	bdestroy(bstr2);
	bdestroy(replace);
	bcstrfree(cstr);
	
	return NULL;
}

char *bformat_test()
{
	bstring bstr;
	char *cstr;
	
	bstr = bformat("%s %s", "Hello", "world");
	cstr = bstr2cstr(bstr, 0);

	mu_assert(strcmp("Hello world", cstr) == 0,
			  "failed bformat");

	bdestroy(bstr);
	bcstrfree(cstr);
	
	return NULL;
}

char *bsplit_test()
{
	bstring bstr;
	struct bstrList *list;
	char *cstr1;
	char *cstr2;
		
	bstr = bfromcstr("Hello world");
	list = bsplit(bstr, ' ');

	cstr1 = bstr2cstr(list->entry[0], 0);
	cstr2 = bstr2cstr(list->entry[1], 0);
	mu_assert(strcmp("Hello", cstr1) == 0, "failed bsplit index 0");
	mu_assert(strcmp("world", cstr2) == 0, "failed bsplit index 1");

	bdestroy(bstr);
	bcstrfree(cstr1);
	bcstrfree(cstr2);
	bstrListDestroy(list);

	return NULL;
}

char *bdata_char_test()
{
	bstring bstr;
	char *cstr;
		
	bstr = bfromcstr("Hello world");

	cstr = bdata(bstr);
	mu_assert(strcmp("Hello world", cstr) == 0, "failed bdata");
	
	char firstCh = bchar(bstr, 0);
	char invalidCh = bchar(bstr, blength(bstr) + 1);
	mu_assert(firstCh == 'H', "failed bchar normal case");
	mu_assert(invalidCh == '\0', "failed bchar invalid case");

	bdestroy(bstr);

	return NULL;
}

char *all_tests()
{
    mu_suite_start();

	mu_run_test(bfromcstr_test);
    mu_run_test(bfromcstralloc_test);
    mu_run_test(blk2bstr_test);
    mu_run_test(bstrcpy_test);
    mu_run_test(bassign_funcs_test);
    mu_run_test(bconcat_test);
    mu_run_test(bscan_funcs_test);
    mu_run_test(bfindreplace_test);
    mu_run_test(bformat_test);
    mu_run_test(bsplit_test);
    mu_run_test(bdata_char_test);

	return NULL;
}

RUN_TESTS(all_tests);
