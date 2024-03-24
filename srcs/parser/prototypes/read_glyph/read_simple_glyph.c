/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_simple_glyph.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:42:56 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 19:33:18 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

uint16_t	list_max(t_glyph_contour *l)
{
	t_glyph_contour	*m;
	uint16_t		max;

	max = 0;
	m = l;
	while (m)
	{
		if (m->val > max)
			max = m->val;
		m = m->next;
	}
	return (max);
}

void	read_coord(t_true_type_font *this, t_glyph *glyph,
	char field, t_glyph_coord_flag cflags)
{
	int		i;
	int16_t	val;
	uint8_t	flag;

	i = -1;
	val = 0;
	while (++i < glyph->numpoints)
	{
		flag = glyph->flags[i];
		if (flag & cflags.byte_flag)
		{
			if (flag & cflags.delta_flag)
				val += this->file->get_uint8(this->file);
			else
				val -= this->file->get_uint8(this->file);
		}
		else if (~flag & cflags.delta_flag)
			val += this->file->get_int16(this->file);
		if (field == 'x')
			get_glyph_point_by_id(glyph, i)->x = val;
		else if (field == 'y')
			get_glyph_point_by_id(glyph, i)->y = val;
	}
}

void	read_simple_glyph_points(t_true_type_font *this, t_glyph *glyph)
{
	int				i;
	int				j;
	uint8_t			flag;
	uint8_t			repeat_count;
	t_glyph_point	point;

	i = -1;
	j = 0;
	while (++i < glyph->numpoints)
	{
		flag = this->file->get_uint8(this->file);
		glyph->flags[j] = flag;
		point.on_curve = (flag & ON_CURVE) > 0;
		push_glyph_point(glyph, point);
		if (flag & REPEAT)
		{
			repeat_count = this->file->get_uint8(this->file);
			i += repeat_count;
			while (repeat_count--)
			{
				glyph->flags[++j] = flag;
				point.on_curve = (flag & ON_CURVE) > 0;
				push_glyph_point(glyph, point);
			}
		}
		j++;
	}
}

int	read_simple_glyph(t_true_type_font *this, t_glyph *glyph)
{
	int			i;

	glyph->type = "simple";
	i = -1;
	while (++i < glyph->numcontours)
		if (push_glyph_contour(glyph, this->file->get_uint16(this->file)))
			return (FONT_ALLOC_ERROR);
	this->file->seek(this->file, this->file->get_uint16(this->file) + this->file->tell(this->file));
	if (glyph->numcontours == 0)
		return (FONT_NO_ERROR);
	glyph->numpoints = list_max(glyph->contours) + 1;
	glyph->flags = malloc(glyph->numpoints * sizeof(uint8_t));
	if (!glyph->flags)
		return (FONT_ALLOC_ERROR);
	read_simple_glyph_points(this, glyph);
	read_coord(this, glyph, 'x', (t_glyph_coord_flag){.byte_flag = X_IS_BYTE, .delta_flag = X_DELTA});
	read_coord(this, glyph, 'y', (t_glyph_coord_flag){.byte_flag = Y_IS_BYTE, .delta_flag = Y_DELTA});
	return (FONT_NO_ERROR);
}
