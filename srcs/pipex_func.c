/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:32:25 by ascordil          #+#    #+#             */
/*   Updated: 2025/01/16 18:19:30 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<../includes/pipex.h>

char	**recup_cmd(char *arg, char **env)
{
	char	**cmd;
	char	*full_path;
	char	*path;

	cmd = ft_split(arg, ' ');
	if (!cmd)
		return (NULL);
	path = get_path(cmd[0], env);
	if (!path)
		return (message_error_exec(cmd[0]), ft_free_tab(cmd), NULL);
	full_path = ft_strdup(path);
	if (!full_path)
		return (ft_free_tab(cmd), free(path), NULL);
	free(cmd[0]);
	cmd[0] = full_path;
	return (cmd);
}

int	open_file(char *name_of_file, int mode)
{
	int	file;

	file = 0;
	if (mode == 1)
	{
		file = open(name_of_file, O_RDONLY);
		if (file < 0)
		{
			message_error_open(name_of_file);
			exit(0);
		}
		return (file);
	}
	else if (mode == 2)
	{
		file = open(name_of_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file < 0)
		{
			message_error_open(name_of_file);
			exit(0);
		}
		return (file);
	}
	return (0);
}

int	initfork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error during creation of Fork", 2);
		exit(0);
		return (-1);
	}
	return (pid);
}

void	message_error_open(char *name_of_file)
{
	if (errno == 13)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(name_of_file, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (errno == 2)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(name_of_file, 2);
		ft_putstr_fd("\n", 2);
	}
	else
		ft_putstr_fd(strerror(errno), 2);
}

void	message_error_exec(char *cmd_name)
{
	ft_putstr_fd("Command not found: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd("\n", 2);
}
