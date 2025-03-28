/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:58:54 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/14 14:52:11 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../my_libft/includes/libft.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_pipex
{
	int		ac;
	char	**av;
	char	**env;
	int		cmd;
	int		fd[2];
	pid_t	pid;
	int		last_fd;
	bool	here_doc;
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
# define INPUT_ERROR "Wrong input. try ./pipex here_doc LIMITER cmd cmd1 file"
# define INPUT2_ERROR "Wrong input. Try ./pipex file1 cmd1 cmd2 file2"

/*=============================================================================#
#                              PIPEX BONUS                                     #
#=============================================================================*/

void	process(char *av, char **env, int *fd);
void	child_process(t_pipex *pipes);
void	main_process(t_pipex *pipes);

/*=============================================================================#
#                               HERE_DOC                                       #
#=============================================================================*/

void	create_here_doc(t_pipex *pipes);
char	*search_path(char *cmd, char **env);

/*=============================================================================#
#                               UTILS BONUS                                    #
#=============================================================================*/

void	parse_bonus(char **envp, char **av);
pid_t	create_fork(t_pipex *pipes);
void	ft_init_pipes(t_pipex *pipes, int ac, char **av, char **envp);
void	open_file(t_pipex *pipes);
void	ft_free(char **str);

#endif