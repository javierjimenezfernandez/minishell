/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javjimen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:57:37 by javjimen          #+#    #+#             */
/*   Updated: 2025/07/24 10:23:07 by javjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char** argv)
{
	//size_t		i;
	char*		newline;
	const char*	prompt = "this is a prompt!: ";

	(void)argc;
	(void)argv;
	newline = readline(prompt);
	//i = 0;
	/* while (newline[i] != '\0')
	{
		write(1, &newline[i], 1);
		i++;
	}
	free(newline);
	write(1, "\n", 1);*/
	if (newline != NULL)
	{
		argv[1] = ft_strjoin(argv[1], newline);
		ft_pipe(argc, argv);
		free(newline);
		free(argv[1]);
	}
	return (0);
}
