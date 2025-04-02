/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:20:34 by ascordil          #+#    #+#             */
/*   Updated: 2025/04/02 17:16:51 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<../includes/pipex_bonus.h>

int	first_process(char *n_input_file, int pipefd[2], char *raw_cmd, char **env)
{
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
		execute_cmd(raw_cmd, env);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
	return (pid);
}

int	intermediate_process(int pipefd[2], char *not_format_cmd, char **env)
{
	int		pid;

	pid = initfork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execute_cmd(not_format_cmd, env);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
	return (pid);
}

int	main_process(char *n_output_file, int pipefd[2], char *raw_cmd, char **env)
{
	int		output_file;

	output_file = open_file(n_output_file, 2);
	dup2(output_file, 1);
	close(pipefd[1]);
	close(pipefd[0]);
	close(output_file);
	execute_cmd(raw_cmd, env);
	if (pipefd != NULL)
		free(pipefd);
	return (0);
}

void	init_pipe(int pipefd[2])
{
	if (!pipefd)
		exit(EXIT_FAILURE);
	if (pipe(pipefd) == -1)
	{
		perror("Error during creation of pipe");
		exit(EXIT_FAILURE);
	}
}

int	main(int count, char **args, char **env)
{
	int		pipefd[2];
	int		i;
	int		flag;

	i = 3;
	flag = 0;
	if (count >= 5 && main_verif_integrity(args, count, env, &flag))
	{
		if (!here_doc_or_normal(args, env, pipefd, flag))
			return (1);
		while (i < count - 2)
		{
			init_pipe(pipefd);
			intermediate_process(pipefd, args[i], env);
			i++;
		}
		if (!flag)
			main_process(args[count - 1], pipefd, args[count - 2], env);
		else
			main_pr_hd(args[count - 1], pipefd, args[count - 2], env);
		return (0);
	}
	if (count < 5)
		error_main();
	return (1);
}
