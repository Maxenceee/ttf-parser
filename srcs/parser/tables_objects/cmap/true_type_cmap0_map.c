/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_type_cmap0_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:20:11 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

uint8_t	true_type_cmap0_map(t_ttcmap0 *this, uint8_t char_code)
{
	return (this->glyph_indexes[char_code]);
}
