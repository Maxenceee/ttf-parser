/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 12:58:38 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 12:09:02 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_PARSER_H
# define FONT_PARSER_H

# include <stdint.h>
# include "reader/binary_reader.h"
# include "prototypes/read_glyph/read_glyph.h"
# include "tables_objects/tables_objects.h"

typedef struct s_true_type_font			t_true_type_font;
typedef struct s_true_type_font_props	t_true_type_font_props;

typedef struct s_ttf_table
{
	char		*tag;
	uint32_t	checksum;
	uint32_t	offset;
	uint32_t	length;
}				t_ttf_table;

struct s_true_type_font_props
{
	uint32_t	scalar_type;
	uint16_t	num_tables;
	uint16_t	search_range;
	uint16_t	entry_selector;
	uint16_t	range_shift;

	int32_t		version;
	int32_t		font_revision;
	uint32_t	checksum_adjustment;
	uint32_t	magic_number;
	uint16_t	flags;
	uint16_t	units_per_em;
	uint64_t	created;
	uint64_t	modified;
	int16_t		x_min;
	int16_t		y_min;
	int16_t		x_max;
	int16_t		y_max;
	uint16_t	mac_style;
	uint16_t	lowest_rec_ppem;
	int16_t		font_direction_hint;
	int16_t		index_to_loc_format;
	int16_t		glyph_data_format;

	int16_t		ascent;
	int16_t		descent;
	int16_t		line_gap;
	uint16_t	advance_width_max;
	int16_t		min_left_side_bearing;
	int16_t		min_right_side_bearing;
	int16_t		x_max_extent;
	int16_t		caret_slope_rise;
	int16_t		caret_slope_run;
	int16_t		caret_offset;
	int16_t		metric_data_format;
	uint16_t	num_of_long_hor_metrics;

	uint16_t	format;
	char		*font_family;
	char		*font_sub_family;
	char		*full_name;
	char		*postscript_name;
};

struct s_true_type_font
{
	t_true_type_font			*next;
	const char					*font_name;
	t_ttf_table					*tables;
	void						*cmap;
	void						*kern;
	uint16_t					length;
	t_binary_reader				*file;
	t_true_type_font_props		props;
};

/* create new ttf font */

t_true_type_font	*ft_create_ttf_font(char *path, const char *font_name);

/* get table offset */

uint32_t			get_table_offset(t_true_type_font *this, const char *table);

/* get map code */

uint16_t			map_code(t_true_type_font *this, uint8_t char_code);

/* glyph offset in table */

uint32_t			get_glyph_offset(t_true_type_font *this, uint16_t index);

/**
 * 
 * Read Tables
 * 
 */

/* read ttf tables offsets */

int					read_offset_tables(t_true_type_font *this,
						t_binary_reader *file);

/* read head table */

int					read_head_table(t_true_type_font *this,
						t_binary_reader *file, uint32_t offset);

/* read name table */

int					read_name_table(t_true_type_font *this,
						t_binary_reader *file, uint32_t offset);

/* read cmap table */

int					read_cmap_table(t_true_type_font *this,
						t_binary_reader *file, uint32_t offset);

/* read hhea table */

int					read_hhea_table(t_true_type_font *this,
						t_binary_reader *file, uint32_t offset);

/* read kern table */

int					read_kern_table(t_true_type_font *this,
						t_binary_reader *file, uint32_t offset);

#endif /* FONT_PARSER_H */