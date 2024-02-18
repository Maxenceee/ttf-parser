/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_points.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:02:37 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 11:56:32 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

t_pointf2	ft_create_fpoint(float x, float y)
{
	return ((t_pointf2){.x = x, .y = y});
}

t_pointi2	ft_dims_to_ipoint(t_screen_dim dims)
{
	return ((t_pointi2){.x = dims.left, .y = dims.top});
}

t_pointi2	ft_create_ipoint(int x, int y)
{
	return ((t_pointi2){.x = x, .y = y});
}
