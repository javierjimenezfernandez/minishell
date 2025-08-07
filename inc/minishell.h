/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javjimen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:57:28 by javjimen          #+#    #+#             */
/*   Updated: 2025/08/07 20:43:33 by javjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define PATH_ENV_VAR "PATH"
// add some way to define the slash depending of unix vs. windows
# define PATH_SLASH "/"
# define USR_BIN_PATH "/usr/bin/"
# define WRONG_USAGE_STR "Usage: <command> <arg> <command> <arg>\n"

/* minishell.c */
int		main(int argc, char** argv);

/* ft_pipe.c */
int		ft_pipe(int argc, char *argv[]);

/* utils.c */
int		free_string_array(char **str_arr);
char	**create_string_array(size_t number_of_members);
int		execute_command(char *command, char **argv, char **envp);

#endif /* MINISHELL_H */
