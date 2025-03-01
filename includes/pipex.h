/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:34:18 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/13 10:59:15 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../my_libft/includes/libft.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	int		cmd;
	char	envp;
	pid_t	pid;
	int		fd[2];
	int		last_fd;
}			t_pipex;

/*=============================================================================#
#                               DEFINES                                        #
#=============================================================================*/

# define PIPE_ERROR "An error ocurred with opening the pipe\n"
# define FORK_ERROR "An error ocurred with forking"
# define OPEN_CHILD_ERROR "An error ocurred with opening the input file"
# define OPEN_PARENT_ERROR "An error occured with opening the output file"
# define COMMAND_NOT_FOUND "Command not found"
# define EXECVE_ERROR "An error ocurred with execve"
# define ENVP_ERROR "No environment variables found"
# define PATH_ERROR "No PATH variable found in the envp"
# define INPUT_ERROR "Wrong input. try ./pipex here_doc LIMITER cmd cmd1 file\n"
# define INPUT2_ERROR "Wrong input. Try ./pipex file1 cmd1 cmd2 file2\n"

/*=============================================================================#
#                               GENERAL                                        #
#=============================================================================*/

void	child(int *fd, char **av, char **envp);
void	parent(int *fd, char **av, char **envp);
void	process(char *argv, char **envp);
char	*search_path(char *command, char **envp);

/*=============================================================================#
#                               UTILS                                          #
#=============================================================================*/

int		parse(char **envp, char **argv);
void	ft_free(char **str);

#endif