/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:22:11 by mgama             #+#    #+#             */
/*   Updated: 2024/02/19 13:52:04 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "images/images.h"

void	*get_font_by_name(t_font font, const char *font_name)
{
	t_true_type_font	*l;

	l = font.ttfs;
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
 * @param mlx the mlx pointer
 * @param image the image pointer, if NULL, a new image will be created and returned
 * @param size the size of the text (in pixels)
 * @param width a pointer where the width of the image
 * will be written, accept NULL pointer
 * @param height a pointer where the height of the image
 * will be written, accept NULL pointer
 */
t_img	*ft_create_string(void *mlx, void *image, const char *text,
	uint32_t size, uint32_t color, const char *font_name, int *width, int *height)
{
	t_true_type_font	*ttf;
	t_glyph_ctx			ctx;

	ttf = get_font_by_name(g_font, font_name);
	if (!ttf)
		return (ft_error(FONT_ERROR_PREFIX"Invalid font name. No font loaded with name `"),
			ft_error((char *)font_name), ft_error("`.\n"), NULL);
	ft_bzero(&ctx, sizeof(t_glyph_ctx));
	ctx.width = get_text_width(ttf, text, size);
	if (width)
		*width = ctx.width;
	ctx.height = get_text_height(ttf, size);
	if (height)
		*height = ctx.height;
	ctx.font_size = size;
	ctx.color = color;
	if (!image)
		image = ft_new_image(mlx, ctx.width, ctx.height);
	if (!image)
		return (ft_error(FONT_ALLOC_ERROR_MSG), NULL);
	ft_draw_rect(ft_create_dims(0, 0, ctx.width, ctx.height), image, TRANSP_BYTE);
	if (draw_text(ttf, image, text, ctx))
		return (ft_delete_image(mlx, (t_img **)(&image)), NULL);
	return (image);
}
