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
	bool res3 = DB_find("world");
	printf("Hello world found? %d\n", res1);
	printf("Hello worl found? %d\n", res2);
	printf("world found? %d\n", res3);

	DB_list();
	apr_terminate();
}
