/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:17:54 by kmorulan          #+#    #+#             */
/*   Updated: 2019/07/04 07:23:30 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"
#include <fcntl.h>

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 1)
	{
		fd = 0;
	}
	else if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
	}
	else
	{
		return (2);
	}
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
		sleep(10);
	}
	if (argc == 2)
	{
		close(fd);
	}
}
