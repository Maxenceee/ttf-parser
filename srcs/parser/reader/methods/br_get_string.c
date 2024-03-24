/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:16:45 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

char	*br_get_string(t_binary_reader *this, uint16_t length)
{
	int		i;
	char	*res;

	res = malloc((length + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < length)
		res[i] = this->get_uint8(this);
	return (res);
}
