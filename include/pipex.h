/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaypara <mbaypara@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:58:36 by mbaypara          #+#    #+#             */
/*   Updated: 2024/03/18 16:33:17 by mbaypara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../42libft/libft.h"
# include "unistd.h"
# include "fcntl.h"
# include "stdio.h"
# include <sys/wait.h>

void	exit_handler(int exitst);
char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
void	exec(char *cmd, char **env);
void	ft_free_tab(char **tab);
void	check(char **av);
char	**safe_split(char *s, char c);
char	*safe_strjoin(char *s1, char *s2);
int		safe_open(char *file, int flag);
char	*safe_substr(char const *s, unsigned int start, size_t len);

#endif
