#include <stdio.h>
#include <bstrlib.h>

int main(int argc, char *argv[])
{
	bstring bstr = bfromcstr("Hello world");
	printf("%s\n", bdata(bstr));
}
