/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_glyph.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:31:12 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 19:33:18 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_GLYPH_H
# define READ_GLYPH_H

typedef struct s_true_type_font	t_true_type_font;

typedef struct s_glyph_point	t_glyph_point;
typedef struct s_glyph_contour	t_glyph_contour;

typedef enum e_glyph_simple_flag
{
	ON_CURVE		= 0x001,
	X_IS_BYTE		= 0x002,
	Y_IS_BYTE		= 0x004,
	REPEAT			= 0x008,
	X_DELTA			= 0x010,
	Y_DELTA			= 0x020
}			t_glyph_simple_flag;

typedef enum e_glyph_compound_flag
{
	ARG_1_AND_2_ARE_WORDS		= 0x001,
	ARGS_ARE_XY_VALUES			= 0x002,
	ROUND_XY_TO_GRID			= 0x004,
	WE_HAVE_A_SCALE				= 0x008,
	MORE_COMPONENTS				= 0x020,
	WE_HAVE_AN_X_AND_Y_SCALE	= 0x040,
	WE_HAVE_A_TWO_BY_TWO		= 0x080,
	WE_HAVE_INSTRUCTIONS		= 0x100,
	USE_MY_METRICS				= 0x200,
	OVERLAP_COMPONENT			= 0x400
}			t_glyph_compound_flag;

typedef struct s_glyph_coord_flag
{
	uint8_t		byte_flag;
	uint8_t		delta_flag;
}				t_glyph_coord_flag;

struct s_glyph_point
{
	t_glyph_point	*next;
	uint32_t		id;
	int				on_curve;
	int16_t			x;
	int16_t			y;
};

struct s_glyph_contour
{
	t_glyph_contour	*next;
	uint32_t		id;
	uint16_t		val;
};

struct s_glyph_component_matrix
{
	int16_t		a;
	int16_t		b;
	int16_t		c;
	int16_t		d;
	int16_t		e;
	int16_t		f;
};

typedef struct s_glyph_component
{
	uint16_t						glyph_index;
	int16_t							dest_point_index;
	int16_t							src_point_index;
	struct s_glyph_component_matrix	matrix;
}				t_glyph_component;

typedef struct s_glyph
{
	int16_t			numcontours;
	uint16_t		numpoints;
	int16_t			x_min;
	int16_t			y_min;
	int16_t			x_max;
	int16_t			y_max;
	char			*type;
	t_glyph_contour	*contours;
	t_glyph_point	*points;
	uint8_t			*flags;
}				t_glyph;

typedef struct s_rdcompound_glyph
{
	uint16_t			flags;
	t_glyph_component	component;
	t_glyph_point		point;
	int16_t				arg1;
	int16_t				arg2;
	uint32_t			old;
	int16_t				x;
	int16_t				y;
}				t_rdcompound_glyph;

t_glyph			*read_glyph(t_true_type_font *this, uint16_t index);
int				read_compound_glyph(t_true_type_font *this, t_glyph *glyph);
int				read_simple_glyph(t_true_type_font *this, t_glyph *glyph);

int				push_glyph_point(t_glyph *glyph, t_glyph_point npoint);
t_glyph_point	*get_glyph_point_by_id(t_glyph *glyph, uint32_t id);

int				push_glyph_contour(t_glyph *glyph, uint16_t ncontour);
t_glyph_contour	*get_glyph_contour_by_id(t_glyph *glyph, uint32_t id);
int16_t			get_glyph_contours_length(t_glyph *glyph);
int16_t			get_glyph_last_contours(t_glyph *glyph);

uint16_t		glyph_count(t_true_type_font *this);

void			destroy_glyph(t_glyph *glyph);

#endif /* READ_GLYPH_H */