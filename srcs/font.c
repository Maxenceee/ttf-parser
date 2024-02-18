/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:09:41 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 13:22:48 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

int	ft_push_new_font(t_font *font, void	*ttf)
{
	t_true_type_font	*tmp;

	if (!ttf)
		return (FONT_ALLOC_ERROR);
	tmp = font->ttfs;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		tmp->next = ttf;
	else
		font->ttfs = ttf;
	font->num_font++;
	return (FONT_NO_ERROR);
}

/**
 * @brief Loads a new font to be used in the game
 * 
 * @param font font struct to store the font data
 * @param type only accept ttf type for the moment
 * @param path path to the font file
 * @param font_name a name to identify the font
 */
int	ft_create_new_font(t_font *font, const char *type,
	char *path, const char *font_name)
{
	if (ft_strcmp("ttf", type) == 0)
	{
		if (!ft_extension(path, ".ttf"))
			return (ft_error(FONT_ERROR_PREFIX"Invalid font name.\n"), FONT_ERROR);
		if (ft_push_new_font(font, ft_create_ttf_font(path, font_name)))
			return (FONT_ERROR);
		return (FONT_NO_ERROR);
	}
	return (ft_error(FONT_ERROR_PREFIX"Invalid font type.\n"), FONT_ERROR);
}
