#include <lcthw/dbg.h>
#include <lcthw/tstree.h>
#include <lcthw/bstrlib.h>

void bdestroy_cb(void *value, void *data)
{
    (void)data;
    bdestroy((bstring)value);
}

void destroy_routes(TSTree *routes)
{
    TSTree_traverse(routes, bdestroy_cb, NULL);
    TSTree_destroy(routes);
}

TSTree * add_route_data(TSTree *routes, bstring line)
{
    struct bstrList *tokens = bsplit(line, ' ');
    check(tokens != NULL, "failed to split bstring %s", bdata(line));
    check(tokens->qty == 2, "Invalid routes config format. Expected 2 cols, got %d", tokens->qty);

    bstring route = tokens->entry[0];
    bstring handler = tokens->entry[1];

    routes = TSTree_insert(routes, bdata(route), blength(route), bstrcpy(handler));
    check(routes != NULL, "Failed to insert in TSTree");

    int rc = bstrListDestroy(tokens);
    check(rc == BSTR_OK, "failed to destroy bstrlist");

    return routes;

error:
    if (tokens) bstrListDestroy(tokens);
    if (routes) destroy_routes(routes);

    return NULL;
}

TSTree *load_routes(char *filename)
{
    FILE *file = NULL;
    TSTree *routes = NULL;
    bstring line = NULL;

    file = fopen(filename, "r");
    check(file != NULL, "Failed to open file");

    while ((line = bgets((bNgetc)fgetc, file, '\n')) != NULL)
    {
        int rc = btrimws(line);
        check(rc == BSTR_OK, "failed to trim bstring");

        routes = add_route_data(routes, line);
        check(routes != NULL, "failed to add route data %s", bdata(line));

        bdestroy(line);
    }

    fclose(file);

    return routes;

error:
    if (routes) destroy_routes(routes);
    if (file) fclose(file);
    if (line) bdestroy(line);

    return NULL;
}

bstring read_line(char *prompt)
{
    printf("%s", prompt);
    bstring line = bgets((bNgetc)fgetc, stdin, '\n');
    check(line != NULL, "failed to read line from stdin");

    check(btrimws(line) == BSTR_OK, "failed to trim bstring");

    return line;

error:
    if (line) bdestroy(line);

    return NULL;
}

bstring match_url(const TSTree *routes, bstring term)
{
    bstring res = (bstring)TSTree_search(routes, bdata(term), blength(term));
    if (res == NULL)
    {
        printf("No exact match found. Trying prefix.\n");
        res = (bstring)TSTree_search_prefix(routes, bdata(term), blength(term));
    }

    return res;
}

void run_urlor(TSTree *routes)
{
    bstring res = NULL;
    bstring line = NULL;

    while((line = read_line("URL> ")) != NULL)
    {
        char *cstrline = bdata(line);
        check(strcmp(cstrline, "quit") != 0, "program quit by user");

        res = match_url(routes, line);
        if (res != NULL)
        {
            printf("MATCH: %s\n", bdata(res));
        }
        else
        {
            printf("FAIL: couldn't match %s\n", bdata(line));
        }

        bdestroy(line);
    }

error:
    if (line) bdestroy(line);
}

int main(int argc, char *argv[])
{
    check(argc == 2, "Usage: %s <urlfile>", argv[0]);

    TSTree *routes = load_routes(argv[1]);
    run_urlor(routes);
    destroy_routes(routes);

    return 0;

error:
    return -1;
}

