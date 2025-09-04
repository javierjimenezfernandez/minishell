/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javjimen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 18:30:16 by javjimen          #+#    #+#             */
/*   Updated: 2025/09/08 19:17:27 by javjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

typedef enum e_state_machine
{
	DEFAULT,
	IN_WORD,
	IN_QUOTE,
	ESCAPED_CHARACTER
}	t_state_machine;

typedef enum e_element_type
{
	T_QUOTING,
	T_RESERVED_WORD,
	T_TOKEN
}	t_element_type;

typedef enum e_quoting_type
{
	T_PIPE = '|',
	T_AND = '&',
	T_SEMI = ';',
	T_LESS = '<',
	T_GREAT = '>',
	T_LBREAK = '(',
	T_RBREAK = ')',
	T_DOLLAR = '$',
	T_ACCENT = '`',
	T_BACKSLASH = '\\',
	T_DQUOTE = '\"',
	T_SQUOTE = '\'',
	T_SPACE = ' ',
	T_TAB = '\t',
	T_NEWLINE = '\n'
}	t_quoting_type;

typedef enum e_special_if_quoted_type
{
	T_WILDCART = '*',
	T_INTERROG = '?',
	T_BRACKET = '[',
	T_HASHTAG = '#',
	T_VIRGUL = '~',
	T_EQUAL = '=',
	T_PERCENT = '%'
}	t_special_if_quoted_type;

/* Lbrace	Rbrace	Bang	In   */
/* '{'	   '}'	   '!'	 'in' */

typedef enum e_reserved_word_type
{
	T_IF,
	T_THEN,
	T_ELSE,
	T_ELIF,
	T_FI,
	T_DO,
	T_DONE,
	T_CASE,
	T_ESAC,
	T_WHILE,
	T_UNTIL,
	T_FOR,
	T_LBRACE,
	T_RBRACE,
	T_BANG,
	T_IN
}	t_reserved_word_type;

typedef enum e_token_type
{
	T_WORD,
	T_ASSIGNMENT_WORD,
	T_NAME,
	T_NEWLINE,
	T_IO_NUMBER,
	T_OPERATOR
}	t_token_type;

typedef enum e_operator_type
{
	T_AND_IF,
	T_OR_IF,
	T_DSEMI,
	T_DLESS,
	T_DGREAT,
	T_LESSAND,
	T_GREATAND,
	T_LESSGREAT,
	T_DLESSDASH,
	T_CLOBBER
}	t_operator_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

#endif /* TOKENIZER_H */
