/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_render.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 12:59:22 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 13:25:17 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_RENDER_H
# define FONT_RENDER_H

typedef struct s_img	t_img;

typedef struct s_horizontal_metrics
{
	uint16_t		advance_width;
	int16_t			left_side_bearing;
}				t_hor_metrics;

typedef struct s_glyph_draw_context_props
{
	uint16_t	index;
	int			init;
	int			saved_x;
	int			saved_y;
	int			x;
	int			y;
	int			s;
	int			p;
	int			c;
	int			contour_s;
	t_img		*image;
}				t_glyph_ctx_p;

/**
 * @brief Drawing context, allows you to easily create paths
 * 
 */
typedef struct s_glyph_draw_context
{
	int				width;
	int				height;
	uint32_t		font_size;
	t_glyph_ctx_p	pr;
	float			scale_factor;
	int				scale_ydelta;
	uint32_t		color;
	t_pointi2		*points;
	uint16_t		pidx;
	int				glyph_width;
}				t_glyph_ctx;

// typedef struct s_intersections
// {
// 	int			t[WINDOW_WIDTH];
// 	uint16_t	count;
// 	uint16_t	y;
// }				t_intersections;

typedef struct s_metrics_params
{
	uint32_t		offset;
	uint16_t		glyph_index;
	uint16_t		*advance_width;
	int16_t			*left_side_bearing;
}				t_metrics_params;

t_string		create_t_string(const char *text, uint32_t size, uint32_t color, const char *font_name);

t_img			*ft_create_string(t_data *mlx, t_font *font, t_string string, int *width, int *height);

/* text */

int				draw_text(t_true_type_font *this, t_img *image, const char *text, t_glyph_ctx ctx);

/* kern */

void			reset_kerns(t_true_type_font *this);
t_pointi2		next_kern(t_true_type_font *this, uint16_t glyph_index);

/* metrics */

t_hor_metrics	get_horizontal_metrics(t_true_type_font *this, uint16_t glyph_index);

/* dims */

uint16_t		get_text_width(t_true_type_font *this, const char *text, uint32_t font_size);
uint16_t		get_text_height(t_true_type_font *this, uint32_t font_size);

/* drawing */

int				get_next_char(uint8_t *character, const char *text, int *i);
int				draw_glyph(t_true_type_font *this, t_glyph_ctx ctx, t_pointi2 pos);

/**
 * Glyph draw context
 */

void			pointc(t_glyph_ctx *ctx, int x, int y, int color);
void			move_to(t_glyph_ctx *ctx, int x, int y);
void			line_to(t_glyph_ctx *ctx, int x, int y);
void			quadratic_curve_to(t_glyph_ctx *ctx, t_pointi2 c, t_pointi2 e);

#endif /* FONT_RENDER_H */