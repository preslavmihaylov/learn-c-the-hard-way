#include <stdio.h>
#include <string.h>
#include <dbg.h>
#include <commands.h>
#include <apr_general.h>
#include <apr_getopt.h>

#define MAX_OPTS_LEN 50

static void initCmdArgs(apr_getopt_t **options,
    int argc, const char * const * argv);
static void parseCmdArgs(apr_getopt_t *options);

int main(int argc, const char * const * argv)
{
    apr_initialize();

    apr_getopt_t *options;
    initCmdArgs(&options, argc, argv);
    parseCmdArgs(options);

    apr_terminate();
}

static void initCmdArgs(apr_getopt_t **options,
    int argc, const char * const * argv)
{
    apr_pool_t *pool;
    apr_pool_create(&pool, NULL);

    apr_getopt_init(options, pool, argc, argv);

    apr_pool_destroy(pool);
}

static void parseCmdArgs(apr_getopt_t *options)
{
    char opt;
    const char * optArgument;
    char configOpts[MAX_OPTS_LEN] = { 0 };
    char makeOpts[MAX_OPTS_LEN] = { 0 };
    char installOpts[MAX_OPTS_LEN] = { 0 };
    CommandType cmdType;

    while (apr_getopt(options, "I:Lc:m:i:d:SF:B:", &opt, &optArgument) == APR_SUCCESS)
    {
        switch (opt)
        {
            case 'I':
            {
                cmdType = COMMAND_INSTALL;
                break;
            }
            case 'L':
            {
                cmdType = COMMAND_LIST;
                break;
            }
            case 'S':
            {
                cmdType = COMMAND_INIT;
                break;
            }
            case 'F':
            {
                cmdType = COMMAND_FETCH;
                break;
            }
            case 'B':
            {
                cmdType = COMMAND_BUILD;
                break;
            }
            case 'c':
            {
                strncpy(configOpts, optArgument, MAX_OPTS_LEN);
                break;
            }
            case 'm':
            {
                strncpy(makeOpts, optArgument, MAX_OPTS_LEN);
                break;
            }
            case 'i':
            {
                strncpy(installOpts, optArgument, MAX_OPTS_LEN);
                break;
            }
            case 'd':
            {
                break;
            }
        }

        log_info("CMD Type: %d", cmdType);
        log_info("Config opts: %s", configOpts);
        log_info("Make opts: %s", makeOpts);
        log_info("Install opts: %s", installOpts);
    }
}

