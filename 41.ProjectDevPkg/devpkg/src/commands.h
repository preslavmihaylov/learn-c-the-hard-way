#ifndef _DEVPKG_COMMANDS_H
#define _DEVPKG_COMMANDS_H

#include <apr_pools.h>

#define DEPENDS_PATH "/tmp/DEPENDS"
#define TAR_GZ_SRC "/tmp/pkg-src.tar.gz"
#define TAR_BZ2_SRC "/tmp/pkg-src.tar.bz2"
#define BUILD_DIR "/tmp/pkg-build"
#define GIT_PAT "*.git"
#define DEPEND_PAT "*DEPENDS"
#define TAR_GZ_PAT "*.tar.gz"
#define TAR_BZ2_PAT "*.tar.bz2"
#define CONFIG_SCRIPT "/tmp/pkg-build/configure"

enum CommandType
{
	COMMAND_NONE,
	COMMAND_INSTALL,
	COMMAND_LIST,
	COMMAND_FETCH,
	COMMAND_INIT,
	COMMAND_BUILD
};

#define COMMAND_ERR -1
#define COMMAND_OK 0
#define COMMAND_NEEDS_INSTALL 1

int Command_fetch(const char *url);
int Command_install(
	const char *url, const char *configure_opts, const char *make_opts,
	const char *install_opts);
int Command_depends(const char *path);
int Command_build(
	const char *url, const char *configure_opts, const char *make_opts,
	const char *install_opts);

#endif // _DEVPKG_COMMANDS_H
