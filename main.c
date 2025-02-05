/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:49:48 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/05 15:18:05 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief 
 * 
 * @param command 
 * @param envp 
 * @return void* 
 */
void	*search_path(char *command, char **envp)
{
	
}

/**
 * @brief 
 * 
 * @param command 
 * @param envp 
 */
void	process(char *argv, char **envp)
{
	char	**command;
	int		i;
	char	*path;

	i = -1;
	command = ft_split(argv, ' ');
	path = search_path(command[0], envp);
	if (!path)
	{
		while (command[++i])
		{
			free(command[i]);
		}
		free(command);
		perror(COMMAND_NOT_FOUND);
		exit(3);
	}
	if (execve(path, command, envp) == -1)
	{
		perror("EXECVE_ERROR");
		exit(4);
	}
}

/**
 * @brief 
 * 
 * @param fd 
 * @param av 
 * @param envp 
 */
void	child(int *fd, char **argv, char **envp)
{
	int	fd_in;

	close(fd[0]);
	fd_in = open(argv[1], O_RDONLY, 0444);
	if (fd_in == -1)
	{
		perror(OPEN_CHILD_ERROR);
		close(fd[1]);
		exit(1);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	close(fd[1]);
	process(argv[2], envp);
}

/**
 * @brief 
 * 
 * @param fd 
 * @param av 
 * @param envp 
 */
void	parent(int *fd, char **argv, char **envp)
{
	int	fd_out;

	close(fd[1]);
	fd_out = open(argv[4], O_WRONLY, O_TRUNC, O_CREAT, 0644);
	if (fd_out == -1)
	{
		perror(OPEN_PARENT_ERROR);
		close(fd[0]);
		exit(2);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd[0]);
	process(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			perror(PIPE_ERROR);
		pid = fork();
		if (pid == -1)
		{
			perror(FORK_ERROR);
			close(fd[0]);
		}
		if (pid == 0)
			child(fd, argv, envp);
		parent(fd, argv, envp);
	}
	else
	{
		ft_putstr_fd("Wrong input. Try .pipex file1 cmd1 cmd2 file2\n", 2);
		exit(42);
	}
	return (0);
}
