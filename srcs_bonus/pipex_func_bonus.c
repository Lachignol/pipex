/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:32:25 by ascordil          #+#    #+#             */
/*   Updated: 2025/01/14 12:33:15 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<../includes/pipex_bonus.h>

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
		return (ft_putstr_fd("Command not found: ", 2),
			ft_putstr_fd(cmd[0], 2), ft_putstr_fd("\n", 2),
			ft_free_tab(cmd), NULL);
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
			message_error_open(name_of_file);
	}
	else if (mode == 2)
	{
		file = open(name_of_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file < 0)
			message_error_open(name_of_file);
	}
	else if (mode == 3)
	{
		file = open(name_of_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file < 0)
			message_error_open(name_of_file);
	}
	return (file);
}

void	execute_cmd(char *not_format_cmd, char **env)
{
	char	**cmd;

	cmd = recup_cmd(not_format_cmd, env);
	if (!cmd)
		exit(EXIT_FAILURE);
	if (execve(cmd[0], cmd, env) == -1)
	{
		ft_putstr_fd("Command not found ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd("\n", 2);
		ft_free_tab(cmd);
		exit(EXIT_FAILURE);
	}
	ft_free_tab(cmd);
}

int	initfork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Error during creation of Fork");
		exit(EXIT_FAILURE);
		return (-1);
	}
	return (pid);
}

int	main_verif_integrity(char **args, int ac, char **env, int *flag)
{
	int	result;

	result = 0;
	if (ft_strnstr(args[1], "here_doc", 8) != 0)
	{
		*flag = 1;
		result = 1;
	}
	else
			result = check_integrity(args, ac, env);
	return (result);
}
