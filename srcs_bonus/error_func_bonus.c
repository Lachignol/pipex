/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:31:25 by ascordil          #+#    #+#             */
/*   Updated: 2025/01/16 18:31:57 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<../includes/pipex_bonus.h>

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

void	error_main(void)
{
	ft_putstr_fd("Format Error!\n", 2);
	ft_putstr_fd("=====Syntaxe of program=====\n", 2);
	ft_putstr_fd("./pipex [path/input_filename] ", 2);
	ft_putstr_fd("[cmd1] [cmd2] [cmd...] [path/output_filename]\n", 2);
	ft_putstr_fd("or\n", 2);
	ft_putstr_fd("./pipex [here_doc] [LIMITER] ", 2);
	ft_putstr_fd("[cmd1] [cmd2] [cmd...] [path/output_filename]\n", 2);
}
