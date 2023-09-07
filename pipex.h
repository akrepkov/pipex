/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrepkov <akrepkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:27:18 by akrepkov          #+#    #+#             */
/*   Updated: 2023/02/17 13:06:19 by akrepkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <fcntl.h>
# include "libft/libft.h"

# define ERR_ARG	"Wrong amount of arg"
# define ERR_FILE	"Problems with file"
# define ERR_C		"Problems with commands"
# define ERR_W		"Something went wrong"

struct s_pipe {
	int		infile;
	int		outfile;
	char	**paths;
	pid_t	pid1;
	pid_t	pid2;
	char	*path;
} pipex;

void	ft_paths(char **commands, const char *envp[]);
void	ft_perror(char *str);
void	firstchild(char *comm_input, const char *envp[], int infile, int *fd);
void	secondchild(char *comm_input, const char *envp[], int outfile, int *fd);
void	ft_pipex(int *fd, char *argv[], const char *envp[], int argc);

#endif
