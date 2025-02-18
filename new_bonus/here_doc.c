/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 22:23:36 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/14 15:11:38 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	child_bonus(t_pipex *pipes)
{
	pipes->here_doc = false;
	if (ft_strncmp(pipes->argv[1], "here_doc", 8) == 0 && pipes->cmd == 3)
	{
		create_here_doc(pipes);
		exit(EXIT_SUCCESS);
	}
	close(pipes->fd[0]);
	dup2(pipes->fd[1], STDOUT_FILENO);
	process(pipes->argv[pipes->cmd], pipes->envp, pipes->fd);
}

void	create_here_doc(t_pipex *pipes)
{
	const char	*limiter;
	char		*line;

	limiter = pipes->argv[2];
	close(pipes->fd[0]);
	while (1)
	{
		if (pipes->cmd == 3 && pipes->here_doc == true)
			ft_printf("pipex_bonus here_doc> ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if ((ft_strncmp(line, limiter, ft_strlen(limiter)) == 0) && line[ft_strlen(limiter)] == '\n')
		{
			close(STDIN_FILENO);
			free(line);
			line = get_next_line(STDIN_FILENO);
			free(line);
			line = NULL;
			break ;
		}
		write(pipes->fd[1], line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	close(pipes->fd[1]);
}

void	create_process(t_pipex *pipes)
{
	while (pipes->cmd < pipes->argc - 2)
	{
		if (pipe(pipes->fd) == -1)
			perror(PIPE_ERROR);
		pipes->pid = create_fork(pipes);
		if (pipes->pid == 0)
		{
			close(pipes->fd[0]);
			child_bonus(pipes);
		}
		close(pipes->fd[1]);
		dup2(pipes->fd[0], STDIN_FILENO);
		close(pipes->fd[0]);
		pipes->cmd++;
	}
	pipes->last_fd = open(pipes->argv[pipes->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (pipes->last_fd == -1)
		perror(OPEN_PARENT_ERROR);
	dup2(pipes->last_fd, STDOUT_FILENO);
	close(pipes->last_fd);
	process(pipes->argv[pipes->cmd], pipes->envp, pipes->fd);
}

void	start_here_doc(t_pipex *pipes)
{
	if (pipe(pipes->fd) == -1)
		perror(PIPE_ERROR);
	pipes->pid = fork();
	if (pipes->pid == -1)
	{
		close(pipes->fd[0]);
		close(pipes->fd[1]);
		perror(FORK_ERROR);
	}
	if (pipes->pid == 0)
		create_here_doc(pipes);
	else
	{
		close(pipes->fd[1]);
		dup2(pipes->fd[0], STDIN_FILENO);
		close(pipes->fd[0]);
		create_process(pipes);
	}
}
