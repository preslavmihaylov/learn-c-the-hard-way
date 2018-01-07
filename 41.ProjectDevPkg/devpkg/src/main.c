#include <stdio.h>
#include <bstrlib.h>
#include <db.h>
#include <dbg.h>
#include <shell.h>
#include <commands.h>
#include <apr_general.h>

int main(int argc, char *argv[])
{
	apr_initialize();

	DB_init();
	Command_fetch("https://github.com/PreslavMihaylov/dotfiles.git");
	Command_fetch("http://apache.cbox.biz//apr/apr-1.6.3.tar.gz");
	Command_install("http://apache.cbox.biz//apr/apr-1.6.3.tar.bz2", NULL, NULL, NULL);
	//Command_build("http://apache.cbox.biz//apr/apr-1.6.3.tar.bz2", NULL, NULL, NULL);

	apr_terminate();
}
