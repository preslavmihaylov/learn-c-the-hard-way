#include "minunit.h"
#include <lcthw/bstrlib.h>
#include <stdio.h>

char *bfromcstr_test()
{
	bstring bstr;
	char *cstr;
	
	bstr = bfromcstr("Hello world!");
	cstr = bstr2cstr(bstr, 'a');
	mu_assert(strcmp("Hello world!", cstr) == 0, 
			  "failed to return proper cstring in normal case");
	
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

char *bfromcstrrangealloc_test()
{
	bstring bstr;
	char *cstr;
	
	bstr = bfromcstrrangealloc(5, 20, "Hello world");
	cstr = bstr2cstr(bstr, 0);
	mu_assert(strcmp("Hello world", cstr) == 0, 
			  "failed bfromcstrrangealloc normal case");
	
	bcstrfree(cstr);
	bdestroy(bstr);
	
	bstr = bfromcstrrangealloc(2, 4, "Hell");
	cstr = bstr2cstr(bstr, 0);
	mu_assert(strcmp("Hell", cstr) == 0, 
			  "failed bfromcstrrangealloc when maxl == string length");
	
	bcstrfree(cstr);	
	bdestroy(bstr);

	bstr = bfromcstrrangealloc(2, 3, "Hell");
	cstr = bstr2cstr(bstr, 0);
	mu_assert(strcmp("Hel", cstr) == 0, 
			  "failed bfromcstrrangealloc when maxl < string length");
	
	bcstrfree(cstr);	
	bdestroy(bstr);
	
	return NULL;
}

char *all_tests()
{
    mu_suite_start();

	mu_run_test(bfromcstr_test);
    mu_run_test(bfromcstralloc_test);
    mu_run_test(bfromcstrrangealloc_test);

	return NULL;
}

RUN_TESTS(all_tests);
