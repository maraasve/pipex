/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieke <marieke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:56:43 by marieke           #+#    #+#             */
/*   Updated: 2025/07/05 16:33:48 by marieke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	err_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
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
