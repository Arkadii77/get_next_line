/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaryan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:49:20 by amaryan           #+#    #+#             */
/*   Updated: 2023/02/07 15:49:31 by amaryan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_rd(char *str, char *buff, int fd)
{
	int		i;
	char	*ptr;

	i = 1;
	if (!str)
		str = ft_strdup("");
	while (i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
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
	static char	*str;
	char		*buff;
	char		*ptr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(buff) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	str = ft_rd(str, buff, fd);
	ptr = ft_nx(str);
	free(buff);
	buff = NULL;
	if (!str)
		return (NULL);
	str = ft_nt(str);
	if (*ptr == 0)
	{
		free(str);
		str = NULL;
		free(ptr);
		ptr = NULL;
		return (NULL);
	}
	return (ptr);
}

// int main()
// {
// 	int fdf;
// 	fdf = open("fd.txt", O_RDONLY);
// 	//get_next_line(fdf);
// 	printf("%s",get_next_line(fdf));
// 	printf("%s",get_next_line(fdf));
// 	printf("%s",get_next_line(fdf));
// 	printf("%s",get_next_line(fdf));
// 	printf("%s",get_next_line(fdf));
// 	printf("%s",get_next_line(fdf));
// 	return (fdf);
// }