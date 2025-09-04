/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javjimen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:57:37 by javjimen          #+#    #+#             */
/*   Updated: 2025/09/11 21:41:37 by javjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	size_t		i;
	char		*newline;
	t_token		**tokenized_input;
	const char	*prompt = "this is a prompt!: ";

	(void)argc;
	(void)argv;
	newline = readline(prompt);
	tokenized_input = ft_calloc(1, sizeof(t_token *));
	*tokenized_input = tokenize(newline);
	i = 0;
	while (newline[i] != '\0')
	{
		write(1, &newline[i], 1);
		i++;
	}
	free(newline);
	write(1, "\n", 1);
	return (0);
}
