/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieke <marieke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:37:02 by marieke           #+#    #+#             */
/*   Updated: 2025/07/05 16:31:59 by marieke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
# include <libft.h>

# define INPUT_ERR "Invalid number of arguments.\n"
# define PATH_ERR "Path not found.\n"
# define CMD_ERR "Command not found.\n"

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		pipe[2];
	int		pid_index;
	int		exit_status;
	char	*path;
	char	**path_array;
	char	*cmd;
	char	**cmd_args;
	int		*pid;
}	t_pipex;

int		err_msg(char *msg);
void	free_child(t_pipex *pipex);
void	free_parent(t_pipex *pipex);
char	*get_path(char *envp[]);
char	*get_command(char **paths_array, char *cmd);
void	close_parent_pipes(t_pipex *pipex);

#endif