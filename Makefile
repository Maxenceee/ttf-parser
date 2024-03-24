MANDATORY_DIR	=	srcs
OBJ_DIR			=	.objs

# fonts
SRCS			=	$(MANDATORY_DIR)/free_ttf.c \
					$(MANDATORY_DIR)/font.c \
					$(MANDATORY_DIR)/fontapi.c \
					$(MANDATORY_DIR)/parser/tables_objects/cmap/true_type_cmap0_map.c \
					$(MANDATORY_DIR)/parser/tables_objects/cmap/true_type_cmap4.c \
					$(MANDATORY_DIR)/parser/tables_objects/cmap/true_type_cmap0.c \
					$(MANDATORY_DIR)/parser/tables_objects/cmap/true_type_cmap4_map.c \
					$(MANDATORY_DIR)/parser/tables_objects/kern/true_type_kern0.c \
					$(MANDATORY_DIR)/parser/tables_objects/kern/true_type_kern0_get.c \
					$(MANDATORY_DIR)/parser/tables_objects/kern/true_type_kern0_reset.c \
					$(MANDATORY_DIR)/parser/prototypes/read_name_table.c \
					$(MANDATORY_DIR)/parser/prototypes/read_offset_tables.c \
					$(MANDATORY_DIR)/parser/prototypes/get_glyph_offset.c \
					$(MANDATORY_DIR)/parser/prototypes/read_glyph/glyph_contours.c \
					$(MANDATORY_DIR)/parser/prototypes/read_glyph/read_glyph.c \
					$(MANDATORY_DIR)/parser/prototypes/read_glyph/glyph_count.c \
					$(MANDATORY_DIR)/parser/prototypes/read_glyph/glyph_points.c \
					$(MANDATORY_DIR)/parser/prototypes/read_glyph/read_simple_glyph.c \
					$(MANDATORY_DIR)/parser/prototypes/read_glyph/read_compound_glyph.c \
					$(MANDATORY_DIR)/parser/prototypes/map_code.c \
					$(MANDATORY_DIR)/parser/prototypes/read_cmap_table.c \
					$(MANDATORY_DIR)/parser/prototypes/read_kern_table.c \
					$(MANDATORY_DIR)/parser/prototypes/read_hhea_table.c \
					$(MANDATORY_DIR)/parser/prototypes/read_head_table.c \
					$(MANDATORY_DIR)/parser/parser.c \
					$(MANDATORY_DIR)/parser/reader/binary_reader.c \
					$(MANDATORY_DIR)/parser/reader/read_file/memjoin.c \
					$(MANDATORY_DIR)/parser/reader/read_file/read_font_file.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_get_fixed.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_get_unicode_string.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_get_uint32.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_tell.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_get_2dot14.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_get_int32.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_get_string.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_get_int16.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_get_uint16.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_get_fword.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_slice.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_seek.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_get_date.c \
					$(MANDATORY_DIR)/parser/reader/methods/br_get_uint8.c \
					$(MANDATORY_DIR)/destroy_font.c \
					$(MANDATORY_DIR)/render/create_string.c \
					$(MANDATORY_DIR)/render/metrics.c \
					$(MANDATORY_DIR)/render/kern.c \
					$(MANDATORY_DIR)/render/string_dims.c \
					$(MANDATORY_DIR)/render/draw_context.c \
					$(MANDATORY_DIR)/render/draw_glyph.c \
					$(MANDATORY_DIR)/render/draw_text.c \
					$(MANDATORY_DIR)/render/drawing.c \
					$(MANDATORY_DIR)/render/images/ft_get_pixel_from_img.c \
					$(MANDATORY_DIR)/render/images/ft_new_image.c \
					$(MANDATORY_DIR)/render/images/ft_pixel_put.c \
					$(MANDATORY_DIR)/render/images/shapes.c

# math
SRCS			+=	$(MANDATORY_DIR)/math/ft_dist.c \
					$(MANDATORY_DIR)/math/ft_points.c \
					$(MANDATORY_DIR)/math/ft_points_cpy.c \
					$(MANDATORY_DIR)/math/ft_create_sdims.c
# util functions
SRCS			+=	$(MANDATORY_DIR)/utils/ft_strjoin.c \
					$(MANDATORY_DIR)/utils/ft_error.c \
					$(MANDATORY_DIR)/utils/ft_strdup.c \
					$(MANDATORY_DIR)/utils/ft_memcpy.c \
					$(MANDATORY_DIR)/utils/ft_strcmp.c \
					$(MANDATORY_DIR)/utils/ft_len.c \
					$(MANDATORY_DIR)/utils/ft_multichr.c \
					$(MANDATORY_DIR)/utils/ft_bzero.c \
					$(MANDATORY_DIR)/utils/ft_atoi.c \
					$(MANDATORY_DIR)/utils/ft_calloc.c \
					$(MANDATORY_DIR)/utils/ft_strtrim.c \
					$(MANDATORY_DIR)/utils/ft_strlcpy.c \
					$(MANDATORY_DIR)/utils/ft_split_utils.c \
					$(MANDATORY_DIR)/utils/ft_ljoin.c \
					$(MANDATORY_DIR)/utils/ft_replace.c \
					$(MANDATORY_DIR)/utils/ft_split.c \
					$(MANDATORY_DIR)/utils/ft_minmax.c \
					$(MANDATORY_DIR)/utils/ft_itoa.c

# objects
OBJS			=	$(patsubst $(MANDATORY_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# headers
HEADERS_DIR		=	$(MANDATORY_DIR)

CC				=	gcc
LIBC			=	ar rcs
RM				=	rm -f
CFLAGS			=	-I$(HEADERS_DIR) -g3 -O0 -Wall -Wextra -Werror

NAME			=	ttf_parser.a

GREEN			=	\033[1;32m
BLUE			=	\033[1;34m
RED				=	\033[1;31m
YELLOW			=	\033[1;33m
DEFAULT			=	\033[0m
UP				=	"\033[A"
CUT				=	"\033[K"

$(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.c $(HEADERS_SOURCES) Makefile
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf ${UP}${CUT}

all: $(NAME)

$(NAME): $(OBJS)
	@$(LIBC) $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"

clean:
	@echo "$(RED)Cleaning build folder$(DEFAULT)"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all lib clean fclean re
