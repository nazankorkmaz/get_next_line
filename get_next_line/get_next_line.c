/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:07:59 by nkorkmaz          #+#    #+#             */
/*   Updated: 2023/02/05 21:13:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	line = malloc(sizeof(char) * i + 1 + new_line);
	if (!line)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';  //line son durumda string \0 \n olur fd stringin bittiğini anlar ve alt satıra geçer. \n konulmazsa her şeyi yan yana yazdırır
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
	new_line = malloc(sizeof(char) * (j - i) + 1); //yeni stringi almak için 
	if (!new_line)
		return (0);
	j = 0;
	i++;
	while (str[i] != '\0')
		new_line[j++] = str[i++];
	new_line[j] = '\0';
	free(str);  //burda eski stringi freelediğimiz için sonradan yeni atama yapabiliyoruz
	return (new_line);
}

char	*ft_get_read(int fd, char *str)
{
	int		count;
	char	*now_str;

	now_str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!now_str)
		return (0);
	count = 1;   //count 1'den başlatılır çünkü dosya var ama boşsa hataya girer.Bunu eklemezsek
	while (!ft_strchr(str, '\n') && count != 0)
	{
		count = read(fd, now_str, BUFFER_SIZE);
		if (count == -1)
		{
			free(now_str);
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
	static char	*str;
	char		*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
	{
		return (0);
	}
	str = ft_get_read(fd, str);
	if (!str)
		return (0);
	line = ft_get_line(str);
	str = ft_get_new_str(str);
	return (line);
}



//#include<stdio.h>
//#include<fcntl.h>

//tek satır yazdıralım
/*
int main()
{
	int fd=open("a.txt",O_RDONLY);
	char *a=get_next_line(fd);
	printf("%s",a);
	free(a);
	system("leaks a.out");
}
*/

//tüm satırları yazdıralım
/*
int main()
{
	int fd= open("a.txt",O_RDONLY);
	char *a=get_next_line(fd);
	while(a)
	{
		printf("%s",a);
		free(a);
		a=get_next_line(fd);
	}
	free(a);
	//system("leaks a.out");
}
*/

//ilk üç satırı yazdıran main 
/*
int main()
{
	int fd=open("a.txt",O_RDONLY);
	char *a=get_next_line(fd);
	char *b=get_next_line(fd);
	char *c=get_next_line(fd);
	printf("%s",a);
	printf("%s",b);
	printf("%s",c);
	free(a);
	free(b);
	free(c);
}
*/

//yalnızca 5.satırı yazdıralım
/*
int main()
{
	int fd=open("a.txt",O_RDONLY);
	char *a=get_next_line(fd);
	int count=1;
	while(a)
	{
		if(count==5){
			printf("%s",a);
		}
		free(a);
		a=get_next_line(fd);
		count++;
	}
	system("leaks a.out");
}
*/