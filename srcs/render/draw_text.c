/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:25:21 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

int	get_next_char(uint8_t *character, const char *text, int *i)
{
	uint8_t		first_byte;
	uint8_t		second_byte;

	if (text[++(*i)])
	{
		first_byte = text[*i];
		if ((first_byte & 0xC0) == 0xC0)
		{
			second_byte = text[*i + 1];
			*character = ((first_byte & 0x1F) << 6) | (second_byte & 0x3F);
			(*i)++;
		}
		else
			*character = first_byte;
		return (1);
	}
	return (0);
}

int	draw_text(t_true_type_font *this, t_img *image,
	const char *text, t_glyph_ctx ctx)
{
	int				i;
	uint16_t		gindex;
	t_hor_metrics	metrics;
	t_pointi2		kern;
	t_pointi2		pos;
	uint8_t			character;

	pos.x = 0;
	pos.y = 0;
	ctx.scale_factor = (float)ctx.font_size / this->props.units_per_em;
	ctx.scale_ydelta = (this->props.ascent * ctx.scale_factor);
	reset_kerns(this);
	i = -1;
	while (get_next_char(&character, text, &i))
	{
		gindex = map_code(this, character);
		metrics = get_horizontal_metrics(this, gindex);
		kern = next_kern(this, gindex);
		ft_bzero(&ctx.pr, sizeof(t_glyph_ctx_p));
		ctx.pr.index = gindex;
		ctx.pr.image = image;
		ctx.glyph_width = metrics.advance_width;
		if (character != 32 && !(character >= 9 && character <= 13))
			if (draw_glyph(this, ctx,
				ft_create_ipoint(pos.x + kern.x, pos.y + kern.y)))
				return (FONT_ERROR);
		pos.x += metrics.advance_width;
	}
	return (FONT_NO_ERROR);
}
