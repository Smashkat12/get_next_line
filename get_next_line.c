/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorulan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 15:04:18 by kmorulan          #+#    #+#             */
/*   Updated: 2019/07/05 16:31:02 by kmorulan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

static t_list	*get_file_buf(size_t fd, t_list **start)
{
	t_list	*tmp;

	tmp = *start;
	while (tmp)
	{
		if (tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(start, tmp);
	return (tmp);
}

static size_t	ft_endl_pos(const char *s)
{
	char	*i;

	i = (char *)s;
	while (*i && *i != '\n')
		i++;
	return (i - s);
}

int				get_next_line(const int fd, char **line)
{
	char			line_b[BUFF_SIZE + 1];
	size_t			bytes_read;
	static t_list	*buffer_list;
	t_list			*file_b;

	CHECK_RETURN(fd < 0 || line == NULL || read(fd, line_b, 0) < 0, -1);
	file_b = get_file_buf(fd, &buffer_list);
	if (!file_b->content)
		file_b->content = ft_strnew(1);
	while ((bytes_read = read(fd, line_b, BUFF_SIZE)))
	{
		line_b[bytes_read] = 0;
		ft_swapnfree(&file_b->content, ft_strjoin(file_b->content, line_b));
		CHECK_RETURN(!file_b->content, -1);
		if (ft_strchr(file_b->content, '\n'))
			break ;
	}
	CHECK_RETURN(bytes_read < BUFF_SIZE && !*(char *)(file_b->content), 0);
	*line = ft_strndup(file_b->content, ft_endl_pos(file_b->content));
	if (ft_strlen(*line) < ft_strlen(file_b->content))
		ft_swapnfree(&file_b->content,
			ft_strdup(file_b->content + ft_strlen(*line) + 1));
	else
		ft_strdel((char **)&file_b->content);
	return (1);
}
