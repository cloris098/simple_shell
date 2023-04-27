#include "main.h"

/* Global variable for interrupt signal handling */
unsigned int sig_flag;

/**
 * sig_handler - Handles inteerupt signal
 * @sig: signal number
 *
 * Return: void
 */

static void sig_handler(int sig)
{
	(void) sig;
	if (sig_flag == 0)
		_puts("\n$ ");
	else
		_puts("\n");
}

/**
 * main - main function
 * @argc: number of arguments
 * @argv: array of arguments passed to main
 * @environ: array of environment variables
 *
 * Return: 0 or exit status
 */

int main(int argc __attribute__((unused)), char **argv, char **environ)
{
	size_t buffer_len = 0;
	unsigned int is_pipe = 0;
	unsigned int i;
	variables_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.shell_args = argv;
	vars.envp = create_env(environ);
	signal(SIGINT, sig_handler);

	if (!isatty(STDIN_FILENO))
		is_pipe = 1;
	if (is_pipe == 0)
		_puts("$ ");
	sig_flag = 0;

	while (getline(&(vars.buffer), &buffer_len, stdin) != -1)
	{
		sig_flag = 1;
		vars.cmd_count++;
		vars.cmds = tokenize(vars.buffer, ";");

		for (i = 0; vars.cmds && vars.cmds[i] != NULL; i++)
		{
			vars.args = tokenize(vars.cmds[i], "\n \t\r");
			if (vars.args && vars.args[0])
				if (check_for_builtin(&vars) == NULL)
					check_for_path(&vars);
			free(vars.args);
		}

		free(vars.buffer);
		free(vars.cmds);
		sig_flag = 0;

		if (is_pipe == 0)
			_puts("$ ");
		vars.buffer = NULL;
	}

	if (is_pipe == 0)
		_puts("\n");
	free_env(vars.envp);
	free(vars.buffer);
	exit(vars.exit_status);
}
