/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraasve <maraasve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:37:05 by marieke           #+#    #+#             */
/*   Updated: 2024/01/08 17:31:16 by maraasve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_cmd(t_pipex pipex, char *cmd, char *envp[])
{
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		dup2(pipex.in_fd, STDIN_FILENO);
		close(pipex.in_fd);
		dup2(pipex.out_fd, STDOUT_FILENO);
		close(pipex.out_fd);
		pipex.cmd_args = ft_split(cmd, ' ');
		if (!pipex.cmd_args)
		{
			err_msg(CMD_ERR);
			exit(1);
		}
		pipex.cmd = get_command(pipex.path_array, pipex.cmd_args[0]);
		if (!pipex.cmd)
		{
			free_child(&pipex);
			err_msg(CMD_ERR);
			exit(1);
		}
		execve(pipex.cmd, pipex.cmd_args, envp);
		perror("Execve");
		exit(1);
	}
}

int	pipe_and_execute(t_pipex pipex, int argc, char *argv[], char *envp[])
{
	int		i;
	char	*cmd;

	execute_cmd(pipex, argv[argc - 2], envp);
	i = 2;
	while (i < argc - 2)
	{
		if (pipe(pipex.pipe) < 0)
			return (perror("Pipe"), 1);
		pipex.out_fd = pipex.pipe[1];
		cmd = argv[i];
		execute_cmd(pipex, cmd, envp);
		close(pipex.in_fd);
		pipex.in_fd = pipex.pipe[0];
		close(pipex.out_fd);
		i++;
	}
	pipex.out_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	execute_cmd(pipex, argv[argc - 2], envp);
	return (0);
}

int	init_pipex(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
	pipex->in_fd = open(argv[1], O_RDONLY);
	if (pipex->in_fd < 0)
		return (perror("Infile"), 1);
	pipex->path = get_path(envp);
	if (!pipex->path)
		return (err_msg(PATH_ERR));
	pipex->path_array = ft_split(pipex->path, ':');
	if (!pipex->path_array)
		return (err_msg(PATH_ERR));
	pipex->out_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->in_fd < 0)
		return (perror("Outfile"), 1);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		i;

	if (argc < 5)
		return (err_msg(INPUT_ERR));
	if (init_pipex(&pipex, argc, argv, envp) == 1)
		return (1);
	if (pipe_and_execute(pipex, argc, argv, envp) == 1)
		return (1);
	i = 0;
	while (i < argc - 3)
	{
		wait(NULL);
		i++;
	}
	free_parent(&pipex);
	return (0);
}
