#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

/**
 * struct vars - structure for shell variables
 * @args: command line arguments
 * @buffer: buffer for input
 * @envp: environment variables
 * @cmd_count: command count
 * @shell_args: arguments at opening of shell
 * @exit_status: exit status
 * @cmds: array of commands
 */

typedef struct vars
{
	char **args;
	char *buffer;
	char **envp;
	size_t cmd_count;
	char **shell_args;
	int exit_status;
	char **cmds;
} vars_t;

/**
 * struct builtin_func - struct for shell built-in functions
 * @name: name of built-in command
 * @func: function for corresponding built-in
 */

typedef struct builtin_func
{
	char *name;
	void (*func)(vars_t *);
} builtin_func_t;

/* Memory Functions */
char **create_env(char **envp);
void free_env(char **envp);
char **_realloc(char **ptr, size_t *size);

/* String Functions */
ssize_t _putstr(char *str);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
unsigned int _strlen(char *str);

char **tokenize(char *str, char *delimiter);
char *custom_strtok(char *str, const char *delimiter);
char *add_value_to_key(char *key, char *value);
char **find_env_key(char **envp, char *key);

/* Built-In Functions */
void (*check_for_builtin(vars_t *vars))(vars_t *vars);
void exit_shell(vars_t *vars);
void env_builtin(vars_t *vars);
void setenv_builtin(vars_t *vars);
void unsetenv_builtin(vars_t *vars);
void add_key_to_env(vars_t *vars);

/* Path Functions */
void check_for_path(vars_t *vars);
int path_execute(char *cmd, vars_t *vars);
char *get_path(char **envp);
int execute_current_directory(vars_t *vars);
int check_directory(char *dir);

/* Error Handling */
void print_error_message(vars_t *vars, char *msg);
void print_string(char *str);
char *uint_to_string(unsigned int count);

#endif /* MAIN_H */
