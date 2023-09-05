/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbesa <arbesa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:25:35 by arbesa            #+#    #+#             */
/*   Updated: 2023/06/15 14:44:31 by arbesa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec(char *cmd, char **envp)
{
	char	**tab;
	char	*command;
	char	*old_command;
	t_data	data;

	data.paths = NULL;
	data.tab = NULL;
	data.token = NULL;
	tab = ft_split(cmd, ' ', &data);
	data.tab = tab;
	old_command = ft_strcat("/", tab[0], &data);
	data.token = old_command;
	if (!old_command)
	{
		write(2, "Invalid input: ' '\n", 20);
		ft_exit(&data, 127);
	}
	command = ft_get_command(old_command, envp, &data);
	ft_execve(&data, command, tab, envp);
}

void	first_child(t_pipex *pipex, char **argv, char **envp)
{
	close(pipex->pipes[READ_END]);
	pipex->infile_fd = open(argv[1], O_RDONLY);
	if (pipex->infile_fd == -1)
		ft_perror(argv[1]);
	ft_dup2(pipex->infile_fd, STDIN_FILENO);
	ft_dup2(pipex->pipes[WRITE_END], STDOUT_FILENO);
	ft_exec(argv[2], envp);
}

void	last_child(t_pipex *pipex, char **argv, char **envp)
{
	close(pipex->pipes[WRITE_END]);
	pipex->outfile_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 000644);
	if (pipex->outfile_fd == -1)
		ft_perror(argv[4]);
	ft_dup2(pipex->outfile_fd, STDOUT_FILENO);
	ft_dup2(pipex->pipes[READ_END], STDIN_FILENO);
	ft_exec(argv[3], envp);
}

void	ft_execute_cmds(t_pipex *pipex, char **envp, char **argv)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
		ft_perror("fork() failed");
	else if (pid1 == 0)
		first_child(pipex, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		ft_perror("fork() failed");
	else if (pid2 == 0)
		last_child(pipex, argv, envp);
}
