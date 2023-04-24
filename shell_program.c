#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * display_prompt - displays the shell prompt for input
 * Description: displays prompt
 */

void display_prompt(void)
{
	printf("simple_shell> ");
}

/**
 * Main - reads user input and executes the command
 * @argc: specifies the number of arguments
 * @argv: an array of strings that contain the actual argument
 * Return: the executed command
 */

int main(int argc, char **argv)
{
	char cmd[MAX_COMMAND_LENGTH];
	char *environ[] = {NULL}; /* environment variable */

	pid_t pid;
	int status;

	while (1)
	{
		display_prompt();

		/* Read user input from stdin */
		if (fgets(cmd, sizeof(cmd), stdin) == NULL)
		{
			/* Handle end of file (Ctrl+D)*/
			printf("\n");
			exit(0);
		}

		/* Remove newline character from the input */
		cmd[strcspn(cmd, "\n")] = '\0';

		/* Fork a new process */
		pid = fork();

		if (pid == 0)
		{
			/* Child process */
			char *exec_args[] = {cmd, NULL};

			/* Execute the command using execve */
			if (execve(cmd, exec_args, environ) == -1)
			{
				/* Executable not found or failed to execute */
				perror("Error");
				exit(1);
			}
		}

		else if (pid > 0)
		{
			/* Parent process */
			waitpid(pid, &status, 0);
		}

		else
		{
			/* Fork failed */
			perror("Error");
			exit(1);
		}
	}

	return (0);
}
