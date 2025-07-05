/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieke <marieke@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:56:43 by marieke           #+#    #+#             */
/*   Updated: 2025/07/05 16:30:52 by marieke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

void	close_parent_pipes(t_pipex *pipex)
{
	close(pipex->in_fd);
	close(pipex->out_fd);
}