/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbesa <arbesa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:05:25 by arbesa            #+#    #+#             */
/*   Updated: 2023/06/15 14:35:04 by arbesa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	**get_path(char **envp, t_data *data);
static void	ft_command_not_found(char *token, t_data *data);

void	pipex(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		write(2, "file1 cmd1 cmd2 file2\n", 23);
		exit(EXIT_FAILURE);
	}
	ft_pipe(pipex.pipes);
	ft_execute_cmds(&pipex, envp, argv);
	close(pipex.pipes[READ_END]);
	close(pipex.pipes[WRITE_END]);
	while (waitpid(-1, NULL, 0) > 0)
		;
}

char	*ft_get_command(char *token, char **envp, t_data *data)
{
	char	**paths;
	char	*path_tested;
	int		i;

	i = 0;
	paths = get_path(envp, data);
	while (paths[i])
	{
		path_tested = ft_strcat(paths[i], token, data);
		if (access(path_tested, X_OK) != -1)
			return (path_tested);
		free(path_tested);
		i++;
	}
	if (access(token, X_OK) != -1)
		return (token);
	ft_command_not_found(token, data);
	return (NULL);
}

static char	**get_path(char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (envp[i] && !(envp[i][0] == 'P' && envp[i][1] == 'A' && \
		envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '='))
		i++;
	if (envp[i])
	{
		data->paths = ft_split(envp[i] + 5, ':', data);
		return (data->paths);
	}
	data->paths = ft_split(" ", ' ', data);
	return (data->paths);
}

static void	ft_command_not_found(char *token, t_data *data)
{
	write(2, "Pipex d'A: ", 12);
	write(2, &token[1], ft_strlen(&token[1]));
	write(2, ": command not found\n", 21);
	ft_exit(data, 127);
}
