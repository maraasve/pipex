/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraasve <maraasve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:11:00 by marieke           #+#    #+#             */
/*   Updated: 2023/12/30 14:59:38 by maraasve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*write, execve, acces*/
# include <unistd.h>

/*prinf DEBUGGING DELETE THISSSSS*/
# include <stdio.h>

/*open flags*/
# include <fcntl.h>

/*waitpid*/
# include <sys/wait.h>

/*error handling*/
# include <errno.h>

/*libft*/
# include "libft/libft.h"

/*error messages*/
# define ERR_ARGS "Error: Invalid number of arguments\n"
# define ERR_PATHS "Error: Can't find paths\n"
# define ERR_CMDS "Error: Couldn't find commands\n"

typedef struct s_pipex
{
	int		pipe[2];
	int		pid1;
	int		pid2;
	int		infile;
	int		outfile;
	char	*paths;
	char	**paths_array;
	char	*cmd;
	char	**cmd_args;
}	t_pipex;

/*pipex.c*/
char	*get_path(char *envp[]);

/*utils.c*/
int		err_msg(char *error);
void	free_parent(t_pipex *pipex);
void	free_child(t_pipex *pipex);

/*childs.c*/
char	*get_cmd(char	**paths_array, char *cmd);
void	first_child(t_pipex pipex, char *argv[], char *envp[]);
void	second_child(t_pipex pipex, char *argv[], char *envp[]);

#endif
