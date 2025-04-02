/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:01:33 by ascordil          #+#    #+#             */
/*   Updated: 2025/01/16 18:32:30 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define  PIPEX_H
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
char		**recup_cmd(char *arg, char **env);
char		**get_array_of_path(char **env);
char		*get_true_path(char *cmd_name, char **array_of_path);
char		*get_path(char *cmd_name, char **env);
void		message_error_exec(char *cmd_name);
void		message_error_open(char *name_of_file);
int			check_integrity(char **args, int ac, char **env);
int			check_cmd_integrity(char *arg, char **env);
int			check_acess(char *name_of_file, int mode);
int			check_path(char *cmd_name, char **env);

#endif
