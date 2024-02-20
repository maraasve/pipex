/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraasve <maraasve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:56:43 by marieke           #+#    #+#             */
/*   Updated: 2024/02/16 15:16:11 by maraasve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	err_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

void	free_child(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
}

void	free_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->path_array[i])
	{
		free(pipex->path_array[i]);
		i++;
	}
	free(pipex->path_array);
	free(pipex->pid);
}

char	*get_path(char *envp[])
{
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*get_command(char **paths_array, char *cmd)
{
	char	*tmp;
	char	*command;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (*paths_array)
	{
		tmp = ft_strjoin(*paths_array, "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd);
		free (tmp);
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
