/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:01:33 by ascordil          #+#    #+#             */
/*   Updated: 2025/01/16 18:33:04 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define  PIPEX_BONUS_H
# include <stdlib.h>
# include "libft.h"
# include <stdarg.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# define NUMBER_OF_PROCESS 2

int			initfork(void);
int			open_file(char *name_of_file, int mode);
int			first_process_here_doc(int pipefd[2], char *limiter);
int			ft_strnstr_rmx_index(const char *big,
				const char *little, size_t len);
int			here_doc_or_normal(char **args, char **env, int pipefd[2],
				int flag);
int			first_process(char *n_input_file, int pipefd[2],
				char *raw_cmd, char **env);
int			main_pr_hd(char *n_output_file, int pipefd[2],
				char *raw_cmd, char **env);
int			initfork(void);
int			check_integrity(char **args, int ac, char **env);
int			check_integrity_here_doc(char **args, int ac, char **env);
int			main_verif_integrity(char **args, int ac, char **env, int *flag);
char		**recup_cmd(char *arg, char **env);
char		*here_doc(char *limiter, int pipefd[2]);
char		*get_path(char *cmd_name, char **env);
char		*get_true_path(char *cmd_name, char **array_of_path);
char		*get_path(char *cmd_name, char **env);
char		**get_array_of_path(char **env);
void		error_main(void);
void		init_pipe(int pipefd[2]);
void		execute_cmd(char *not_format_cmd, char **env);
void		message_error_open(char *name_of_file);

#endif
