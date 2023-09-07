/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrepkov <akrepkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:10:45 by akrepkov          #+#    #+#             */
/*   Updated: 2023/02/17 12:54:59 by akrepkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_paths(char **commands, const char *envp[])
{
	int			i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			pipex.path = (char *)&envp[i][5];
		i++;
	}
	i = 0;
	pipex.paths = ft_split(pipex.path, ':');
	while (pipex.paths[i] != NULL)
	{
		pipex.path = ft_strjoin_extra(pipex.paths[i], commands[0]);
		if (access(pipex.path, F_OK) == 0)
		{
			if (execve(pipex.path, commands, NULL) == -1)
				ft_perror(ERR_C);
		}
		i++;
	}
	free (pipex.path);
	ft_perror(ERR_C);
}

void	firstchild(char *comm_input, const char *envp[], int infile, int *fd)
{
	char	**commands;

	if (dup2(fd[1], STDOUT_FILENO) < 0)
		ft_perror (ERR_FILE);
	if (dup2(infile, STDIN_FILENO) < 0)
		ft_perror (ERR_FILE);
	close(fd[0]);
	close(infile);
	close(fd[1]);
	commands = ft_split(comm_input, ' ');
	if (!commands)
		ft_perror (ERR_C);
	ft_paths(commands, envp);
}

void	secondchild(char *comm_input, const char *envp[], int outfile, int *fd)
{
	char	**commands;

	if (dup2(fd[0], STDIN_FILENO) < 0)
		ft_perror (ERR_FILE);
	if (dup2(outfile, STDOUT_FILENO) < 0)
		ft_perror (ERR_FILE);
	close(fd[1]);
	close(outfile);
	close(fd[0]);
	commands = ft_split(comm_input, ' ');
	if (!commands)
		ft_perror (ERR_C);
	ft_paths(commands, envp);
}

void	ft_pipex(int *fd, char *argv[], const char *envp[], int argc)
{
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		ft_perror (ERR_FILE);
	pipex.outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex.outfile < 0)
		ft_perror (ERR_FILE);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		ft_perror (ERR_W);
	else if (pipex.pid1 == 0)
		firstchild(argv[2], envp, pipex.infile, fd);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		ft_perror (ERR_W);
	else if (pipex.pid2 == 0)
		secondchild(argv[3], envp, pipex.outfile, fd);
}

int	main(int argc, char *argv[], const char *envp[])
{
	int		fd[2];

	if (argc != 5)
		ft_perror (ERR_ARG);
	if (pipe(fd) == -1)
		ft_perror (ERR_W);
	ft_pipex(fd, argv, envp, argc);
	close(fd[1]);
	close(fd[0]);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (0);
}
