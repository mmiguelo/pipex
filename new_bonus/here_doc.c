/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 22:23:36 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/13 22:23:36 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	create_process(t_pipex *pipes)
{
	while (pipes->cmd != pipes->argc - 2)
	{
		if (pipe(pipes->fd) == -1)
			perror(PIPE_ERROR);
		pipes->pid = create_fork(pipes);
		if (pipes->pid == 0)
		{
			close(pipes->fd[0]);
			//falta resolver isto
			child(...);
		}
		close(pipes->fd[1]);
		dup2(pipes->fd[0], STDIN_FILENO);
		close(pipes->fd[0]);
		pipes->cmd++;
	}
	if (pipes->here_doc)
		pipes->last_fd = open(pipes->argv[pipes->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (pipes->last_fd == -1)
		perror(OPEN_PARENT_ERROR);
	dup2(pipes->last_fd, STDOUT_FILENO);
	close(pipes->last_fd);
	//falta resolver isto
	process(...);
}

void	create_here_doc(t_pipex *pipes)
{
	const char	*limiter;
	char		*line;

	limiter = pipes->argv[2];
	close(pipes->fd[0]);
	while (1)
	{
		ft_printf("pipex_bonus here_doc> ");
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(pipes->fd[1], line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	close(pipes->fd[1]);
}
