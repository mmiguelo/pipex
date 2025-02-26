/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:09:03 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/14 13:34:34 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	process(char *av, char **env, int *fd)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (ft_strchr(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else
		path = search_path(cmd[0], env);
	if (!path)
	{
		ft_free(cmd);
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	execve(path, cmd, env);
	close(fd[0]);
	close(fd[1]);
	free(path);
	ft_free(cmd);
	perror(EXECVE_ERROR);
}

void	child_process(t_pipex *pipes)
{
	int		fd;

	if (ft_strncmp(pipes->av[1], "here_doc", 8) == 0 && pipes->cmd == 2)
	{
		create_here_doc(pipes);
		exit(EXIT_SUCCESS);
	}
	if (pipes->cmd == 2)
	{
		fd = open(pipes->av[1], O_RDONLY);
		if (fd == -1)
			perror(OPEN_CHILD_ERROR);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	dup2(pipes->fd[1], STDOUT_FILENO);
	close(pipes->fd[1]);
	process(pipes->av[pipes->cmd], pipes->env, pipes->fd);
	exit(EXIT_FAILURE);
}

void	main_process(t_pipex *pipes)
{
	while (pipes->cmd < pipes->ac - 2)
	{
		if (pipe(pipes->fd) == -1)
			perror(PIPE_ERROR);
		pipes->pid = create_fork(pipes);
		if (pipes->pid == 0)
		{
			close(pipes->fd[0]);
			child_process(pipes);
		}
		close(pipes->fd[1]);
		dup2(pipes->fd[0], STDIN_FILENO);
		close(pipes->fd[0]);
		pipes->cmd++;
	}
	open_file(pipes);
	dup2(pipes->last_fd, STDOUT_FILENO);
	close(pipes->last_fd);
	process(pipes->av[pipes->cmd], pipes->env, pipes->fd);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipes;

	if (ac < 5)
		return (ft_putstr_fd(INPUT2_ERROR, 2), 1);
	if ((ft_strncmp(av[1], "here_doc", 8) == 0 && ac < 6))
		return (ft_putstr_fd(INPUT_ERROR, 2), 1);
	ft_init_pipes(&pipes, ac, av, env);
	parse_bonus(env, av);
	if (pipes.here_doc)
	{
		if (pipe(pipes.fd) == -1)
			return (ft_putstr_fd(PIPE_ERROR, 2), 1);
		pipes.pid = create_fork(&pipes);
		if (pipes.pid == 0)
			create_here_doc(&pipes);
		else
		{
			close(pipes.fd[1]);
			dup2(pipes.fd[0], STDIN_FILENO);
			close(pipes.fd[0]);
			main_process(&pipes);
		}
	}
	else
		main_process(&pipes);
}
