#include <commands.h>

int Command_fetch(apr_pool_t *p, const char *url, int fetch_only)
{
	return -1;
}

int Command_install(
	apr_pool_t *p,
	const char *url,
	const char *configure_opts,
	const char *make_opts,
	const char *install_opts)
{
	return -1;
}

int Command_depends(apr_pool_t *p, const char *path)
{
	return -1;
}

int Command_build(
	apr_pool_t *p,
	const char *url,
	const char *configure_opts,
	const char *make_opts,
	const char *install_opts)
{
	return -1;
}

