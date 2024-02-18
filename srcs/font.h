/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:00:25 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 13:22:45 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include "font_props.h"
# include "parser/font_parser.h"
// # include "render/font_render.h"

struct s_string
{
	uint32_t	size;
	const char	*text;
	uint32_t	color;
	const char	*font_name;
};

struct s_font
{
	uint32_t			num_font;
	t_true_type_font	*ttfs;
};

/* create new ttf font */

int			ft_create_new_font(t_font *font, const char *type,
				char *path, const char *font_name);

/* destroy ttf font */

void		destroy_font(t_true_type_font *this);

/* freeing */

void		free_ttf_head(t_true_type_font *this);
void		free_ttf_kern(t_true_type_font *this);
void		free_ttf_cmap_caches(t_ttcmap4 *this);
void		free_ttf_cmap(t_true_type_font *this);
void		free_ttf_tables(t_true_type_font *this);

#endif /* FONT_H */
