/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:20:34 by ascordil          #+#    #+#             */
/*   Updated: 2025/01/15 13:52:36 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<../includes/pipex.h>

int	first_process(char *n_input_file, int pipefd[2], char *raw_cmd, char **env)
{
	char	**cmd;
	int		pid;
	int		input_file;

	input_file = open_file(n_input_file, 1);
	pid = initfork();
	if (pid == 0)
	{
		dup2(input_file, 0);
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
		close(input_file);
		cmd = recup_cmd(raw_cmd, env);
		if (!cmd)
			exit(EXIT_FAILURE);
		if (execve(cmd[0], cmd, env) == -1)
		{
			message_error_exec(cmd[1]);
			return (ft_free_tab(cmd), exit(EXIT_FAILURE), -1);
		}
		return (ft_free_tab(cmd), 1);
	}
	return (pid);
}

int	main_process(char *n_output_file, int pipefd[2], char *raw_cmd, char **env)
{
	char	**cmd;
	int		output_file;

	output_file = open_file(n_output_file, 2);
	dup2(pipefd[0], 0);
	dup2(output_file, 1);
	close(pipefd[0]);
	close(pipefd[1]);
	close(output_file);
	cmd = recup_cmd(raw_cmd, env);
	if (!cmd)
		exit(0);
	if (execve(cmd[0], cmd, env) == -1)
	{
		message_error_exec(cmd[1]);
		ft_free_tab(cmd);
		exit(0);
	}
	ft_free_tab(cmd);
	return (0);
}

int	main(int count, char **args, char **env)
{
	int	pipefd[2];

	if (count == 5)
	{
		if (!check_integrity(args, count, env))
			return (1);
		if (pipe(pipefd) == -1)
		{
			perror("Error during creation of pipe");
			exit(0);
		}
		first_process(args[1], pipefd, args[2], env);
		main_process(args[4], pipefd, args[3], env);
	}
	else
	{
		ft_putstr_fd("Format Error:\n", 2);
		ft_putstr_fd("Syntaxe of program ==>", 2);
		ft_putstr_fd("./pipex [path/input_filename]", 2);
		ft_putstr_fd("['cmd1'] ['cmd2'] [path/output_filename]", 2);
		exit(0);
	}
}
