/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_tell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:24:41 by mgama             #+#    #+#             */
/*   Updated: 2023/11/15 15:01:46 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

uint32_t	br_tell(t_binary_reader *this)
{
	return (this->_pos);
}