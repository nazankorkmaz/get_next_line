/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:06:58 by nkorkmaz          #+#    #+#             */
/*   Updated: 2023/02/05 21:07:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;
	int		new_line;

	i = 0;
	new_line = ft_strchr(str, '\n');
	if (!str[i])
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1 + new_line);
	if (!line)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_get_new_str(char *str)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = ft_strlen(str);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (0);
	}
	new_line = (char *)malloc(sizeof(char) * (j - i) + 1);
	if (!new_line)
		return (0);
	j = 0;
	i++;
	while (str[i] != '\0')
		new_line[j++] = str[i++];
	new_line[j] = '\0';
	free(str);
	return (new_line);
}

char	*ft_get_read(int fd, char *str)
{
	int		count;
	char	*now_str;

	now_str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!now_str)
		return (0);
	count = 1;
	while (! ft_strchr(str, '\n') && count != 0)
	{
		count = read(fd, now_str, BUFFER_SIZE);
		if (count == -1)
		{
			free (now_str);
			return (0);
		}
		now_str[count] = '\0';
		str = ft_strjoin(str, now_str);
	}
	free(now_str);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[256]; //linuxde max 256 dosya açılır genel olarak ama bu sayı değişe de bilir.
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = ft_get_read(fd, str[fd]);
	if (!str[fd])
		return (0);
	line = ft_get_line(str[fd]);
	str[fd] = ft_get_new_str(str[fd]);
	return (line);
}

#include <stdio.h>
#include <fcntl.h>
//iki dosyanın da hepsini yazdıralım
/*
int	main(void)
{
	int	fd1 = open("a.txt", O_RDONLY);
	int	fd2 = open("b.txt", O_RDONLY);
	char	*a = get_next_line(fd1);

	while (a)
	{
		printf("%s", a);
		free(a);
		a = get_next_line(fd1);
		
	}
	free(a);
	char	*b = get_next_line(fd2);
	while (b)
	{
		printf("%s", b);
		free(b);
		b = get_next_line(fd2);
	}
	free(b);
	system("leaks a.out");
}
*/

//ikisinden de birer satır yazdıralım
/*
int	main(void)
{
	int	fd1 = open("a.txt", O_RDONLY);
	int	fd2 = open("b.txt", O_RDONLY);

	char	*a;
	char	*b;
	a = get_next_line(fd1);
	b = get_next_line(fd2);
	while (a && b)
	{
		printf("%s%s", a, b);
		free(a);
		free(b);
		a = get_next_line(fd1);
		b = get_next_line(fd2);
	}
	free(a);
	free(b);
	system("leaks a.out");
}
*/

//file descriptorler 3den başlar 
//file oluşturulamazsa fd -1 döner
/*
int	main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;

	fd1 = open("a.txt", O_RDONLY);
	fd2 = open("b.txt", O_RDONLY);
	fd3 = open("c.txt", O_RDONLY);
	printf("%d\n%d\n%d", fd1, fd2, fd3);
}
*/

//dosya açar yazar ve okur.
/*
int	main(void)
{
	int fd1 = open("ax.txt", O_CREAT|O_RDWR, 0777);
	int fd2 = open("bx.txt", O_CREAT|O_RDWR, 0777);

	write(fd1, "11111xx\naaaaaaaaa\n444444", 32);
	write(fd2, "22222xx\nbbbbbbb\n5555555", 32);

	close(fd1);
	close(fd2);	

	fd1 = open("ax.txt", O_CREAT|O_RDWR, 0777);
	fd2 = open("bx.txt", O_CREAT|O_RDWR, 0777);

	printf("%d\n", fd1);
	printf("%d\n", fd2);

	printf("%s",get_next_line(fd1));
	printf("%s",get_next_line(fd2));
	
	close(fd1);
	close(fd2);
}
*/