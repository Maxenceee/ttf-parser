/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fontapi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:27:28 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 20:03:00 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

struct s_true_type_font	*get_font(const char *name)
{
	return (get_font_by_name(g_font, name));
}

inline struct s_glyph	*get_glyph(const char *name, char c)
{
	t_true_type_font	*font = get_font_by_name(g_font, name);

	if (!font)
		return (NULL);
	return (read_glyph(font, map_code(font, c)));
}

struct s_true_type_font_family *get_font_family(const char *name)
{
	t_true_type_font	*font = get_font_by_name(g_font, name);

	if (!font)
		return (NULL);
	return (&font->family);
}

struct s_true_type_font_props *get_font_props(const char *name)
{
	t_true_type_font	*font = get_font_by_name(g_font, name);

	if (!font)
		return (NULL);
	return (&font->props);
}

struct s_true_type_font_family *font_family(void *font)
{
	return (&((t_true_type_font *)font)->family);
}

struct s_true_type_font_props *font_props(void *font)
{
	return (&((t_true_type_font *)font)->props);
}