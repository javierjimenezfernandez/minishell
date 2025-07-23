/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javjimen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:57:28 by javjimen          #+#    #+#             */
/*   Updated: 2025/07/23 11:58:40 by javjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

/* minishell.c */
int	main(int argc, char** argv);

/* ft_pipe.c */
int ft_pipe(int argc, char *argv[]);

#endif /* MINISHELL_H */
