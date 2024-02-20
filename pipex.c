/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraasve <maraasve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:37:05 by marieke           #+#    #+#             */
/*   Updated: 2024/02/20 15:47:22 by maraasve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	cmd_innit(t_pipex *pipex, char *cmd)
{
	pipex->cmd_args = ft_split(cmd, ' ');
	if (!pipex->cmd_args)
	{
		free_child(pipex);
		free_parent(pipex);
		close_parent_pipes(pipex);
		return (err_msg(CMD_ERR));
	}
	pipex->cmd = get_command(pipex->path_array, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		free_child(pipex);
		free_parent(pipex);
		close_parent_pipes(pipex);
		return (err_msg(CMD_ERR));
	}
	return (0);
}

void	execute_cmd(t_pipex *pipex, char *cmd, char *envp[])
{
	pipex->pid[pipex->pid_index] = fork();
	if (pipex->pid[pipex->pid_index] == 0)
	{
		if (pipex->in_fd < 0 || pipex->out_fd < 0)
			exit(1);
		dup2(pipex->in_fd, STDIN_FILENO);
		close(pipex->pipe[0]);
		dup2(pipex->out_fd, STDOUT_FILENO);
		close(pipex->pipe[1]);
		if (cmd_innit(pipex, cmd) != 0)
			exit(127);
		execve(pipex->cmd, pipex->cmd_args, envp);
		free_child(pipex);
		free_parent(pipex);
		close_parent_pipes(pipex);
		perror("Execve");
		exit(1);
	}
	++pipex->pid_index;
}

int	pipe_and_execute(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
	int		i;
	char	*cmd;

	i = 2;
	while (i < argc - 2)
	{
		if (pipe(pipex->pipe) < 0)
			return (perror("Pipe"), 1);
		pipex->out_fd = pipex->pipe[1];
		cmd = argv[i];
		execute_cmd(pipex, cmd, envp);
		close(pipex->in_fd);
		pipex->in_fd = pipex->pipe[0];
		close(pipex->out_fd);
		i++;
	}
	pipex->out_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex->out_fd < 0)
		return (free_parent(pipex), close_parent_pipes(pipex), 1);
	execute_cmd(pipex, argv[argc - 2], envp);
	return (0);
}

int	init_pipex(t_pipex *pipex, int argc, char *argv[], char *envp[])
{
	pipex->in_fd = open(argv[1], O_RDONLY);
	if (pipex->in_fd < 0)
		perror("Input");
	pipex->path = get_path(envp);
	if (!pipex->path)
		return (err_msg(PATH_ERR), 0);
	pipex->path_array = ft_split(pipex->path, ':');
	if (!pipex->path_array)
	{
		close(pipex->in_fd);
		free(pipex->path);
		return (err_msg(PATH_ERR));
	}
	pipex->pid_index = 0;
	pipex->pid = ft_calloc((argc - 3), sizeof(int));
	if (!pipex->pid)
	{
		close(pipex->in_fd);
		return (1);
	}
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
	if (pipe_and_execute(&pipex, argc, argv, envp) == 1)
		return (1);
	i = 0;
	close_parent_pipes(&pipex);
	while (i < argc - 3)
	{
		waitpid(pipex.pid[i], &pipex.exit_status, 0);
		i++;
	}
	free_parent(&pipex);
	return (WEXITSTATUS(pipex.exit_status));
}
