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
    (void)route;
    (void)handler;

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

char *read_line(char *prompt)
{
    printf("%s", prompt);
    bstring bline = bgets((bNgetc)fgetc, stdin, '\n');
    check(bline != NULL, "failed to read line from stdin");

    int rc = btrimws(bline);
    check(rc == BSTR_OK, "failed to trim bstring");

    char *line = bstr2cstr(bline, 0);
    bdestroy(bline);

    return line;

error:
    return NULL;
}

void run_urlor(TSTree *routes)
{
    char *line;

    while((line = read_line("URL> ")) != NULL)
    {
        check(strcmp(line, "quit") == 0, "program quit by user");

        printf("%s\n", line);
        bcstrfree(line);
    }

error:
    if (line) bcstrfree(line);
}

int main(int argc, char *argv[])
{
    TSTree *routes = load_routes("temp.txt");

    run_urlor(routes);
    destroy_routes(routes);
}

