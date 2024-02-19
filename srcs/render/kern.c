/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kern.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:28:17 by mgama             #+#    #+#             */
/*   Updated: 2024/02/19 14:00:05 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

void	reset_kerns(t_true_type_font *this)
{
	t_ttkern0	*kern;

	kern = this->kern;
	while (kern)
	{
		kern->reset(kern);
		kern = kern->next;
	}
}

t_pointi2	next_kern(t_true_type_font *this, uint16_t glyph_index)
{
	t_pointi2	pt;
	t_pointi2	fp;
	t_ttkern0	*kern;

	fp.x = 0;
	fp.y = 0;
	kern = this->kern;
	while (kern)
	{
		pt = kern->get(kern, glyph_index);
		fp.x += pt.x;
		fp.y += pt.y;
		kern = kern->next;
	}
	return (fp);
}
