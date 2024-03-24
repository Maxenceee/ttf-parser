/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_compound_glyph.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:40:19 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 19:32:53 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

static void	read_compound_glyph_flags_scale(t_true_type_font *this,
	t_rdcompound_glyph *cg)
{
	if (cg->flags & WE_HAVE_A_SCALE)
	{
		cg->component.matrix.a = this->file->get_2dot14(this->file);
		cg->component.matrix.d = cg->component.matrix.a;
	}
	else if (cg->flags & WE_HAVE_AN_X_AND_Y_SCALE)
	{
		cg->component.matrix.a = this->file->get_2dot14(this->file);
		cg->component.matrix.d = this->file->get_2dot14(this->file);
	}
	else if (cg->flags & WE_HAVE_A_TWO_BY_TWO)
	{
		cg->component.matrix.a = this->file->get_2dot14(this->file);
		cg->component.matrix.b = this->file->get_2dot14(this->file);
		cg->component.matrix.c = this->file->get_2dot14(this->file);
		cg->component.matrix.d = this->file->get_2dot14(this->file);
	}
}

static void	read_compound_glyph_flags(t_true_type_font *this,
	t_rdcompound_glyph *cg)
{
	if (cg->flags & ARG_1_AND_2_ARE_WORDS)
	{
		cg->arg1 = this->file->get_int16(this->file);
		cg->arg2 = this->file->get_int16(this->file);
	}
	else
	{
		cg->arg1 = this->file->get_uint8(this->file);
		cg->arg2 = this->file->get_uint8(this->file);
	}
	if (cg->flags & ARGS_ARE_XY_VALUES)
	{
		cg->component.matrix.e = cg->arg1;
		cg->component.matrix.f = cg->arg2;
	}
	else
	{
		cg->component.dest_point_index = cg->arg1;
		cg->component.src_point_index = cg->arg2;
	}
	read_compound_glyph_flags_scale(this, cg);
}

static void	read_compound_glyph_push_simple(t_glyph *glyph,
	t_rdcompound_glyph *cg, t_glyph *simple_glyph)
{
	int	i;

	i = -1;
	while (++i < simple_glyph->numcontours)
		push_glyph_contour(glyph, get_glyph_contour_by_id(
				simple_glyph, i)->val + glyph->numpoints);
	i = -1;
	while (++i < simple_glyph->numpoints)
	{
		cg->x = get_glyph_point_by_id(simple_glyph, i)->x;
		cg->y = get_glyph_point_by_id(simple_glyph, i)->y;
		cg->x = cg->component.matrix.a * cg->x + cg->component.matrix.b
			* cg->y + cg->component.matrix.e;
		cg->y = cg->component.matrix.c * cg->x + cg->component.matrix.d
			* cg->y + cg->component.matrix.f;
		cg->point.x = cg->x;
		cg->point.y = cg->y;
		cg->point.on_curve = get_glyph_point_by_id(
				simple_glyph, i)->on_curve;
		push_glyph_point(glyph, cg->point);
		glyph->numpoints++;
	}
	destroy_glyph(simple_glyph);
}

int	read_compound_glyph(t_true_type_font *this, t_glyph *glyph)
{
	t_glyph				*simple_glyph;
	t_rdcompound_glyph	cg;

	glyph->type = "compound";
	cg.flags = MORE_COMPONENTS;
	while (cg.flags & MORE_COMPONENTS)
	{
		cg.flags = this->file->get_uint16(this->file);
		ft_bzero(&cg.component, sizeof(t_glyph_component));
		cg.component.matrix.a = 1;
		cg.component.matrix.d = 1;
		cg.component.glyph_index = this->file->get_uint16(this->file);
		read_compound_glyph_flags(this, &cg);
		cg.old = this->file->tell(this->file);
		simple_glyph = read_glyph(this, cg.component.glyph_index);
		if (simple_glyph)
			read_compound_glyph_push_simple(glyph, &cg, simple_glyph);
		this->file->seek(this->file, cg.old);
	}
	glyph->numcontours = get_glyph_contours_length(glyph);
	if (cg.flags & WE_HAVE_INSTRUCTIONS)
		this->file->seek(this->file,
			this->file->get_uint16(this->file) + this->file->tell(this->file));
	return (FONT_NO_ERROR);
}
