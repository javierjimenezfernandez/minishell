/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javjimen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:46:54 by javjimen          #+#    #+#             */
/*   Updated: 2025/07/24 13:04:18 by javjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "minishell.h"

int ft_pipe(int argc, char *argv[])
{
    int     pipefd[2];
    char    buf;
    char    *parent_output;
    char    *aux;
    char    **arguments;
    pid_t   cpid;
    
    if (argc != 2)
    {
        ft_printf(STDERR_FILENO, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
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
        parent_output = ft_calloc(1, sizeof(char));
        while (read(pipefd[0], &buf, 1) > 0)
        {
            /* save the pipe read end of the child into a variable 
            to be the input of the right command of the pipe */
            aux = ft_strjoin(parent_output, &buf);
            free(parent_output);
            parent_output = aux;
        }
        if (parent_output[0] != "\0")
        {
            arguments = ft_split(parent_output, " ");
        }
        close(pipefd[0]);
        free(parent_output);
        // add execve call to the program (careful: read the man for argv passed to execve)
        exit(EXIT_SUCCESS);
    }
    else
    {   /* Parent executes argv[1] and writes output to pipe */
        close(pipefd[0]);          /* Close unused read end */
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);          /* Reader will see EOF */
        wait(NULL);                /* Wait for child */
        exit(EXIT_SUCCESS);
    }
}