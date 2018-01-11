#include <stdio.h>
#include <string.h>
#include <dbg.h>
#include <commands.h>
#include <db.h>
#include <apr_general.h>
#include <apr_getopt.h>

#define MAX_OPTS_LEN 50

static void initCmdArgs(apr_getopt_t **options,
    int argc, const char * const * argv);
static void parseCmdArgs(apr_getopt_t *options);
static void executeCmd(CommandType cmdType,
    const char *url, const char *configOpts, const char *makeOpts,
    const char *installOpts);

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
    const char *optArgument;
    char url[MAX_OPTS_LEN];
    char configOpts[MAX_OPTS_LEN] = { 0 };
    char makeOpts[MAX_OPTS_LEN] = { 0 };
    char installOpts[MAX_OPTS_LEN] = { 0 };
    CommandType cmdType = COMMAND_NONE;

    while (apr_getopt(options, "I:Lc:m:i:SF:B:", &opt, &optArgument) == APR_SUCCESS)
    {
        switch (opt)
        {
            case 'I':
            {
                check(cmdType == COMMAND_NONE,
                    "Cannot specify more than one command type");
                cmdType = COMMAND_INSTALL;
                check(url != NULL, "Install command expects an argument");
                strncpy(url, optArgument, MAX_OPTS_LEN);

                break;
            }
            case 'L':
            {
                check(cmdType == COMMAND_NONE,
                    "Cannot specify more than one command type");
                cmdType = COMMAND_LIST;

                break;
            }
            case 'S':
            {
                check(cmdType == COMMAND_NONE,
                    "Cannot specify more than one command type");
                cmdType = COMMAND_INIT;

                break;
            }
            case 'F':
            {
                check(cmdType == COMMAND_NONE,
                    "Cannot specify more than one command type");
                check(url != NULL, "Fetch command expects an argument");
                cmdType = COMMAND_FETCH;
                strncpy(url, optArgument, MAX_OPTS_LEN);

                break;
            }
            case 'B':
            {
                check(cmdType == COMMAND_NONE,
                    "Cannot specify more than one command type");
                check(url != NULL, "Build command expects an argument");
                cmdType = COMMAND_BUILD;
                strncpy(url, optArgument, MAX_OPTS_LEN);

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
        }
    }

    check(cmdType != COMMAND_NONE, "No command specified.");
    executeCmd(cmdType, url, configOpts, makeOpts, installOpts);

error: // fallthrough
    return;
}

static void executeCmd(CommandType cmdType,
    const char *url, const char *configOpts, const char *makeOpts,
    const char *installOpts)
{
    int rc = 0;

    switch (cmdType)
    {
        case COMMAND_INSTALL:
        {
            rc = Command_install(url, configOpts, makeOpts, installOpts);
            check(rc == 0, "Failed to install %s", url);

            break;
        }
        case COMMAND_LIST:
        {
            int rc = DB_list();
            check(rc == 0, "Failed to list database contents");

            break;
        }
        case COMMAND_FETCH:
        {
            rc = Command_fetch(url);
            check(rc == 0, "Failed to fetch %s", url);
            log_info("Downloaded to %s and in /tmp/", BUILD_DIR);

            break;
        }
        case COMMAND_INIT:
        {
            rc = DB_init();
            check(rc == 0, "Failed to create devpkg database");

            break;
        }
        case COMMAND_BUILD:
        {
            rc = Command_build(url, configOpts, makeOpts, installOpts);
            check(rc == 0, "Failed to build %s", url);

            break;
        }
        default:
        {
            sentinel("Invalid command given");
        }
    }

error: // fallthrough
    return;
}
