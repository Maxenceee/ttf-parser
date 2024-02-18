/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_dims.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 22:42:36 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 13:29:52 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font_render.h"

uint16_t	get_text_width(t_true_type_font *this,
	const char *text, uint32_t font_size)
{
	int			i;
	uint8_t		character;
	uint16_t	index;
	uint16_t	totalwidth;

	i = -1;
	totalwidth = 0;
	while (get_next_char(&character, text, &i))
	{
		index = map_code(this, character);
		totalwidth += get_horizontal_metrics(this, index).advance_width;
	}
	return ((totalwidth * ((float)font_size / this->props.units_per_em)) + 5);
}

uint16_t	get_text_height(t_true_type_font *this, uint32_t font_size)
{
	uint16_t	totalheight;

	totalheight = this->props.ascent - this->props.descent;
	return (totalheight * ((float)font_size / this->props.units_per_em));
}
