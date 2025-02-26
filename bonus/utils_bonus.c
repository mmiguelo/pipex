/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:20:42 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/14 13:20:11 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parse_bonus(char **env, char **av)
{
	int	i;

	if (!env || !*env)
	{
		ft_putstr_fd(ENVP_ERROR, 2);
		exit(1);
	}
	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (!env[i])
	{
		ft_putstr_fd(PATH_ERROR, 2);
		exit(2);
	}
	i = -1;
	while (av[++i])
	{
		if (av[i] && !av[i][0])
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
		close(pipes->fd[1]);
	}
	return (pid);
}

void	ft_init_pipes(t_pipex *pipes, int ac, char **av, char **env)
{
	pipes->ac = ac;
	pipes->av = av;
	pipes->env = env;
	if (ft_strcmp("here_doc", av[1]) == 0)
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

void	open_file(t_pipex *pipes)
{
	if (ft_strncmp(pipes->av[1], "here_doc", 8) == 0)
		pipes->last_fd = open(pipes->av[pipes->ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipes->last_fd = open(pipes->av[pipes->ac - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipes->last_fd == -1)
		perror(OPEN_PARENT_ERROR);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
