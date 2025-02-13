/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_utisl_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 21:20:42 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/13 21:20:42 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	process(char *av, char **envp, int *fd)
{
	char	**command;
	char	*path;

	command = ft_split(av, ' ');
	path = search_path(command[0], envp);
	if (!path)
	{
		ft_free(command);
		perror(COMMAND_NOT_FOUND);
		close(fd[0]);
		close(fd[1]);
		exit(3);
	}
	if (execve(path, command, envp) == -1)
	{
		ft_free(command);
		free(path);
		close(fd[0]);
		close(fd[1]);		
		perror(EXECVE_ERROR);
		exit(4);
	}
}

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
