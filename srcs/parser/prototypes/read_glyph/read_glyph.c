/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_glyph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:33:26 by mgama             #+#    #+#             */
/*   Updated: 2023/11/21 18:12:14 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

t_glyph	*read_glyph(t_true_type_font *this, uint16_t index)
{
	t_glyph		*glyph;
	uint32_t	goffset;

	glyph = ft_calloc(1, sizeof(t_glyph));
	if (!glyph)
		return (NULL);
	goffset = get_glyph_offset(this, index);
	this->file->seek(this->file, goffset);
	glyph->number_of_contours = this->file->get_int16(this->file);
	glyph->x_min = this->file->get_fword(this->file);
	glyph->y_min = this->file->get_fword(this->file);
	glyph->x_max = this->file->get_fword(this->file);
	glyph->y_max = this->file->get_fword(this->file);
	if (glyph->number_of_contours == -1)
		read_compound_glyph(this, glyph);
	else
		read_simple_glyph(this, glyph);
	return (glyph);
}

void	destroy_glyph(t_glyph *glyph)
{
	t_glyph_point	*point;
	t_glyph_contour	*contour;
	void			*next;

	if (!glyph)
		return ;
	if (glyph->flags)
		free(glyph->flags);
	point = glyph->points;
	while (point)
	{
		next = point->next;
		free(point);
		point = next;
	}
	contour = glyph->contour_ends;
	while (contour)
	{
		next = contour->next;
		free(contour);
		contour = next;
	}
	free(glyph);
	glyph = NULL;
}
