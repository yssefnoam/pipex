#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "libft/libft.h"

int	put_error(char *errorstr, char *filename)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(errorstr, 2);
	ft_putstr_fd("\n", 2);
	return (1);
} 

char	*find_path(char **env)
{
    int i;
    int j;

    i = 0;
    while (env[i])
    {
        j = 0;
		while (env[i][j])
        {
            if (env[i][j] == '=')
	            if (!ft_strncmp(env[i], "PATH=", ft_strlen("PATH=")))
					return (&(env[i][j]));
			j++;
		}
        i++;

    }
	return (NULL);
}

int	ft_free_double(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		ft_free(&(ptr[i]));
		i++;
	}
	free(ptr[i]);
	free(ptr);
	return (1);
}

void	search_for_path_and_exec(char *cmd, char **env)
{
	char	**paths;
	char	**argv;
	char	*str2;
	int		i;
	char	*path;

	paths = ft_split(find_path(env), ':');
	argv = ft_split(cmd, ' ');
	str2 = ft_strjoin("/", argv[0]);
	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i], str2);
		execve(path, argv, env);
		free(path);
		i++;
	}
	ft_putstr_fd(argv[0], 1);
	ft_putstr_fd("command not found\n", 1);
	ft_free_double(paths);
	ft_free_double(argv);
	free(str2);
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
		if (in == 1)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			dup2(fd[1], 1);
		}
		search_for_path_and_exec(cmd, env);
		exit (127);
	}
	return (pid);
}

int	exec_last_child(int *fd, char *cmd, char *out, char **env)
{
	int	writ;
	int	status;
	int pid;
	

	writ = open(out, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (writ == -1)
		return (put_error(strerror(errno), out));
	fd[1] = writ; 
	pid = exec_child(1, fd, cmd, env);
	close(fd[0]);
	waitpid(pid, &status, 0);
	return (status);
}

int main(int ac, char *argv[], char **env)
{
    int i;
    int in;
	int	pcount;
	int	fd[2];
	int	k;

	k = 1;
    if (ac > 4)
    {
        i = 0;
        in = open(argv[k++], O_RDONLY);
		if (in == -1)
			return (put_error(strerror(errno), argv[k - 1]));
		pcount = ac - 4;
        while (i < pcount)
        {
			printf("work\n");
            pipe(fd);
            exec_child(in, fd, argv[k++], env);
            close(fd[1]);
            if (i != 0)
                close(in);
            in = fd[0];
			i++;
		}
		k = exec_last_child(fd, argv[k], argv[k + 1], env);
		while (--pcount >= 0)
			wait(NULL);
		return (0);
    }
	ft_putstr_fd("error\n", 1);
    return (1);
}