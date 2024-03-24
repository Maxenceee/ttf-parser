/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glyph_points.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:59:23 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

int	push_glyph_point(t_glyph *glyph, t_glyph_point npoint)
{
	t_glyph_point	*tmp;
	t_glyph_point	*point;

	point = ft_calloc(1, sizeof(t_glyph_point));
	if (!point)
		return (FONT_ALLOC_ERROR);
	point->on_curve = npoint.on_curve;
	point->x = npoint.x;
	point->y = npoint.y;
	tmp = glyph->points;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		point->id = tmp->id + 1;
		tmp->next = point;
	}
	else
		glyph->points = point;
	return (FONT_NO_ERROR);
}

t_glyph_point	*get_glyph_point_by_id(t_glyph *glyph, uint32_t id)
{
	t_glyph_point	*tmp;

	tmp = glyph->points;
	while (tmp)
	{
		if (tmp->id == id)
			return (tmp);
		tmp = tmp->next;
	}
	return (glyph->points);
}
