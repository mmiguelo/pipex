/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:34:18 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/01/27 09:10:55 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX
# define PIPEX

# include "../my_libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

/*=============================================================================#
#                               DEFINES                                        #
#=============================================================================*/

# define PIPE_ERROR "An error ocurred with opening the pipe\n"
# define FORK_ERROR "An error ocurred with making a fork"

/*=============================================================================#
#                               GENERAL                                        #
#=============================================================================*/


#endif