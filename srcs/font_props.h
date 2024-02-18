/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_props.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:00:33 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 11:50:20 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_PROPS_H
# define FONT_PROPS_H

# include "utils/utils.h"
# include "pcolors.h"
# include "math/math.h"

typedef struct s_data			t_data;
typedef struct s_font			t_font;
typedef struct s_string			t_string;

# define FONT_NO_ERROR			0x000
# define FONT_ERROR				0x001
# define FONT_ALLOC_ERROR		0x002

# define FONT_ERROR_PREFIX		"Font error: "
# define FONT_ALLOC_ERROR_MSG	"Font error: Could not allocate memory.\n"

#endif /* FONT_PROPS_H */