/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javjimen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:57:28 by javjimen          #+#    #+#             */
/*   Updated: 2025/07/20 17:29:33 by javjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* c libraries */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
/* libft headers */
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
/* minishell headers */
# include "utils.h"
# include "tokenizer.h"

/* minishell.c */
int	main(int argc, char **argv);

#endif /* MINISHELL_H */
