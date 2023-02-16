/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:23:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/02/15 15:28:05 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "pipex.h"

//take PATH=/usr/.... from envp command;
char	*path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			break ;
		i++;
	}
	return (env[i]);
}

//make the command path that we need for execve() function;
char	*cmd_path(char **envp, char *av)
{
	char	**str1;
	char	**splited_path;
	char	*slash_before_cmd;
	char	*cmd_path;
	int		i;

	str1 = ft_split(av, ' ');
	if (!access(str1[0], F_OK))
		return (str1[0]);
	i = 0;
	slash_before_cmd = ft_strjoin("/", str1[0]);
	splited_path = ft_split(path(envp) + 5, ':');
	if (splited_path[i])
	{
		while (splited_path[i])
		{
			cmd_path = ft_strjoin(splited_path[i], slash_before_cmd);
			if (!access(cmd_path, F_OK))
				return (cmd_path);
			i++;
		}
	}
	return (NULL);
}

void	child1(int id, char **av, char **envp, int fd[])
{
	int		file1;
	char	**str1;

	fork_error(id);
	if (id == 0)
	{
		close(fd[0]);
		file1 = open(av[1], O_RDONLY, 0777);
		open_error(file1);
		dup2(file1, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		str1 = ft_split(av[2], ' ');
		not_found(envp, av[2]);
		execve(cmd_path(envp, av[2]), str1, envp);
	}
}

void	child2(int id2, char **av, char **envp, int fd[])
{
	int		id;
	int		file2;
	char	**str2;

	id = fork();
	child1(id, av, envp, fd);
	id2 = fork();
	fork_error(id2);
	if (id2 == 0)
	{
		close(fd[1]);
		file2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		open_error(file2);
		dup2(file2, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		str2 = ft_split(av[3], ' ');
		not_found(envp, av[3]);
		execve(cmd_path(envp, av[3]), str2, envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(id, NULL, 0);
}

int	main(int ac, char *av[], char *envp[])
{
	int	fd[2];
	int	p;
	int	id;

	p = 0;
	id = 0;
	if (ac != 5)
	{
		perror("please enter 5 arguments including a.out");
		exit(EXIT_FAILURE);
	}
	else
	{
		p = pipe(fd);
		if (p == -1)
		{
			perror("Error occured with pipe() function");
			exit(EXIT_FAILURE);
		}
		child2(id, av, envp, fd);
	}
}
