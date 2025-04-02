/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_func_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:20:35 by ascordil          #+#    #+#             */
/*   Updated: 2025/04/02 17:28:04 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<../includes/pipex_bonus.h>

int	first_process_here_doc(int pipefd[2], char *limiter)
{
	int		pid;

	pid = initfork();
	if (pid == 0)
	{
		close(pipefd[0]);
		here_doc(limiter, pipefd);
		close(pipefd[1]);
	}
	else
	{
		wait(NULL);
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
	}
	return (pid);
}

char	*here_doc(char *limiter, int pipefd[2])
{
	char	*letter_read;

	while (1)
	{
		ft_printf("pipe heredoc> ");
		letter_read = get_next_line(0);
		if (!letter_read)
			return (exit(0), NULL);
		if ((ft_strncmp(letter_read, limiter, ft_strlen(limiter)) == 0)
			&& !(letter_read[ft_strlen(limiter) + 1]))
			return (free(letter_read), exit(0), NULL);
		write(pipefd[1], letter_read, ft_strlen(letter_read));
		free(letter_read);
	}
	return (free(letter_read), NULL);
}

int	here_doc_or_normal(char **args, char **env, int pipefd[2], int ac)
{
	if (ft_strnstr(args[1], "here_doc", 8) != 0)
	{
		init_pipe(pipefd);
		first_process_here_doc(pipefd, args[2]);
		if (!check_integrity_here_doc(args, ac, env))
			return (0);
		return (1);
	}
	else
	{
		init_pipe(pipefd);
		first_process(args[1], pipefd, args[2], env);
		return (1);
	}
}

int	main_pr_hd(char *n_output_file, int pipefd[2], char *raw_cmd, char **env)
{
	int		output_file;

	output_file = open_file(n_output_file, 3);
	dup2(output_file, 1);
	close(pipefd[0]);
	close(pipefd[1]);
	close(output_file);
	execute_cmd(raw_cmd, env);
	if (pipefd != NULL)
		free(pipefd);
	return (0);
}
