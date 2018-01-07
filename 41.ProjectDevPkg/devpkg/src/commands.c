#include <unistd.h>
#include <commands.h>
#include <apr_uri.h>
#include <apr_fnmatch.h>
#include <bstrlib.h>
#include <dbg.h>
#include <shell.h>
#include <db.h>

static int Command_fetchAndUntar(
	apr_pool_t *pool, const char *urlScheme, const char *url,
	const char *targetSrcDir, const char *targetBuildDir);

int Command_fetch(const char *url)
{
	int rc;
	apr_uri_t info;
	apr_pool_t *pool = NULL;
	const char *dependsPath;

	rc = apr_pool_create(&pool, NULL);
	check(rc == APR_SUCCESS, "Failed to create a pool");

	rc = apr_uri_parse(pool, url, &info);
	check(rc == APR_SUCCESS, "Failed to parse URL: %s", url);

	if (apr_fnmatch(GIT_PAT, info.path, 0) == APR_SUCCESS)
	{
		rc = Shell_exec(GIT_SH, "URL", url, NULL);
		check(rc == 0, "Failed to clone %s to %s", url, BUILD_DIR);
	}
	else if (apr_fnmatch(TAR_GZ_PAT, info.path, 0) == APR_SUCCESS)
	{
		rc = Command_fetchAndUntar(
			pool, info.scheme, url, TAR_GZ_SRC, BUILD_DIR);
		check(rc == 0, "Failed fetch and untar");
	}
	else if (apr_fnmatch(TAR_BZ2_PAT, info.path, 0) == APR_SUCCESS)
	{
		rc = Command_fetchAndUntar(
			pool, info.scheme, url, TAR_BZ2_SRC, BUILD_DIR);
		check(rc == 0, "Failed fetch and untar");
	}
	else if (apr_fnmatch(DEPEND_PAT, info.path, 0) == APR_SUCCESS)
	{
		if (info.scheme)
		{
			dependsPath = DEPENDS_PATH;
			rc = Shell_exec(
				CURL_SH, "TARGET", dependsPath, "URL", url, NULL);
			check(rc == 0, "Failed to fetch DEPENDS file %s", url);
		}
		else
		{
			dependsPath = url;
		}

		rc = Command_depends(dependsPath);
		check(rc == 0, "Failed installing dependencies of %s", url);

		return COMMAND_OK;
	}
	else
	{
		sentinel("Don't know how to handle this type of file %s", url);
	}

	if (pool) apr_pool_destroy(pool);
	return COMMAND_NEEDS_INSTALL;

error:
	if (pool) apr_pool_destroy(pool);
	return COMMAND_ERR;
}

int Command_install(
	const char *url, const char *configure_opts, const char *make_opts,
	const char *install_opts)
{
	int rc = 0;

	rc = Shell_exec(CLEANUP_SH, NULL);
	check(rc == 0, "Failed cleanup before install");

	rc = DB_find(url);
	check(rc != DB_ERR, "Failed querying database");

	if (rc == DB_FOUND)
	{
		log_info("package %s already installed", url);
		return 0;
	}

	rc = Command_fetch(url);
	check(rc != -1, "Failed fetching");

	if (rc == 1)
	{
		rc = Command_build(url, NULL, NULL, NULL);
		check(rc == 0, "Failed building package");
	}
	else
	{
		// DEPENDS already built
	}

	rc = Shell_exec(CLEANUP_SH, NULL);
	check(rc == 0, "Failed cleanup after install");

	return COMMAND_OK;

error:

	return COMMAND_ERR;
}

int Command_depends(const char *path)
{
	FILE *dependsFile = NULL;
	struct bStream *stream = NULL;
	bstring line = bfromcstr("");
	int rc = 0;

	check(access(path, X_OK | W_OK | R_OK) == 0,
		"Cannot access DEPENDS file: %s", path);

	dependsFile = fopen(path, "r");
	check(dependsFile != NULL,
		"Failed to fopen DEPENDS file: %s", path);

	stream = bsopen((bNread)fread, dependsFile);
	check(stream != NULL, "Failed to initialize bstream");

	while (bsreadln(line, stream, '\n') == BSTR_OK)
	{
		btrimws(line);

		log_info("Building dependent package %s", bdata(line));
		rc = Command_install(bdata(line), NULL, NULL, NULL);
		check(rc == 0,
			"Failed installing dependent package %s", bdata(line));
	}

	if (dependsFile) fclose(dependsFile);
	if (stream) bsclose(stream);
	if (line) bdestroy(line);

	return COMMAND_OK;

error: // fallthrough
	if (dependsFile) fclose(dependsFile);
	if (stream) bsclose(stream);
	if (line) bdestroy(line);

	return COMMAND_ERR;
}

int Command_build(
	const char *url, const char *configure_opts, const char *make_opts,
	const char *install_opts)
{
	int rc = 0;

	rc = access(BUILD_DIR, X_OK | W_OK | R_OK);
	check(rc == 0, "Cannot access build directory: %s", BUILD_DIR);

	if (access(CONFIG_SCRIPT, X_OK | W_OK | R_OK) == 0)
	{
		rc = Shell_exec(CONFIGURE_SH, "OPTS", configure_opts, NULL);
		check(rc == 0, "Failed configure step");
	}

	rc = Shell_exec(MAKE_SH, "OPTS", make_opts, NULL);
	check(rc == 0, "Failed make step");

	install_opts = install_opts ? install_opts : "install";
	rc = Shell_exec(INSTALL_SH, "OPTS", install_opts, NULL);
	check(rc == 0, "Failed install step");

	rc = Shell_exec(CLEANUP_SH, NULL);
	check(rc == 0, "Failed cleanup step");

	rc = DB_update(url);
	check(rc == DB_OK, "Failed to add package to database");

	return COMMAND_OK;

error:
	return COMMAND_ERR;
}

static int Command_fetchAndUntar(
	apr_pool_t *pool, const char *urlScheme, const char *url,
	const char *targetSrcDir, const char *targetBuildDir)
{
	int rc = 0;
	Shell tarCommand =
		apr_fnmatch(TAR_GZ_PAT, url, 0) == APR_SUCCESS ?
			TAR_GZ_SH : TAR_BZ2_SH;

	if (urlScheme)
	{
		rc = Shell_exec(CURL_SH, "TARGET", targetSrcDir, "URL", url, NULL);
		check(rc == 0, "Failed to curl %s into %s", url, targetSrcDir);
	}

	rc = apr_dir_make_recursive(targetBuildDir,
		APR_FPROT_GREAD | APR_FPROT_GWRITE | APR_FPROT_GEXECUTE |
		APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
		pool);
	check(rc == APR_SUCCESS,
		"Failed to create build directory: %s", targetBuildDir);

	rc = Shell_exec(tarCommand, "FILE", targetSrcDir, NULL);
	check(rc == 0, "Failed to untar %s", targetSrcDir);

	return COMMAND_OK;

error:
	return COMMAND_ERR;
}

