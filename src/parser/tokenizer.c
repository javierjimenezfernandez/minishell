/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javjimen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:30:19 by javjimen          #+#    #+#             */
/*   Updated: 2025/09/08 19:17:33 by javjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "utils.h"

/*

token recognition: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_03
shell grammar: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10

*/

int	ft_ismetachar(int c)
{
	return ((c == '|')
		|| (c == '&')
		|| (c == ';')
		|| (c == '<')
		|| (c == '>')
		|| (c == '(')
		|| (c == ')')
		|| (c == '$')
		|| (c == '`')
		|| (c == '\\')
		|| (c == '\"')
		|| (c == '\'')
		|| (c == ' ')
		|| (c == '\t')
		|| (c == '\n')
		|| (c == '*')
		|| (c == '?')
		|| (c == '[')
		|| (c == '#')
		|| (c == '~')
		|| (c == '=')
		|| (c == '%'));
}

t_token	tokenize(const char *input)
{
	t_state_machine	fsm;
	t_token			token;
	size_t			i;

	fsm = DEFAULT;
	token.type = T_WORD;
	token.value = input;
	i = 0;
	while (input[i] != '\0' && ft_isascii(input[i]))
	{
		if (fsm == DEFAULT)
		{
			if (ft_ismetachar(input[i]))
				fsm = IN_QUOTE;
			else if (ft_isprint(input[i]) && !ft_isspace(input[i]))
				fsm = IN_WORD;
		}
	}
	return (token);
}
