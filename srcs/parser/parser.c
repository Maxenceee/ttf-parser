/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:10:58 by mgama             #+#    #+#             */
/*   Updated: 2024/01/12 17:02:45 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

uint32_t	get_table_offset(t_true_type_font *this, const char *table)
{
	int	i;

	i = -1;
	while (++i < this->props.num_tables)
	{
		if (ft_strcmp(table, this->tables[i].tag) == 0)
			return (this->tables[i].offset);
	}
	return (0);
}

static int	read_ttf_tables(t_true_type_font *ttf)
{
	if (read_offset_tables(ttf, ttf->file))
		return (FONT_ALLOC_ERROR);
	if (read_head_table(ttf, ttf->file, get_table_offset(ttf, "head")))
		return (FONT_ALLOC_ERROR);
	if (read_cmap_table(ttf, ttf->file, get_table_offset(ttf, "cmap")))
		return (FONT_ALLOC_ERROR);
	if (read_hhea_table(ttf, ttf->file, get_table_offset(ttf, "hhea")))
		return (FONT_ALLOC_ERROR);
	if (read_kern_table(ttf, ttf->file, get_table_offset(ttf, "kern")))
		return (FONT_ALLOC_ERROR);
	return (FONT_NO_ERROR);
}

t_true_type_font	*ft_create_ttf_font(char *path, const char *font_name)
{
	int					fd;
	t_true_type_font	*ttf;

	ttf = (t_true_type_font *)ft_calloc(1, sizeof(t_true_type_font));
	if (!ttf)
		return (ft_error(FONT_ALLOC_ERROR_MSG), NULL);
	ttf->font_name = font_name;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error(FONT_ERROR_PREFIX"Invalid font path.\n"),
			free(ttf), NULL);
	ttf->file = new_binary_reader(fd);
	close(fd);
	if (!ttf->file)
		return (free(ttf), NULL);
	if (read_ttf_tables(ttf))
		return (destroy_font(ttf), NULL);
	ttf->length = glyph_count(ttf);
	return (ttf);
}
