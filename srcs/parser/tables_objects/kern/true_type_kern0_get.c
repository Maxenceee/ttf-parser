/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_type_kern0_get.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:39:50 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

t_pointi2	true_type_kern0_get(t_ttkern0 *kern, uint32_t glyph_index)
{
	int			i;
	int16_t		x;
	uint32_t	ch;

	x = 0;
	if (kern->old >= 0)
	{
		i = -1;
		ch = (kern->old << 16) | glyph_index;
		while (++i < kern->n_pairs)
		{
			if (kern->map[i].key == ch)
			{
				x = kern->map[ch].value;
				break ;
			}
		}
	}
	kern->old = glyph_index;
	if (kern->swap)
		return (ft_create_ipoint(0, x));
	return (ft_create_ipoint(x, 0));
}
