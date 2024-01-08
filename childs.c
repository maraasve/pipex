/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraasve <maraasve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:08:39 by marieke           #+#    #+#             */
/*   Updated: 2024/01/08 17:27:10 by maraasve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(char	**paths_array, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths_array)
	{
		tmp = ft_strjoin(*paths_array, "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		tmp = NULL;
		if (!command)
			return (NULL);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		command = NULL;
		paths_array++;
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.pipe[1], 1);
	close(pipex.pipe[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_args = ft_split(argv[2], ' ');
	if (!pipex.cmd_args)
	{
		err_msg(ERR_CMDS);
		close(pipex.pipe[1]);
		exit(1);
	}
	pipex.cmd = get_cmd(pipex.paths_array, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		err_msg(ERR_CMDS);
		close(pipex.pipe[1]);
		free_child(&pipex);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
	perror("Execve");
}

void	second_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = ft_split(argv[3], ' ');
	if (!pipex.cmd_args)
	{
		err_msg(ERR_CMDS);
		close(pipex.pipe[0]);
		exit(1);
	}
	pipex.cmd = get_cmd(pipex.paths_array, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		err_msg(ERR_CMDS);
		close(pipex.pipe[0]);
		free_child(&pipex);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
	perror("Execve");
}
