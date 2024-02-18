/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:10:47 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 13:30:25 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font_render.h"
#include "../math/math.h"

void	reflect(t_glyph_ctx *ctx, int *x, int *y)
{
	*x = *x * ctx->scale_factor;
	*y = ((ctx->height * ctx->scale_factor) - *y)
		* ctx->scale_factor + ctx->scale_ydelta - 5;
}

void	pointc(t_glyph_ctx *ctx, int x, int y, int color)
{
	reflect(ctx, &x, &y);
	ft_mlx_pixel_put(ctx->pr.image, x, y - 1, color);
	ft_mlx_pixel_put(ctx->pr.image, x - 1, y - 1, color);
	ft_mlx_pixel_put(ctx->pr.image, x + 1, y - 1, color);
	ft_mlx_pixel_put(ctx->pr.image, x, y, color);
	ft_mlx_pixel_put(ctx->pr.image, x - 1, y, color);
	ft_mlx_pixel_put(ctx->pr.image, x + 1, y, color);
	ft_mlx_pixel_put(ctx->pr.image, x, y + 1, color);
	ft_mlx_pixel_put(ctx->pr.image, x + 1, y + 1, color);
	ft_mlx_pixel_put(ctx->pr.image, x - 1, y + 1, color);
}

void	move_to(t_glyph_ctx *ctx, int x, int y)
{
	reflect(ctx, &x, &y);
	if (!ctx->pr.init)
	{
		ctx->pr.saved_x = x;
		ctx->pr.saved_y = y;
	}
	ctx->pr.x = x;
	ctx->pr.y = y;
	ctx->pidx++;
}

void	line_to(t_glyph_ctx *ctx, int x, int y)
{
	reflect(ctx, &x, &y);
	ft_draw_line(ctx->pr.image,
		ft_create_ipoint(ctx->pr.x, ctx->pr.y),
		ft_create_ipoint(x, y), ctx->color);
	ctx->pr.x = x;
	ctx->pr.y = y;
	ctx->pidx++;
}

void	quadratic_curve_to(t_glyph_ctx *ctx, t_pointi2 c, t_pointi2 e)
{
	t_bezier	b;

	reflect(ctx, &c.x, &c.y);
	reflect(ctx, &e.x, &e.y);
	b.start = ft_create_ipoint(ctx->pr.x, ctx->pr.y);
	b.control = c;
	b.end = e;
	b.steps = 150;
	if (ft_dist_btw_points(b.start, b.end) > 50.f)
		b.steps = 300;
	b.points = ctx->points;
	b.count = &ctx->pidx;
	ft_quadratic_bezier(ctx->pr.image, b, ctx->color);
	ctx->pr.x = e.x;
	ctx->pr.y = e.y;
	ctx->pidx++;
}
