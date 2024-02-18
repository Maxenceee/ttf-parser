/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:22:11 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 13:25:04 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "images.h"

t_string	create_t_string(const char *text, uint32_t size, uint32_t color, const char *font_name)
{
	return ((t_string){.text = text, .size = size,
		.color = color, .font_name = font_name});
}

void	*get_font_by_name(t_font *font, const char *font_name)
{
	t_true_type_font	*l;

	l = font->ttfs;
	while (l)
	{
		if (ft_strcmp(font_name, l->font_name) == 0)
			return (l);
		l = l->next;
	}
	return (NULL);
}

/**
 * @brief Creates a t_img with the text passed in `string` drawn in it
 *  
 * @param width a pointer where the width of the image
 * will be written, accept NULL pointer
 * @param height a pointer where the height of the image
 * will be written, accept NULL pointer
 */
t_img	*ft_create_string(t_data *mlx, t_font *font, t_string string, int *width, int *height)
{
	t_true_type_font	*ttf;
	t_img				*ttf_image;
	t_glyph_ctx			ctx;

	ttf = get_font_by_name(font, string.font_name);
	if (!ttf)
		return (ft_error(FONT_ERROR_PREFIX"Invalid font name. No font loaded with name `"),
			ft_error((char *)string.font_name), ft_error("`.\n"), NULL);
	ft_bzero(&ctx, sizeof(t_glyph_ctx));
	ctx.width = get_text_width(ttf, string.text, string.size);
	if (width)
		*width = ctx.width;
	ctx.height = get_text_height(ttf, string.size);
	if (height)
		*height = ctx.height;
	ctx.font_size = string.size;
	ctx.color = string.color;
	ttf_image = ft_new_image(mlx->mlx, ctx.width, ctx.height);
	if (!ttf_image)
		return (ft_error(FONT_ALLOC_ERROR_MSG), NULL);
	ft_draw_rect(ft_create_dims(0, 0, ctx.width, ctx.height), ttf_image, TRANSP_BYTE);
	if (draw_text(ttf, ttf_image, string.text, ctx))
		return (ft_delete_image(mlx->mlx, &ttf_image), NULL);
	return (ttf_image);
}
