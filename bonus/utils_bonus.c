/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:51:53 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/13 15:14:11 by mmiguelo         ###   ########.fr       */
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

void	child(int *fd, char **argv, char **envp)
{
	int	fd_in;

	close(fd[0]);
	fd_in = open(argv[1], O_RDONLY, 0444);
	if (fd_in == -1)
	{
		perror(OPEN_CHILD_ERROR);
		close(fd[1]);
		exit(3);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	process(argv[2], envp);
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
