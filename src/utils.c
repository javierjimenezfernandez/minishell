/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: javjimen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:13:33 by javjimen          #+#    #+#             */
/*   Updated: 2025/08/07 21:43:26 by javjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_string_array(char **string_array)
{
	int	i;

	if (string_array == NULL)
		return (-1);
	i = 0;
	while (string_array[i] != NULL)
		i++;
	while (i >= 0)
	{
		free(string_array[i]);
		i--;
	}
	free(string_array);
	return (0);
}

char	**create_string_array(size_t number_of_members)
{
	char	**string_array;
	size_t	i;

	string_array = ft_calloc(number_of_members + 1, sizeof(char *));
	if (string_array == NULL)
		return (NULL);
	i = 0;
	while (i <= number_of_members)
	{
		string_array[i] = NULL;
		i++;
	}
	return (string_array);
}

int	execute_command(char *command, char **argv, char **envp)
{
	char	**paths_array;
	char	*path_env_var;
	char	*execve_path;
	char	*aux;
	int		ret;
	size_t	i;


	path_env_var = getenv(PATH_ENV_VAR);
	if (path_env_var == NULL)
	{
		perror("getenv");
		return (-1);
	}
	paths_array = ft_split(path_env_var, ':');
	if (paths_array == NULL)
	{
		perror("ft_split");
		return (-1);
	}
	i = 0;
	while (paths_array[i] != NULL)
	{
		execve_path = ft_strjoin(paths_array[i], PATH_SLASH);
		if (execve_path == NULL)
		{
			perror("ft_strjoin");
			free_string_array(paths_array);
			return (-1);
		}
		aux = execve_path;
		execve_path = ft_strjoin(execve_path, command);
		if (execve_path == NULL)
		{
			perror("ft_strjoin");
			free_string_array(paths_array);
			free(aux);
			return (-1);
		}
		free(aux);
		ret = execve(execve_path, argv, envp);
		free(execve_path);
		if (ret != -1)
			break ;
		i++;
	}
	free_string_array(paths_array);
	return (ret);
}
