/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:49:48 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/03 14:16:39 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void child(int *fd, char **av, char **envp)
{
	close fd[0];
}

void parent(int *fd, char **av, char **envp)
{
	
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
			close(fd[1]);
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
