/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbesa <arbesa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:23:19 by arbesa            #+#    #+#             */
/*   Updated: 2023/06/15 14:44:02 by arbesa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# define WRITE_END 1
# define READ_END 0

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		pipes[2];
	int		fd[2];
}	t_pipex;

typedef struct s_data
{
	char	**paths;
	char	**tab;
	char	*token;
}	t_data;

void	ft_free(char **tab);
void	ft_perror(char *error_msg);
void	ft_dup2(int old_fd, int new_fd);
void	ft_execve(t_data *data, char *command, char **tab, char **envp);
void	ft_pipe(int *pipe_fd);
char	*ft_strcat(char *dest, char *src, t_data *data);
char	**ft_split(char const *s, char c, t_data *data);
void	ft_execute_cmds(t_pipex *pipex, char **envp, char **argv);
void	last_child(t_pipex *pipex, char **argv, char **envp);
void	first_child(t_pipex *pipex, char **argv, char **envp);
void	ft_exec(char *cmd, char **envp);
char	*ft_get_command(char *token, char **envp, t_data *data);
void	pipex(int argc, char **argv, char **envp);
int		ft_strlen(char *str);
void	ft_exit(t_data *data, int exit_code);
#endif
