/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraasve <maraasve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:37:02 by marieke           #+#    #+#             */
/*   Updated: 2024/01/08 17:32:09 by maraasve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/*open flags*/
# include <fcntl.h>

/*malloc*/
# include <stdlib.h>

/*write, access*/
# include <unistd.h>

/*perror*/
# include <stdio.h>

/*wait*/
# include <sys/wait.h>

/*libft*/
# include "../libft/libft.h"

# define INPUT_ERR "Invalid number of arguments.\n"
# define PATH_ERR "Failed to find path.\n"
# define CMD_ERR "Failed to find command.\n"

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		pipe[2];
	int		pid;
	char	*path;
	char	**path_array;
	char	*cmd;
	char	**cmd_args;
}	t_pipex;

int		err_msg(char *msg);
void	free_child(t_pipex *pipex);
void	free_parent(t_pipex *pipex);
char	*get_path(char *envp[]);
char	*get_command(char **paths_array, char *cmd);

#endif