/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:49:48 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/06 16:08:32 by mmiguelo         ###   ########.fr       */
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
			return (partial_path);
		free(partial_path);
		i++;
	}
	ft_free(full_path);
	return (NULL);
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
	char	*path;

	command = ft_split(argv, ' ');
	path = search_path(command[0], envp);
	if (!path)
	{
		ft_free(command);
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
		exit(3);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
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
	fd_out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd_out == -1)
	{
		perror(OPEN_PARENT_ERROR);
		close(fd[0]);
		exit(4);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	process(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	parse(envp);
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
		else if (pid == 0)
			child(fd, argv, envp);
		parent(fd, argv, envp);
	}
	else
	{
		ft_putstr_fd("Wrong input. Try .pipex file1 cmd1 cmd2 file2\n", 2);
		return (0);
	}
	return (0);
}
