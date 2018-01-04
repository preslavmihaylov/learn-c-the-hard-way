#include <stdio.h>
#include <bstrlib.h>
#include <db.h>
#include <apr_general.h>

int main(int argc, char *argv[])
{
	apr_initialize();
	DB_init();

	DB_update("Hello world");
	bool res1 = DB_find("Hello world");
	bool res2 = DB_find("Hello worl");
	printf("Hello world found? %d\n", res1);
	printf("Hello worl found? %d\n", res2);
	apr_terminate();
}
