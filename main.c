/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:49:48 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/03 15:47:22 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief 
 * 
 * @param fd 
 * @param av 
 * @param envp 
 */
void	child(int *fd, char **av, char **envp)
{
	int	fd_child;

	close(fd[0]);
	fd_child = open(av[1], O_RDONLY, 444);
	if (fd_child == -1)
	{
		perror(OPEN_CHILD_ERROR);
		close(fd);
		exit(1);
	}
	dup2;
	dup2;
	execute;
}

/**
 * @brief 
 * 
 * @param fd 
 * @param av 
 * @param envp 
 */
void	parent(int *fd, char **av, char **envp)
{
	int	fd_parent;

	close(fd[1]);
	fd_parent = open(av[4], O_WRONLY, O_TRUNC, O_CREAT, 0644);
	read(fd[0]);
	close(fd[0]);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	// fd[0] - read
	// fd[1] - write
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
		if (!pid)
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
