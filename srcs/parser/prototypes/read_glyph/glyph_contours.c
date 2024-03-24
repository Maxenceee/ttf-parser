/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glyph_contours.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:07:29 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 19:33:18 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

int	push_glyph_contour(t_glyph *glyph, uint16_t ncontour)
{
	uint32_t		id;
	t_glyph_contour	*tmp;
	t_glyph_contour	*contour;

	contour = ft_calloc(1, sizeof(t_glyph_contour));
	if (!contour)
		return (FONT_ALLOC_ERROR);
	id = 0;
	contour->val = ncontour;
	tmp = glyph->contours;
	while (tmp)
	{
		id = tmp->id;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		contour->id = id + 1;
		tmp->next = contour;
	}
	else
		glyph->contours = contour;
	return (FONT_NO_ERROR);
}

t_glyph_contour	*get_glyph_contour_by_id(t_glyph *glyph, uint32_t id)
{
	t_glyph_contour	*tmp;

	tmp = glyph->contours;
	while (tmp)
	{
		if (tmp->id == id)
			return (tmp);
		tmp = tmp->next;
	}
	return (glyph->contours);
}

int16_t	get_glyph_contours_length(t_glyph *glyph)
{
	t_glyph_contour	*tmp;
	uint16_t		c;

	c = 0;
	tmp = glyph->contours;
	while (tmp)
	{
		c++;
		tmp = tmp->next;
	}
	return (c);
}

int16_t	get_glyph_last_contours(t_glyph *glyph)
{
	t_glyph_contour	*tmp;

	tmp = glyph->contours;
	while (tmp)
	{
		if (!tmp->next)
			return (tmp->val);
		tmp = tmp->next;
	}
	return (0);
}
