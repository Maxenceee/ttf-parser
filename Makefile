NAME            := ttf_parser.a

MANDATORY_DIR   := srcs
OBJ_DIR         := .objs

CC              := gcc
LIBC            := ar rcs
RM              := rm -rf

CFLAGS          := -Wall -Wextra -Werror -g3 -O0
DEPSFLAGS       := -MMD -MP
INCLUDES        := -I $(MANDATORY_DIR)

ALL_CFLAGS      := $(CFLAGS) $(DEPSFLAGS) $(INCLUDES)

# Fonts
SRCS            := $(MANDATORY_DIR)/free_ttf.c \
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

# Math
SRCS            += $(MANDATORY_DIR)/math/ft_dist.c \
                   $(MANDATORY_DIR)/math/ft_points.c \
                   $(MANDATORY_DIR)/math/ft_points_cpy.c \
                   $(MANDATORY_DIR)/math/ft_create_sdims.c

# Util functions
SRCS            += $(MANDATORY_DIR)/utils/ft_strjoin.c \
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

OBJS            := $(patsubst $(MANDATORY_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
ALL_DEPS        := $(OBJS:.o=.d)

TOTAL_FILES     := $(words $(OBJS))
CURRENT_FILE    := 0

BOLD            := \033[1m
DIM             := \033[2m
CYAN            := \033[36m
GREEN           := \033[32m
YELLOW          := \033[33m
BLUE            := \033[34m
MAGENTA         := \033[35m
RED             := \033[31m
RESET           := \033[0m

define update_progress
	$(eval CURRENT_FILE=$(shell expr $(CURRENT_FILE) + 1))
	$(eval PERCENT=$(shell expr $(CURRENT_FILE) \* 100 / $(TOTAL_FILES)))
	$(eval PROGRESS=$(shell expr $(CURRENT_FILE) \* 20 / $(TOTAL_FILES)))
	$(eval REMAINING=$(shell expr 20 - $(PROGRESS)))
	@printf "\r\033[K   $(GREEN)✔$(RESET) %b %-50s$(RESET)\n" "$(1)" "$(2)"
	@printf "   [$(GREEN)%s$(DIM)%s$(RESET)] %3d%%" \
		"$(shell printf '%0.s#' $$(seq 1 $(PROGRESS) 2>/dev/null))" \
		"$(shell printf '%0.s-' $$(seq 1 $(REMAINING) 2>/dev/null))" \
		"$(PERCENT)"
endef

define get_file_size
$$(du -h $(1) 2>/dev/null | awk '{print $$1}')
endef

all: $(NAME)

$(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.c Makefile
	@mkdir -p $(@D)
	$(call update_progress,$(YELLOW)Compiling C  $(RESET), $<)
	@$(CC) $(ALL_CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@printf "\r\033[K\n   $(BOLD)$(BLUE)Creating static library $(NAME)...$(RESET)\n"
	@$(LIBC) $(NAME) $(OBJS)
	@if [ -f $(NAME) ]; then \
		printf "   $(GREEN)✔ $(NAME) compiled successfully!$(RESET) $(DIM)(%s)$(RESET)\n\n" "$(call get_file_size,$(NAME))"; \
	else \
		printf "   $(RED)✖ Failed to create $(NAME)$(RESET)\n\n"; \
		exit 1; \
	fi

-include $(ALL_DEPS)

clean:
	@printf "   $(RED)➤ Cleaning objects...$(RESET)\n"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@printf "   $(RED)➤ Removing library...$(RESET)\n"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re