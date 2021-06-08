/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 10:45:09 by ynoam             #+#    #+#             */
/*   Updated: 2021/06/08 10:45:12 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	finishexec(char **str, char ***path, char ***argv)
{
	put_error("command not found", (*argv)[0]);
	ft_free_double(*path);
	ft_free_double(*argv);
	free(*str);
}

int	search_for_path_and_exec(char *cmd, char **env)
{
	char	**paths;
	char	**argv;
	char	*str2;
	int		i;
	char	*path;

	argv = ft_split(cmd, ' ');
	if (is_path(argv[0]))
	{
		exec_normal2(argv, env);
		ft_free_double(argv);
		return (0);
	}
	paths = ft_split(find_path(env), ':');
	str2 = ft_strjoin("/", argv[0]);
	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i], str2);
		execve(path, argv, env);
		free(path);
		i++;
	}
	finishexec(&str2, &paths, &argv);
	return (0);
}

int	exec_child(int in, int *fd, char *cmd, char **env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (in != -1)
		{
			dup2(in, 0);
			close(in);
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
		}
		if (in == -1)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			dup2(fd[1], 1);
		}
		search_for_path_and_exec(cmd, env);
		exit(127);
	}
	return (pid);
}

int	exec_last_child(int *fd, char *cmd, char *out, char **env)
{
	int	writ;
	int	status;
	int	pid;

	writ = open(out, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (writ == -1)
		return (put_error(strerror(errno), out));
	fd[1] = writ;
	pid = exec_child(-1, fd, cmd, env);
	close(fd[0]);
	waitpid(pid, &status, 0);
	return (status);
}

int	wait_proc(int pcount)
{
	while (--pcount >= 0)
		wait(NULL);
	return (0);
}
