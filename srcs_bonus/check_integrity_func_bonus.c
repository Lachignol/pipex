/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_integrity_func.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:21:52 by ascordil          #+#    #+#             */
/*   Updated: 2025/01/16 18:32:20 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<../includes/pipex_bonus.h>

int	check_path(char *cmd_name, char **env)
{
	char		**array_of_path;
	char		*path;

	path = NULL;
	array_of_path = get_array_of_path(env);
	if (!array_of_path)
		return (0);
	path = get_true_path(cmd_name, array_of_path);
	if (!path)
		return (ft_free_tab(array_of_path), 0);
	return (ft_free_tab(array_of_path), free(path), 1);
}

int	check_acess(char *name_of_file, int mode)
{
	int	file;

	file = 0;
	if (mode == 1)
	{
		if (access(name_of_file, F_OK | R_OK) != 0)
		{
			message_error_open(name_of_file);
			return (0);
		}
	}
	else
	{
		if (access(name_of_file, F_OK | W_OK) != 0)
		{
			message_error_open(name_of_file);
			return (0);
		}
	}
	return (1);
}

int	check_cmd_integrity(char *arg, char **env)
{
	char	**cmd;

	cmd = ft_split(arg, ' ');
	if (!cmd)
		return (0);
	if (!check_path(cmd[0], env))
		return (ft_putstr_fd("Command not found: ", 2),
			ft_putstr_fd(cmd[0], 2), ft_putstr_fd("\n", 2),
			ft_free_tab(cmd), 0);
	return (ft_free_tab(cmd), 1);
}

int	check_integrity(char **args, int ac, char **env)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	while (args[i] && i <= ac - 1)
	{
		if ((i == 1) && (ft_only_space(args[i]) || !check_acess(args[i], 1)))
			result = -1;
		else if ((i == ac - 1) && ft_only_space(args[i]))
			result = -1;
		else if (i != 1 && i != ac -1)
		{
			if (ft_only_space(args[i]) || !check_cmd_integrity(args[i], env))
				result = -1;
		}
		i++;
	}
	if (result < 0)
		return (0);
	return (1);
}

int	check_integrity_here_doc(char **args, int ac, char **env)
{
	int	i;
	int	result;

	i = 2;
	result = 0;
	while (args[i] && i <= ac - 1)
	{
		if (i == 2 && (ft_only_space(args[2]) || !check_acess(args[i], 1)))
			result = -1;
		else if ((i == ac - 1) && ft_only_space(args[i]))
			result = -1;
		else if (i != 2 && i != ac - 1)
		{
			if (ft_only_space(args[i])
				|| !check_cmd_integrity(args[i], env))
					result = -1;
		}
		i++;
	}
	if (result < 0)
		return (0);
	return (1);
}
