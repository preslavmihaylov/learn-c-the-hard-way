#include <unistd.h>
#include <apr_errno.h>
#include <apr_file_io.h>
#include <bstrlib.h>
#include <db.h>
#include <dbg.h>

static FILE *DB_open(const char *path);
static void DB_close(FILE *db);
static bstring DB_load();

int DB_init()
{
	apr_pool_t *p = NULL;
	apr_pool_create(&p, NULL);

	if (access(DB_DIR, X_OK | W_OK | R_OK) != 0)
	{
		apr_status_t rc = apr_dir_make_recursive(DB_DIR,
			APR_FPROT_GREAD | APR_FPROT_GWRITE | APR_FPROT_GEXECUTE |
			APR_FPROT_UREAD | APR_FPROT_UWRITE | APR_FPROT_UEXECUTE,
			p);

		check(rc == APR_SUCCESS, "Failed to create db directory: %s", DB_DIR);
	}

	if (access(DB_FILE, X_OK | W_OK | R_OK) != 0)
	{
		FILE *db = DB_open(DB_FILE);
		check(db != NULL, "Failed to create db file: %s", DB_FILE);

		DB_close(db);
	}

	apr_pool_destroy(p);
	return 0;

error:
	apr_pool_destroy(p);
	return -1;
}

int DB_list()
{
	bstring dbContents = DB_load();
	check(dbContents != NULL, "Failed to read contents from DB");

	printf("%s", bdata(dbContents));

	bdestroy(dbContents);
	return 0;

error:
	return -1;
}

int DB_update(const char *url)
{
	FILE *db = NULL;
	int rc = -1;

	if (DB_find(url))
	{
		log_info("url %s already exists in DB", url);
		return -1;
	}

	db = DB_open(DB_FILE);
	check(db != NULL, "Failed to open db file: %s", DB_FILE);

	bstring bstr = bfromcstr(url);
	bconchar(bstr, '\n');

	fwrite(bstr->data, blength(bstr), 1, db);

	rc = 0;

error: // fallthrough
	if (db) DB_close(db);

	return rc;
}

bool DB_find(const char *url)
{
	bool found = false;
	bstring dbContents = NULL;
	bstring term = NULL;

	// a whole line must match, not only part of it
	term = bfromcstr("\n");
	bcatcstr(term, url);
	bconchar(term, '\n');

	dbContents = DB_load();
	check(dbContents != NULL, "Failed to read DB contents");

	found = binstr(dbContents, 0, term) != BSTR_ERR ? true : false;

error: // fallthrough
	if (term) bdestroy(term);
	if (dbContents) bdestroy(dbContents);

	return found;
}

static FILE *DB_open(const char *path)
{
	return fopen(path, "a+");
}

static void DB_close(FILE *db)
{
	fclose(db);
}

static bstring DB_load()
{
	FILE *db = NULL;
	bstring dbContents = NULL;

	db = DB_open(DB_FILE);
	check(db != NULL, "Failed to open db file: %s", DB_FILE);

	dbContents = bread((bNread)fread, db);
	check(dbContents != NULL, "Failed to read db contents");

	DB_close(db);
	return dbContents;

error:
	if (db) DB_close(db);
	if (dbContents) bdestroy(dbContents);

	return NULL;
}
