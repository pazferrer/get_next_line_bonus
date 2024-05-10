/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pferrer- <pferrer-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:29:44 by pferrer-          #+#    #+#             */
/*   Updated: 2024/05/07 20:30:14 by pferrer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*save_lecture(int fd, char *reading)
{
	char	*lecture;
	char	*tmp;
	int		i;
	int		z;

	i = 0;
	z = 0;
	lecture = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (lecture == NULL)
	{
		free(reading);
		return (NULL);
	}
	lecture[0] = '\0';
	while (newline_search(lecture) == 0)
	{
		z = read(fd, lecture, BUFFER_SIZE);
		if (z == -1)
		{
			free(lecture);
			free(reading);
			return (NULL);
		}
		if (z == 0)
		{
			free(lecture);
			return (reading);
		}
		lecture[z] = '\0';
		tmp = join_string(reading, lecture);
		if (tmp == NULL)
		{
			free(lecture);
			return (NULL);
		}
		free(reading);
		reading = tmp;
	}
	free(lecture);
	return (reading);
}

char	*save_line(char *lecture)
{
	int		i;
	char	*line;

	i = 0;
	while (lecture[i] && lecture[i] != '\n')
		i++;
	if (lecture[i] == '\n')
		i = i + 1;
	line = malloc((i + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	line[i--] = '\0';
	while (i >= 0)
	{
		line[i] = lecture[i];
		i--;
	}
	return (line);
}

char	*save_line2(char *lecture, char *line)
{
	int		i;
	int		z;
	char	*line2;

	i = 0;
	while (line[i] == lecture[i] && line[i])
		i++;
	if (lecture[i] == '\0')
		return (NULL);
	z = i;
	while (lecture[z])
		z++;
	line2 = malloc((z - i + 1) * sizeof(char));
	if (line2 == NULL)
	{
		line = NULL;
		lecture = NULL;
		return (NULL);
	}
	z = 0;
	while (lecture[i])
		line2[z++] = lecture[i++];;
	line2[z] = '\0';
	return (line2);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*lecture;
	static char	*line2;

	if (fd == -1)
		return (NULL);
	lecture = save_lecture(fd, line2);
	if (lecture == NULL)
	{
		line2 = NULL;
		return (NULL);
	}
	line = save_line(lecture);
	if (line == NULL)
	{
		free(lecture);
		line2 = NULL;
		return (NULL);
	}
	line2 = save_line2(lecture, line);
	if (line2 == NULL && line == NULL && lecture == NULL)
	{
		free(line);
		free(lecture);
		return (NULL);
	}
	free(lecture);
	return (line);
}

/*
int main() 
{
	int		fd;
	char	*lecture;
	char	*line;
	char	*line2;
	char	*getnextline;

//	fd = open("archivo.txt", O_RDONLY);
	fd = open("test", O_RDONLY);
	printf("ARCHIVO fd: %d\n", fd);

  	//line2 = NULL;
    //lecture = save_lecture(fd, line2);

	//line = save_line(lecture);

	//line2 = save_line2(lecture, line);

	getnextline = get_next_line(fd);

	//printf("Lectura: %s\n", lecture);
	//printf("linea: %s\n", line);
	//printf("linea2: %s\n", line2);
	printf("get_next_line es: %s\n", getnextline);
	
	getnextline  = get_next_line(fd);
	printf("get_next_line es: %s\n", getnextline);
    //free(lecture);
	//free(line2);
   //free(line);	// Liberar la memoria asignada

    return 0;
 
}
*/
