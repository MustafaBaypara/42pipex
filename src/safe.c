/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:43:18 by mbaypara          #+#    #+#             */
/*   Updated: 2024/06/19 18:22:22 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**safe_split(char *s, char c)
{
	char	**str;

	str = ft_split(s, c);
	if (!str)
	{
		perror("ERROR: Split");
	}
	return (str);
}

char	*safe_strjoin(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (!str)
	{
		perror("ERROR: Strjoin");
		exit(EXIT_FAILURE);
	}
	return (str);
}

int	safe_open(char *file, int flag)
{
	int	fd;

	fd = open(file, flag);
	if (fd == -1)
	{
		perror("ERROR: File does not open.");
		ft_putendl_fd(file, 2);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

char	*safe_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!dst)
	{
		perror("ERROR: Substr");
		exit(EXIT_FAILURE);
	}
	return (dst);
}
