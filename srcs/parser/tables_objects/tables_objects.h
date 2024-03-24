/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables_objects.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:45:06 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 19:47:48 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLES_OBJECTS_H
# define TABLES_OBJECTS_H

/**
 * 
 * Cmap
 * 
 */

typedef struct s_true_type_cmap4_cache		t_ttcmap4_cache;
typedef struct s_true_type_cmap4_segment	t_ttcmap4_segment;
typedef struct s_true_type_cmap0			t_ttcmap0;
typedef struct s_true_type_cmap4			t_ttcmap4;

struct s_true_type_cmap0
{
	t_ttcmap0			*next;
	uint32_t			format;
	t_binary_reader		*file;
	uint8_t				*glyph_indexes;
	uint8_t				((*map)(t_ttcmap0 *, uint8_t));
};

struct s_true_type_cmap4_segment
{
	uint32_t	id_range_offset;
	uint32_t	start_code;
	uint32_t	end_code;
	uint32_t	id_delta;
};

struct s_true_type_cmap4_cache
{
	t_ttcmap4_cache	*next;
	uint8_t			key;
	uint16_t		glyph_index;
};

struct s_true_type_cmap4
{
	t_ttcmap4			*next;
	uint32_t			format;
	t_binary_reader		*file;
	t_ttcmap4_cache		*caches;
	t_ttcmap4_segment	*segments;
	uint16_t			seg_count;
	uint16_t			((*map)(t_ttcmap4 *, uint8_t));
};

typedef struct s_ttcmap_sub_table
{
	uint16_t	platform_id;
	uint16_t	platform_specific_id;
	uint32_t	offset;
}				t_ttcmap_stable;

typedef struct s_linkedl_mask
{
	void		*next;
	uint32_t	format;
}		t_linkedl_mask;

/* true type cmap 0 */

t_ttcmap0	*new_ttcmap0(t_binary_reader *file);

/* true type cmap0 map method */

uint8_t		true_type_cmap0_map(t_ttcmap0 *this, uint8_t char_code);

/* true type cmap 0 */

t_ttcmap4	*new_ttcmap4(t_binary_reader *file);

/* true type cmap4 map method */

uint16_t	true_type_cmap4_map(t_ttcmap4 *this, uint8_t char_code);

/**
 * 
 * Kern
 * 
 */

typedef struct s_true_type_kern0			t_ttkern0;
typedef struct s_true_type_kern0_map		t_ttkern0_map;

struct s_true_type_kern0_map
{
	uint16_t	key;
	int16_t		value;
};

struct s_true_type_kern0
{
	t_ttkern0			*next;
	t_binary_reader		*file;
	uint32_t			offset;
	uint16_t			swap;
	uint16_t			n_pairs;
	t_ttkern0_map		*map;
	int32_t				old;
	void				(*reset)(t_ttkern0 *);
	t_pointi2			((*get)(t_ttkern0 *, uint32_t));
};

/* true type kern 0 */

t_ttkern0	*new_ttkern0(t_binary_reader *file,
				uint16_t vertical, uint16_t cross);

/* kern reset method */

void		true_type_kern0_reset(t_ttkern0 *kern);

/* kern get method */

t_pointi2	true_type_kern0_get(t_ttkern0 *kern, uint32_t glyph_index);

#endif /* TABLES_OBJECTS_H */