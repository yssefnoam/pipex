/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 10:43:21 by ynoam             #+#    #+#             */
/*   Updated: 2021/06/08 10:44:05 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char *argv[], char **env)
{
	int	i;
	int	in;
	int	pcount;
	int	fd[2];
	int	k;

	k = 1;
	if (ac < 5)
		return (put_error("error argument.", "syntax"));
	i = 0;
	in = open(argv[k++], O_RDONLY);
	if (in == -1)
		return (put_error(strerror(errno), argv[k - 1]));
	pcount = ac - 4;
	while (i < pcount)
	{
		pipe(fd);
		exec_child(in, fd, argv[k++], env);
		close(fd[1]);
		if (i++ != 0)
			close(in);
		in = fd[0];
	}
	k = exec_last_child(fd, argv[k], argv[k + 1], env);
	return (wait_proc(pcount));
}
