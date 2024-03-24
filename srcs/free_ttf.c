/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ttf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:06:21 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 19:55:36 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

void	free_ttf_head(t_true_type_font *this)
{
	if (this->family.font_family)
		free(this->family.font_family);
	if (this->family.font_sub_family)
		free(this->family.font_sub_family);
	if (this->family.full_name)
		free(this->family.full_name);
	if (this->family.postscript_name)
		free(this->family.postscript_name);
}

void	free_ttf_kern(t_true_type_font *this)
{
	(void)this;
}

void	free_ttf_cmap_caches(t_ttcmap4 *this)
{
	t_ttcmap4_cache		*cache;
	t_ttcmap4_cache		*tmp;

	cache = this->caches;
	while (cache)
	{
		tmp = cache->next;
		free(cache);
		cache = tmp;
	}
}

void	free_ttf_cmap(t_true_type_font *this)
{
	t_linkedl_mask		*cmap;
	t_linkedl_mask		*tmp;
	t_ttcmap4			*cmap4;

	cmap = this->cmap;
	while (cmap)
	{
		tmp = cmap->next;
		if (cmap->format == 0)
		{
			if (((t_ttcmap0 *)cmap)->glyph_indexes)
				free(((t_ttcmap0 *)cmap)->glyph_indexes);
		}
		else if (cmap->format == 4)
		{
			cmap4 = ((t_ttcmap4 *)cmap);
			if (cmap4->segments)
				free(cmap4->segments);
			if (cmap4->caches)
				free_ttf_cmap_caches(cmap4);
		}
		free(cmap);
		cmap = tmp;
	}
}

void	free_ttf_tables(t_true_type_font *this)
{
	int	i;

	i = -1;
	while (++i < this->props.num_tables)
	{
		if (this->tables[i].tag)
			free(this->tables[i].tag);
	}
	free(this->tables);
}
