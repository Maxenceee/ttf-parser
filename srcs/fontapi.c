/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fontapi.C                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:27:28 by mgama             #+#    #+#             */
/*   Updated: 2024/02/19 16:46:07 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

t_true_type_font	*get_font(const char *name)
{
	return (get_font_by_name(g_font, name));
}

t_glyph	*get_glyph(const char *name, char c)
{
	t_true_type_font	*font = get_font_by_name(g_font, name);

	if (!font)
		return (NULL);
	return (read_glyph(font, map_code(font, c)));
}