/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_font.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:56:03 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

void	destroy_font(t_true_type_font *this)
{
	if (!this)
		return ;
	if (this->file)
		delete_binary_reader(this->file);
	free_ttf_tables(this);
	free_ttf_head(this);
	free_ttf_cmap(this);
	free_ttf_kern(this);
	free(this);
	this = NULL;
}
