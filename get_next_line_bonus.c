/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaryan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:49:20 by amaryan           #+#    #+#             */
/*   Updated: 2023/02/07 15:49:31 by amaryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_nx(char *str)
{
	int		i;
	char	*s;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	s = ft_substr(str, 0, i + 1);
	return (s);
}

char	*ft_nt(char *str)
{
	int		i;
	char	*s;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	s = ft_substr(str, i + 1, ft_strlen(str) - i + 1);
	free(str);
	str = ft_strdup(s);
	free(s);
	s = NULL;
	return (str);
}

char	*ft_rd(char *str, int fd)
{
	int		i;
	char	*ptr;
	char	buff[BUFFER_SIZE + 1];

	i = 1;
	if (!str)
		str = ft_strdup("");
	while (i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
		{
			free(str);
			return (NULL);
		}
		buff[i] = '\0';
		ptr = ft_strdup(str);
		free(str);
		str = ft_strjoin(ptr, buff);
		free(ptr);
		ptr = NULL;
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*ptr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = ft_rd(str[fd], fd);
	if (!str[fd])
	{
		return (NULL);
	}
	ptr = ft_nx(str[fd]);
	str[fd] = ft_nt(str[fd]);
	if (*ptr == 0)
	{
		free(str[fd]);
		str[fd] = NULL;
		free(ptr);
		ptr = NULL;
		return (NULL);
	}
	return (ptr);
}

// int main()
// {
// 	int fdf;
// 	char *s;
// 	fdf = open("fd.txt", O_RDONLY);
// 	s = get_next_line(fdf);
// 	printf("%s",s);
// 	free(s);
// 	s = get_next_line(7);
// 	printf("%s",s);
// 	free(s);
// 	system("leaks a.out");
// 	return (fdf);
// }