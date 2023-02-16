/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:23:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/02/15 13:34:34 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "pipex.h"

void	not_found(char **envp, char *av)
{
	if (!cmd_path(envp, av))
	{
		write(2, "command not found: ", 19);
		write(2, av, ft_strlen(av));
		write(2, "\n", 1);
		exit(EXIT_FAILURE);
	}
}

void	open_error(int file)
{
	if (file == -1)
	{
		write(2, "error with open() function\n", 27);
		exit(EXIT_FAILURE);
	}
}

void	fork_error(int id)
{
	if (id == -1)
	{
		perror("Error occured with fork() function");
		exit(EXIT_FAILURE);
	}
}
