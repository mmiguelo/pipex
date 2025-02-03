/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:49:48 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/03 14:54:46 by mmiguelo         ###   ########.fr       */
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
	write(fd[1], &fd_child, );
	close(fd[1]);
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
	close(fd[1]);
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
