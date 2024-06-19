/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:58:14 by mbaypara          #+#    #+#             */
/*   Updated: 2024/06/19 18:22:09 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = safe_open(av[1], O_RDONLY);
	dup2(fd, 0);
	exec(av[2], env);
}

void	parent(char **av, int *p_fd, char **env)
{
	int	fd;

	fd = safe_open(av[4], O_WRONLY | O_TRUNC | O_CREAT);
	dup2(fd, 1);
	exec(av[3], env);
}

void	handle_child_process(char **av, int *p_fd, char **env)
{
	int		status;
	pid_t	pid1;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("Fork failed");
	}
	if (!pid1)
		child(av, p_fd, env);
	waitpid(pid1, &status, 0);
	if (!WIFEXITED(status))
	{
		perror("Child process terminated abnormally");
		exit(EXIT_FAILURE);
	}
}

void	handle_parent_process(char **av, int *p_fd, char **env)
{
	int		status;
	int		exit_status;
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	if (!pid2)
		parent(av, p_fd, env);
	waitpid(pid2, &status, 0);
	if (!WIFEXITED(status))
	{
		perror("Parent process terminated abnormally");
		exit(EXIT_FAILURE);
	}
	exit_status = WEXITSTATUS(status);
	exit(exit_status);
}

int	main(int ac, char **av, char **env)
{
	int	p_fd[2];

	if (ac != 5)
	{
		perror("Parameter error! Must be:");
		fprintf(stderr, "./pipex infile cmd cmd outfile\n");
		exit(EXIT_FAILURE);
	}
	check(av);
	if (pipe(p_fd) == -1)
	{
		perror("Pipe failed");
		exit(EXIT_FAILURE);
	}
	handle_child_process(av, p_fd, env);
	handle_parent_process(av, p_fd, env);
	return (0);
}
