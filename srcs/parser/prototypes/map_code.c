/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_code.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:16:41 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:51:10 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

uint16_t	map_code(t_true_type_font *this, uint8_t char_code)
{
	t_linkedl_mask	*cmap;
	uint16_t		index;

	cmap = this->cmap;
	while (cmap)
	{
		if (cmap->format == 0)
			index = ((t_ttcmap0 *)cmap)->map((t_ttcmap0 *)cmap, char_code);
		else if (cmap->format == 4)
			index = ((t_ttcmap4 *)cmap)->map((t_ttcmap4 *)cmap, char_code);
		if (index)
			return (index);
		cmap = cmap->next;
	}
	return (0);
}
