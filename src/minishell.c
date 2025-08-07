/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javjimen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:57:37 by javjimen          #+#    #+#             */
/*   Updated: 2025/08/07 19:40:07 by javjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	//size_t		i;
	char		*newline;
	char		**commands;
	int			comcount;
	const char	*prompt = "Enter the commands to give to the minishell: ";

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
		commands = ft_split(newline, ' ');
		if (commands == NULL)
		{
			perror("ft_split");
			free(newline);
			return (1);
		}
		free(newline);
		comcount = 0;
		while (commands[comcount] != NULL)
			comcount++;
		ft_pipe(comcount, commands);
		free_string_array(commands);
	}
	return (0);
}
