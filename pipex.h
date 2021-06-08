/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 10:22:46 by ynoam             #+#    #+#             */
/*   Updated: 2021/06/08 10:23:23 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"

int		put_error(char *errorstr, char *filename);
int		is_path(char *cmd);
char	*find_path(char **env);
int		exec_normal2(char *argv[], char **env);
int		ft_free_double(char **ptr);
void	finishexec(char **str, char ***path, char ***argv);
int		search_for_path_and_exec(char *cmd, char **env);
int		exec_child(int in, int *fd, char *cmd, char **env);
int		exec_last_child(int *fd, char *cmd, char *out, char **env);
int		wait_proc(int pcount);

#endif