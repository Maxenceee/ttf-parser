/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:09:41 by mgama             #+#    #+#             */
/*   Updated: 2024/02/19 13:20:29 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

struct s_font	g_font = {0, NULL};

int	ft_push_new_font(void	*ttf)
{
	t_true_type_font	*tmp;

	if (!ttf)
		return (FONT_ALLOC_ERROR);
	tmp = g_font.ttfs;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		tmp->next = ttf;
	else
		g_font.ttfs = ttf;
	g_font.num_font++;
	return (FONT_NO_ERROR);
}

/**
 * @brief Deletes a loaded font 
 * 
 * @param font_name the name of the font to be deleted
 */
int	ft_delete_font(const char *font_name)
{
	t_true_type_font	*tmp;

	if (!font_name)
		return (ft_error(FONT_ERROR_PREFIX"Font name cannot be NULL.\n"), FONT_ERROR);
	tmp = g_font.ttfs;
	while (tmp)
	{
		if (ft_strcmp(font_name, tmp->font_name) == 0)
		{
			destroy_font(tmp);
			g_font.num_font--;
			break ;
		}
		tmp = tmp->next;
	}
	return (FONT_NO_ERROR);
}

/**
 * @brief Loads a new font to be used later
 * 
 * @param type only accept `ttf` type for the moment
 * @param path path to the font file
 * @param font_name a name to identify the font
 */
int	ft_create_new_font(const char *type, char *path, const char *font_name)
{
	if (ft_strcmp("ttf", type) == 0)
	{
		if (!ft_extension(path, ".ttf"))
			return (ft_error(FONT_ERROR_PREFIX"Invalid font name.\n"), FONT_ERROR);
		if (ft_push_new_font(ft_create_ttf_font(path, font_name)))
			return (FONT_ERROR);
		return (FONT_NO_ERROR);
	}
	return (ft_error(FONT_ERROR_PREFIX"Invalid font type.\n"), FONT_ERROR);
}
