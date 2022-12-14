#include "shell_head.h"
#include "errno.h"
#include "sys/wait.h"
/**
 *Run_Command - Fork execution and run program
 *@argV: Null Terminated Array of arguments
 *
 *Return: 0 or fail
 */
int Run_Command(char **argV)
{
	pid_t childPID;
	int status;
	/* if passed NULL, Return -1 */
	if (argV == NULL || argV[0] == NULL)
		return (-1);
	childPID = fork();
	if (childPID == 0)
	{
		if (execve(argV[0], argV, NULL) == -1)
			exit(errno);
	}
	else
	{
		wait(&status);
	}
	return (0);

}

/**
 *Get_Command - Get correct Command
 * @tokens: String Array of input
 * Return: result of Command
 */
int Get_Command(char **tokens)
{
	int i = 0;
	builtIn ops[] = {
		{"exit", myexit},
		{"env", printEnv},
		{NULL, Validate_Input}
	};
	while (ops[i].opName != NULL)
	{
		if (strcmp(ops[i].opName, tokens[0]) == 0)
			break;
		i++;
	}
	return (ops[i].f(tokens));
}

/**
 * myexit - frees token array and exits program
 * @tokens: stray array output
 * Return: -1
 */

int myexit(char **tokens)
{
	int i = 0;

	for (i = 0; i < 17; i++)
	{
		if (tokens[i] != NULL)
		{
			free(tokens[i]);
		}
	}
	free(tokens);
	if (isatty(0))
		write(STDOUT_FILENO, "\n", 1);
	exit(0);
	return (-1);
}

/**
 * printEnv - prints content of enviormental variable
 * @tokens: placeholder
 * Return: -1
 */

int printEnv(__attribute__((unused))char **tokens)
{
	int i = 0;

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);
	return (-1);
}
