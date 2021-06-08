/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 10:27:39 by ynoam             #+#    #+#             */
/*   Updated: 2021/06/08 10:27:40 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	put_error(char *errorstr, char *filename)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(errorstr, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	is_path(char *cmd)
{
	int	i;

	i = ft_strlen(cmd);
	if ((i >= 2 && cmd[0] == '.' && cmd[1] == '/')
		|| (i >= 3 && cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
		|| (i >= 1 && cmd[0] == '/'))
		return (1);
	return (0);
}

char	*find_path(char **env)
{
	int	i;
	int	j;

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

int	exec_normal2(char *argv[], char **env)
{
	execve(argv[0], argv, env);
	put_error(strerror(errno), argv[0]);
	return (0);
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
