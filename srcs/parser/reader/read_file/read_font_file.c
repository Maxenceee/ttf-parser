/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_font_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:46:34 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

unsigned char	*ft_read_font_file(int fd, unsigned char *file, uint32_t *rsize)
{
	unsigned char	*buff;
	int				read_bytes;
	uint32_t		size;

	size = 0;
	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(unsigned char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buff), NULL);
		buff[read_bytes] = '\0';
		file = ft_memjoin(file, buff, size, read_bytes);
		if (!file)
			return (free(buff), NULL);
		size += read_bytes;
	}
	*rsize = size;
	free(buff);
	return (file);
}
