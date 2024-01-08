/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraasve <maraasve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:05:53 by marieke           #+#    #+#             */
/*   Updated: 2024/01/02 18:01:03 by maraasve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

void	close_pipe(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}

void	fork_process(t_pipex *pipex, char *argv[], char *envp[])
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
	{
		free_parent(pipex);
		perror("Fork");
		exit(1);
	}
	if (pipex->pid1 == 0)
		first_child(*pipex, argv, envp);
	else
	{
		pipex->pid2 = fork();
		if (pipex->pid2 < 0)
		{
			free_parent(pipex);
			perror("Fork");
			exit(1);
		}
	}
	if (pipex->pid2 == 0)
		second_child(*pipex, argv, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		exit_status;

	if (argc != 5)
		return (err_msg(ERR_ARGS));
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		return (perror("Infile"), 1);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.outfile < 0)
		return (perror("Outfile"), 1);
	if (pipe(pipex.pipe) < 0)
		return (perror("Pipe"), 1);
	pipex.paths = get_path(envp);
	if (!pipex.paths)
		return (err_msg(ERR_PATHS));
	pipex.paths_array = ft_split(pipex.paths, ':');
	if (!pipex.paths_array)
		return (err_msg(ERR_PATHS));
	fork_process(&pipex, argv, envp);
	close_pipe(&pipex);
	waitpid(pipex.pid1, &exit_status, 0);
	waitpid(pipex.pid2, &exit_status, 0);
	free_parent(&pipex);
	return (WEXITSTATUS(exit_status));
}
