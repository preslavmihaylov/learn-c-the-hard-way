#include <shell.h>
#include <dbg.h>

int Shell_run(apr_pool_t *p, Shell *cmd)
{
	apr_procattr_t *attr;
	apr_status_t exitStatus;

	exitStatus = apr_procattr_create(&attr, p);
	check(exitStatus == APR_SUCCESS, "Failed to initialize proc attributes");

	exitStatus = apr_procattr_cmdtype_set(attr, APR_PROGRAM_PATH);
	check(exitStatus == APR_SUCCESS, "Failed to set cmd type");

	exitStatus = apr_procattr_dir_set(attr, cmd->dir);
	check(exitStatus == APR_SUCCESS, "Failed to set cmd directory");

	exitStatus = apr_procattr_io_set(attr, APR_NO_PIPE, APR_NO_PIPE, APR_NO_PIPE);
	check(exitStatus == APR_SUCCESS, "Failed to set cmd file descriptors");

	exitStatus = apr_proc_create(&cmd->proc, cmd->exe, cmd->args, NULL, attr, p);
	check(exitStatus == APR_SUCCESS, "Failed to create process");

	exitStatus = apr_proc_wait(&cmd->proc, &cmd->exit_code, &cmd->exit_why, APR_WAIT);
	check(exitStatus == APR_CHILD_DONE, "Process child didn't exit normally");
	check(cmd->exit_code == 0, "Process exit code not 0, Actual: %d", cmd->exit_code);
	check(cmd->exit_why == APR_PROC_EXIT, "Process didn't exit normally");

	return 0;

error:
	return -1;
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

