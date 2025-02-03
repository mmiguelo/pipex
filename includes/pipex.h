/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:34:18 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/02/03 10:51:36 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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