/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:17:06 by ascordil          #+#    #+#             */
/*   Updated: 2025/04/02 17:25:01 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<../includes/pipex.h>

char	*get_path(char *cmd_name, char **env)
{
	char	**array_of_path;
	char	*path;

	array_of_path = get_array_of_path(env);
	if (!array_of_path)
		return (NULL);
	path = get_true_path(cmd_name, array_of_path);
	if (!path)
		return (ft_free_tab(array_of_path), NULL);
	return (ft_free_tab(array_of_path), path);
}

char	*get_true_path(char *cmd_name, char **array_of_path)
{
	int		i;
	char	*path_temp;
	char	*path;
	char	*cmd_name_f;

	i = -1;
	path = NULL;
	cmd_name_f = ft_strjoin("/", cmd_name);
	if (!cmd_name_f)
		return (NULL);
	while (array_of_path[++i])
	{
		path_temp = ft_strjoin(array_of_path[i], cmd_name_f);
		if (!path_temp)
			return (free(cmd_name_f), NULL);
		if (access(path_temp, F_OK | X_OK) == 0)
		{
			path = ft_strdup(path_temp);
			if (!path)
				return (free(cmd_name_f), free(path_temp), NULL);
			return (free(cmd_name_f), free(path_temp), path);
		}
		free(path_temp);
	}
	return (free(cmd_name_f), path);
}

char	**get_array_of_path(char **env)
{
	int		i;
	char	**array_of_path;

	i = 0;
	array_of_path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			array_of_path = ft_split(&env[i][5], ':' );
			if (!array_of_path)
				return (NULL);
			return (array_of_path);
		}
		i++;
	}
	return (array_of_path);
}
