/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:51:53 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/13 12:28:57 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * @brief 
 * 
 * @param pipe 
 */
void	ft_init_pipes(t_pipex *pipes, int argc, char **argv, char **envp)
{
	pipes->argc = argc;
	pipes->argv = argv;
	pipes->envp = envp;
	if (ft_strcmp("here_doc", argv[1]) == 0)
	{
		pipes->here_doc = true;
		pipes->cmd = 3;
	}
	else
	{
		pipes->here_doc = false;
		pipes->cmd = 2;
	}
}

void	parse_bonus(char **envp, char **argv)
{
	int	i;

	if (!envp || !*envp)
	{
		ft_putstr_fd(ENVP_ERROR, 2);
		exit(1);
	}
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
	{
		ft_putstr_fd(PATH_ERROR, 2);
		exit(2);
	}
	i = -1;
	while (argv[++i])
	{
		if (argv[i] && !argv[i][0])
		{
			ft_putstr_fd(INPUT2_ERROR, 2);
			exit(3);
		}
	}
	return ;
}

pid_t	create_fork(t_pipex *pipes)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror(FORK_ERROR);
		close(pipes->fd[0]);
	}
	return (pid);
}
