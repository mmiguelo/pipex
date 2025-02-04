/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:34:18 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/05 10:58:43 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../my_libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>

/*=============================================================================#
#                               DEFINES                                        #
#=============================================================================*/

# define PIPE_ERROR "An error ocurred with opening the pipe\n"
# define FORK_ERROR "An error ocurred with forking"
# define OPEN_CHILD_ERROR "An error ocurred with opening the input file"
# define OPEN_PARENT_ERROR "An error occured with opening av[2]"
# define COMMAND_NOT_FOUND "Command not found"

/*=============================================================================#
#                               GENERAL                                        #
#=============================================================================*/

void	child(int *fd, char **av, char **envp);
void	parent(int *fd, char **av, char **envp);
void	process(char *argv, char **envp);
char	*search_path(char *command, char **envp);

#endif