/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbesa <arbesa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:00:18 by arbesa            #+#    #+#             */
/*   Updated: 2023/06/15 14:43:14 by arbesa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_pipe(int *pipe_fd)
{
	if (pipe(pipe_fd) == -1)
		ft_perror("pipe() failed");
}

void	ft_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		ft_perror("dup2() failed");
}

void	ft_execve(t_data *data, char *command, char **tab, char **envp)
{
	execve(command, tab, envp);
	write(2, "Execve error\n", 14);
	free(command);
	ft_exit(data, EXIT_FAILURE);
}

void	ft_perror(char *error_msg)
{
	close(3);
	close(4);
	close(5);
	close(6);
	perror(error_msg);
	exit(EXIT_FAILURE);
}

void	ft_exit(t_data *data, int exit_code)
{
	close(3);
	close(4);
	close(5);
	close(6);
	if (data->paths)
		ft_free(data->paths);
	if (data->tab)
		ft_free(data->tab);
	if (data->token)
		free(data->token);
	exit(exit_code);
}
