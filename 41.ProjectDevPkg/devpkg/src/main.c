#include <stdio.h>
#include <bstrlib.h>
#include <db.h>

int main(int argc, char *argv[])
{
	DB_init();
	DB_update("Hello world");
	bstring bstr = bfromcstr("Hello world");
	printf("%s\n", bdata(bstr));
}
