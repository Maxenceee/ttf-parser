/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:55:48 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 11:35:30 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

float	ft_dist_btw_pointsf(t_pointf2 p1, t_pointf2 p2)
{
	return (sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)));
}

float	ft_dist_btw_points(t_pointi2 p1, t_pointi2 p2)
{
	return (sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)));
}
