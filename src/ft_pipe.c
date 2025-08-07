/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javjimen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:46:54 by javjimen          #+#    #+#             */
/*   Updated: 2025/08/07 21:39:21 by javjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "minishell.h"

int ft_pipe(int argc, char **argv)
{
	int		pipefd[2];
	int		savestdfd[2];
	char	**arguments;
	pid_t	cpid;

	if (argc != 4)
	{
		write(STDERR_FILENO, WRONG_USAGE_STR, ft_strlen(WRONG_USAGE_STR));
		exit(EXIT_FAILURE);
	}
	// Ignore SIGCHLD to prevent zombie processes
	if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		free_string_array(argv);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		free_string_array(argv);
		exit(EXIT_FAILURE);
	}
	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		free_string_array(argv);
		exit(EXIT_FAILURE);
	}
	if (cpid == 0)
	{	/* Child reads from pipe */
		close(pipefd[1]);		/* Close unused write end */
		savestdfd[0] = dup(STDIN_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		arguments = create_string_array(3);
		if (arguments == NULL)
		{
			perror("create_string_array");
			free_string_array(argv);
			exit(EXIT_FAILURE);
		}
		arguments[0] = ft_strdup(argv[2]);
		if (arguments[0] == NULL)
		{
			perror("ft_strdup");
			free_string_array(argv);
			free_string_array(arguments);
			exit(EXIT_FAILURE);
		}
		arguments[1] = ft_strdup(argv[3]);
		if (arguments[1] == NULL)
		{
			perror("ft_strdup");
			free_string_array(argv);
			free_string_array(arguments);
			exit(EXIT_FAILURE);
		}
		if (execute_command(argv[2], arguments, NULL) == -1)
		{
			perror("execute_command");
			free_string_array(argv);
			free_string_array(arguments);
			exit(EXIT_FAILURE);
		}
		close(pipefd[0]);
		dup2(savestdfd[0], STDIN_FILENO);
		close(savestdfd[0]);
		free_string_array(arguments);
		exit(EXIT_SUCCESS);
	}
	else
	{	/* Parent executes argv[1] and writes output to pipe */
		close(pipefd[0]);		/* Close unused read end */
		savestdfd[1] = dup(STDOUT_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		arguments = create_string_array(3);
		if (arguments == NULL)
		{
			perror("create_string_array");
			free_string_array(argv);
			exit(EXIT_FAILURE);
		}
		arguments[0] = ft_strdup(argv[0]);
		if (arguments[0] == NULL)
		{
			perror("ft_strdup");
			free_string_array(argv);
			exit(EXIT_FAILURE);
		}
		arguments[1] = ft_strdup(argv[1]);
		if (arguments[1] == NULL)
		{
			perror("ft_strdup");
			free_string_array(arguments);
			exit(EXIT_FAILURE);
		}
		if (execute_command(argv[0], arguments, NULL) == -1)
		{
			perror("execute_command");
			free_string_array(argv);
			free_string_array(arguments);
			exit(EXIT_FAILURE);
		}
		close(pipefd[1]);		/* Reader will see EOF */
		dup2(savestdfd[1], STDOUT_FILENO);
		close(savestdfd[1]);
		free_string_array(arguments);
		wait(NULL);				/* Wait for child */
		exit(EXIT_SUCCESS);
	}
}
