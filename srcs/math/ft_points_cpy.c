/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_points_cpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:38:49 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 11:35:30 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

t_pointi2	*ft_copy_ipoint(t_pointi2 point)
{
	t_pointi2	*spoint;

	spoint = (t_pointi2 *)ft_calloc(1, sizeof(t_pointi2));
	if (!spoint)
		return (NULL);
	spoint->x = point.x;
	spoint->y = point.y;
	return (spoint);
}

t_pointf2	*ft_copy_fpoint(t_pointf2 point)
{
	t_pointf2	*spoint;

	spoint = (t_pointf2 *)ft_calloc(1, sizeof(t_pointf2));
	if (!spoint)
		return (NULL);
	spoint->x = point.x;
	spoint->y = point.y;
	return (spoint);
}
