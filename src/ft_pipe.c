/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javjimen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:46:54 by javjimen          #+#    #+#             */
/*   Updated: 2025/07/25 12:52:16 by javjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "minishell.h"

#define USR_BIN_PATH "/usr/bin/"
#define WRONG_USAGE_STR "Usage: <command> <arg> <command> <arg>\n"

int free_string_array(char **str_arr)
{
    int i = 0;

    if (str_arr == NULL)
        return (-1);
    i = 0;
	while (str_arr[i] != NULL)
		i++;
	while (i >= 0)
	{
		free(str_arr[i]);
		i--;
	}
	free(str_arr);
    return (0);
}

int ft_pipe(int argc, char *argv[])
{
    int     pipefd[2];
    int     savestdfd[2];
    // char    buf;
    char    *path;
    // char    *parent_output;
    // char    *aux;
    char    **arguments;
    pid_t   cpid;
    
    if (argc != 4)
    {
        write(STDERR_FILENO, WRONG_USAGE_STR, ft_strlen(WRONG_USAGE_STR));
        exit(EXIT_FAILURE);
    }
    // Ignore SIGCHLD to prevent zombie processes
    if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
    {
        perror("signal");
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0)
    {   /* Child reads from pipe */
        close(pipefd[1]);          /* Close unused write end */
        /* while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n", 1); */
        savestdfd[0] = dup(STDIN_FILENO);
        dup2(pipefd[0], STDIN_FILENO);
        /* parent_output = ft_calloc(1, sizeof(char));
        while (read(pipefd[0], &buf, 1) > 0)
        {
            // save the pipe read end of the child into a variable 
            // to be the input of the right command of the pipe
            aux = ft_strjoin(parent_output, &buf);
            free(parent_output);
            parent_output = aux;
        }
        if (parent_output[0] != "\0")
        {
            arguments = ft_split(parent_output, " ");
            if (arguments == NULL)
            {
                perror("ft_split");
                exit(EXIT_FAILURE);
            }
        }
        close(pipefd[0]);
        free(parent_output); */
        arguments = malloc(sizeof(char *) * 3);
        if (arguments == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        arguments[0] = NULL;
        arguments[1] = NULL;
        arguments[2] = NULL;
        arguments[0] = ft_strdup(argv[2]);
        if (arguments[0] == NULL)
        {
            perror("ft_strdup");
            exit(EXIT_FAILURE);
        }
        arguments[1] = ft_strdup(argv[3]);
        if (arguments[1] == NULL)
        {
            perror("ft_strdup");
            free_string_array(arguments);
            exit(EXIT_FAILURE);
        }
        path = ft_strjoin(USR_BIN_PATH, argv[2]);
        if (execve(path, arguments, NULL) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);
        dup2(savestdfd[0], STDIN_FILENO);
        close(savestdfd[0]);
        free_string_array(arguments);
        exit(EXIT_SUCCESS);
    }
    else
    {   /* Parent executes argv[1] and writes output to pipe */
        close(pipefd[0]);          /* Close unused read end */
        savestdfd[1] = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        arguments = malloc(sizeof(char *) * 3);
        if (arguments == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        arguments[0] = NULL;
        arguments[1] = NULL;
        arguments[2] = NULL;
        arguments[0] = ft_strdup(argv[0]);
        if (arguments[0] == NULL)
        {
            perror("ft_strdup");
            exit(EXIT_FAILURE);
        }
        arguments[1] = ft_strdup(argv[1]);
        if (arguments[1] == NULL)
        {
            perror("ft_strdup");
            free_string_array(arguments);
            exit(EXIT_FAILURE);
        }
        path = ft_strjoin(USR_BIN_PATH, argv[0]);
        if (execve(path, arguments, NULL) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
        // write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);          /* Reader will see EOF */
        dup2(savestdfd[1], STDOUT_FILENO);
        close(savestdfd[1]);
        free(path);
        free_string_array(arguments);
        wait(NULL);                /* Wait for child */
        exit(EXIT_SUCCESS);
    }
}