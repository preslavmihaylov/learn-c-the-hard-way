#include <shell.h>

int Shell_run(apr_pool_t *p, Shell *cmd)
{
	return 0;
}

int Shell_exec(Shell cmd, ...)
{
	return 0;
}

Shell CLEANUP_SH =
{
	.dir = "/tmp",
	.exe = "rm",
	.args = { "rm", "-rf", "/tmp/pkg-build", "/tmp/pkg-src.tar.gz",
		"/tmp/pkg-src.tar.bz2", "/tmp/DEPENDS", NULL }
};

Shell GIT_SH =
{
	.dir = "/tmp",
	.exe = "git",
	.args = { "git", "clone", "URL", "pkg-build", NULL }
};

Shell TAR_SH =
{
	.dir = "/tmp/pkg-build",
	.exe = "tar",
	.args = { "tar", "-xzf", "FILE", "--strip-components", "1", NULL }
};

Shell CURL_SH =
{
	.dir = "/tmp",
	.exe = "curl",
	.args = { "curl", "-L", "-o", "TARGET", "URL", NULL }
};

Shell CONFIGURE_SH =
{
	.dir = "/tmp/pkg-build",
	.exe = "./configure",
	.args = { "configure", "OPTS", NULL }
};

Shell MAKE_SH =
{
	.dir = "/tmp/pkg-build",
	.exe = "make",
	.args = { "make", "OPTS", NULL }
};

Shell INSTALL_SH =
{
	.dir = "/tmp/pkg-build",
	.exe = "sudo",
	.args = { "sudo", "make", "TARGET", NULL }
};

