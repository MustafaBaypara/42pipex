/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:04:38 by mbaypara          #+#    #+#             */
/*   Updated: 2024/03/19 13:08:10 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	check(char **av)
{
	int	fd[2];

	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (access(av[1], F_OK) == -1)
	{
		perror("No File ERROR:");
		ft_putstr_fd("no such file or directory", 2);
		exit(EXIT_FAILURE);
	}
	else if (access(av[1], R_OK) == -1)
	{
		perror("Permission Error");
		ft_putstr_fd("permission denied", 2);
		exit(EXIT_FAILURE);
	}
	if (access(av[4], W_OK | R_OK) == -1)
	{
		perror("Permission Error");
		ft_putstr_fd("permission denied", 2);
		exit(EXIT_FAILURE);
	}
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = safe_substr(env[i], 0, j);
		if (ft_strncmp(sub, name, ft_strlen(sub)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (0);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*ppart;
	char	**s_cmd;

	i = -1;
	allpath = safe_split(my_getenv("PATH", env), ':');
	s_cmd = safe_split(cmd, ' ');
	while (allpath[++i])
	{
		ppart = safe_strjoin(allpath[i], "/");
		exec = safe_strjoin(ppart, s_cmd[0]);
		free(ppart);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			ft_free_tab(allpath);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (cmd);
}

void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = safe_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		perror("ERROR EXECUTE");
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_free_tab(s_cmd);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
