/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _font.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:00:25 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:54:49 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FONT_H__
# define __FONT_H__

# include "utils/utils.h"
# include "pcolors.h"
# include "math/math.h"

// typedef struct s_data			t_data;
typedef struct s_font			t_font;

# define FONT_NO_ERROR			0x000
# define FONT_ERROR				0x001
# define FONT_ALLOC_ERROR		0x002

# define FONT_ERROR_PREFIX		"Font error: "
# define FONT_ALLOC_ERROR_MSG	"Font error: Could not allocate memory.\n"

# include "parser/font_parser.h"
# include "render/font_render.h"

struct s_font
{
	uint32_t			num_font;
	t_true_type_font	*ttfs;
};

extern struct s_font	g_font;

/* create new ttf font */

int					ft_create_new_font(const char *type, char *path, const char *font_name);
t_true_type_font	*get_font_by_name(t_font font, const char *font_name);

/* destroy ttf font */

void		destroy_font(t_true_type_font *this);

/* freeing */

void		free_ttf_head(t_true_type_font *this);
void		free_ttf_kern(t_true_type_font *this);
void		free_ttf_cmap_caches(t_ttcmap4 *this);
void		free_ttf_cmap(t_true_type_font *this);
void		free_ttf_tables(t_true_type_font *this);

#endif /* __FONT_H__ */
