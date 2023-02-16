/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 21:54:52 by mhassani          #+#    #+#             */
/*   Updated: 2023/02/15 13:44:33 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <sys/wait.h>

size_t	ft_strlen(const char *str);
char	*cmd_path(char **envp, char *av);
void	not_found(char **envp, char *av);
void	open_error(int file);
void	fork_error(int id);

#endif