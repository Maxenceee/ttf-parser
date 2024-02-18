/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_int32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:36:55 by mgama             #+#    #+#             */
/*   Updated: 2023/11/15 15:04:19 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

int32_t	br_get_int32(t_binary_reader *this)
{
	return ((this->get_uint8(this) << 24)
		| (this->get_uint8(this) << 16)
		| (this->get_uint8(this) << 8)
		| (this->get_uint8(this)));
}
