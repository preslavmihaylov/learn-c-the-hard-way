#include "minunit.h"
#include <lcthw/tstree.h>

char *test_insert()
{
    {
        TSTree *res = TSTree_insert(NULL, NULL, 0, NULL);
        mu_assert(res == NULL, "Didn't return NULL when given key NULL");
    }

    {
        char *str = "Hello";
        TSTree *res = TSTree_insert(NULL, str, 0, str);
        mu_assert(res == NULL, "Didn't return NULL when given len 0");
    }

    {
        char *str = "p";
        TSTree *res = TSTree_insert(NULL, str, strlen(str), str);
        mu_assert(res != NULL, "TSTree was unexpectedly NULL");
        mu_assert(res->splitchar == 'p', "Incorrect splitchar");
        mu_assert(res->value == str, "Incorrect value");
    }

    {
        char *str1 = "a";
        char *str2 = "b";
        TSTree *res = TSTree_insert(NULL, str1, strlen(str1), str1);
        res = TSTree_insert(res, str2, strlen(str2), str2);

        mu_assert(res != NULL, "TSTree was unexpectedly NULL");
        mu_assert(res->splitchar == 'a', "Incorrect splitchar");
        mu_assert(res->value == str1, "Incorrect value");

        mu_assert(res->right != NULL, "TSTree right node incorrect");
        mu_assert(res->right->splitchar == 'b', "Incorrect right node splitchar");
        mu_assert(res->right->value == str2, "Incorrect right node value");
    }

    {
        char *str1 = "c";
        char *str2 = "b";
        TSTree *res = TSTree_insert(NULL, str1, strlen(str1), str1);
        res = TSTree_insert(res, str2, strlen(str2), str2);

        mu_assert(res != NULL, "TSTree was unexpectedly NULL");
        mu_assert(res->splitchar == 'c', "Incorrect splitchar");
        mu_assert(res->value == str1, "Incorrect value");
        
        mu_assert(res->left != NULL, "TSTree left node NULL");
        mu_assert(res->left->splitchar == 'b', "Incorrect left node splitchar");
        mu_assert(res->left->value == str2, "Incorrect left node value");
    }

    {
        char *str1 = "ab";
        TSTree *res = TSTree_insert(NULL, str1, strlen(str1), str1);

        mu_assert(res != NULL, "TSTree was unexpectedly NULL");
        mu_assert(res->splitchar == 'a', "Incorrect first node splitchar");
        mu_assert(res->value == NULL, "Incorrect first node value");
        
        mu_assert(res->equal != NULL, "second node unexpectedly NULL");
        mu_assert(res->equal->splitchar == 'b', "Incorrect second node splitchar");
        mu_assert(res->equal->value == str1, "Incorrect second node value");
    }

    {
        char *str1 = "abc";
        char *str2 = "ab";
        char *str3 = "a";
        TSTree *res = TSTree_insert(NULL, str1, strlen(str1), str1);
        res = TSTree_insert(res, str2, strlen(str2), str2);
        res = TSTree_insert(res, str3, strlen(str3), str3);

        mu_assert(res != NULL, "TSTree was unexpectedly NULL");
        mu_assert(res->splitchar == 'a', "Incorrect first node splitchar");
        mu_assert(res->value == str3, "Incorrect first node value");

        mu_assert(res->equal != NULL, "second node unexpectedly NULL");
        mu_assert(res->equal->splitchar == 'b', "Incorrect second node splitchar");
        mu_assert(res->equal->value == str2, "Incorrect second node value");
        
        mu_assert(res->equal->equal != NULL, "third node unexpectedly NULL");
        mu_assert(res->equal->equal->splitchar == 'c', "Incorrect third node splitchar");
        mu_assert(res->equal->equal->value == str1, "Incorrect third node value");
    }

    {
        char *str1 = "bbc";
        char *str2 = "bb";
        char *str3 = "b";

        char *lstr1 = "abc";
        char *lstr2 = "ab";
        char *lstr3 = "a";

        char *rstr1 = "cbc";
        char *rstr2 = "cb";
        char *rstr3 = "c";

        TSTree *res = TSTree_insert(NULL, str1, strlen(str1), str1);
        res = TSTree_insert(res, str2, strlen(str2), str2);
        res = TSTree_insert(res, str3, strlen(str3), str3);

        res = TSTree_insert(res, lstr1, strlen(lstr1), lstr1);
        res = TSTree_insert(res, lstr2, strlen(lstr2), lstr2);
        res = TSTree_insert(res, lstr3, strlen(lstr3), lstr3);

        res = TSTree_insert(res, rstr1, strlen(rstr1), rstr1);
        res = TSTree_insert(res, rstr2, strlen(rstr2), rstr2);
        res = TSTree_insert(res, rstr3, strlen(rstr3), rstr3);

        // equal branch
        mu_assert(res != NULL, "TSTree was unexpectedly NULL");
        mu_assert(res->splitchar == 'b', "Incorrect first node splitchar");
        mu_assert(res->value == str3, "Incorrect first node value");

        mu_assert(res->equal != NULL, "second node unexpectedly NULL");
        mu_assert(res->equal->splitchar == 'b', "Incorrect second node splitchar");
        mu_assert(res->equal->value == str2, "Incorrect second node value");
        
        mu_assert(res->equal->equal != NULL, "third node unexpectedly NULL");
        mu_assert(res->equal->equal->splitchar == 'c', "Incorrect third node splitchar");
        mu_assert(res->equal->equal->value == str1, "Incorrect third node value");
        
        // left branch
        TSTree *lres = res->left;
        mu_assert(lres != NULL, "TSTree was unexpectedly NULL");
        mu_assert(lres->splitchar == 'a', "Incorrect first node splitchar");
        mu_assert(lres->value == lstr3, "Incorrect first node value");

        mu_assert(lres->equal != NULL, "second node unexpectedly NULL");
        mu_assert(lres->equal->splitchar == 'b', "Incorrect second node splitchar");
        mu_assert(lres->equal->value == lstr2, "Incorrect second node value");
        
        mu_assert(lres->equal->equal != NULL, "third node unexpectedly NULL");
        mu_assert(lres->equal->equal->splitchar == 'c', "Incorrect third node splitchar");
        mu_assert(lres->equal->equal->value == lstr1, "Incorrect third node value");

        // right branch
        TSTree *rres = res->right;
        mu_assert(rres != NULL, "TSTree was unexpectedly NULL");
        mu_assert(rres->splitchar == 'c', "Incorrect first node splitchar");
        mu_assert(rres->value == rstr3, "Incorrect first node value");

        mu_assert(rres->equal != NULL, "second node unexpectedly NULL");
        mu_assert(rres->equal->splitchar == 'b', "Incorrect second node splitchar");
        mu_assert(rres->equal->value == rstr2, "Incorrect second node value");
        
        mu_assert(rres->equal->equal != NULL, "third node unexpectedly NULL");
        mu_assert(rres->equal->equal->splitchar == 'c', "Incorrect third node splitchar");
        mu_assert(rres->equal->equal->value == rstr1, "Incorrect third node value");
    }

    {
        char *str1 = "a";
        char *str2 = "a";
        TSTree *res = TSTree_insert(NULL, str1, strlen(str1), str1);
        res = TSTree_insert(res, str2, strlen(str2), str2);

        mu_assert(res == NULL, "Expected NULL as duplicates are not allowed");
    }

    return NULL;
}

char *test_search_exact()
{
    return NULL;
}

char *test_search_prefix()
{
    return NULL;
}

char *test_traverse()
{
    return NULL;
}

char *test_destroy()
{
    return NULL; 
}

char *all_tests()
{
    mu_suite_start();
    
    mu_run_test(test_insert);
    mu_run_test(test_search_exact);
    mu_run_test(test_search_prefix);
    mu_run_test(test_traverse);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
