/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:42:25 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/13 16:09:23 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*search_path(char *command, char **envp)
{
	char	**full_path;
	char	*partial_path;
	char	*temp;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	full_path = ft_split(envp[i] + 5, ':' );
	if (!full_path)
		return (NULL);
	i = 0;
	while (full_path[i])
	{
		temp = ft_strjoin(full_path[i], "/");
		partial_path = ft_strjoin(temp, command);
		free(temp);
		if (access(partial_path, F_OK | X_OK) == 0)
			return (ft_free(full_path), partial_path);
		free(partial_path);
		i++;
	}
	ft_free(full_path);
	return (NULL);
}

void	process(char *argv, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(argv, ' ');
	if (!command || !command[0])
	{
		free(command);
		perror("Error splitting command");
		exit(2);
	}
	path = search_path(command[0], envp);
	if (!path)
	{
		ft_free(command);
		perror(COMMAND_NOT_FOUND);
		exit(3);
	}
	if (execve(path, command, envp) == -1)
	{
		perror(EXECVE_ERROR);
		ft_free(command);
		free(path);
		exit(4);
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
			child(pipes->fd, pipes->argv, pipes->envp);
		}
		close(pipes->fd[1]);
		dup2(pipes->fd[0], STDIN_FILENO);
		close(pipes->fd[0]);
		pipes->cmd++;
	}
	if (pipes->here_doc)
		pipes->last_fd = open(pipes->argv[pipes->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		pipes->last_fd = open(pipes->argv[pipes->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipes->last_fd == -1)
		perror(OPEN_PARENT_ERROR);
	dup2(pipes->last_fd, STDOUT_FILENO);
	close(pipes->last_fd);
	process(pipes->argv[pipes->cmd], pipes->envp);
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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipes;

	if (argv[1] && (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
		return (ft_putstr_fd(INPUT_ERROR, 2), 4);
	if (argc < 5)
		return (ft_putstr_fd(INPUT2_ERROR, 2), 5);
	parse_bonus(envp, argv);
	ft_init_pipes(&pipes, argc, argv, envp);
	if (pipes.here_doc)
	{
		if (pipe(pipes.fd) == -1)
			return (ft_putstr_fd(PIPE_ERROR, 2), 6);
		pipes.pid = create_fork(&pipes);
		if (pipes.pid == 0)
			create_here_doc(&pipes);
		else
		{
			close(pipes.fd[1]);
			dup2(pipes.fd[0], STDIN_FILENO);
			close(pipes.fd[0]);
			create_process(&pipes);
		}
	}
	else
		create_process(&pipes);
}
