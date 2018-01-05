#include <stdio.h>
#include <bstrlib.h>
#include <db.h>
#include <dbg.h>
#include <shell.h>
#include <apr_general.h>

int main(int argc, char *argv[])
{
	apr_initialize();

	Shell_exec(GIT_SH, "URL", "https://github.com/PreslavMihaylov/dotfiles", NULL);

	apr_terminate();
}
