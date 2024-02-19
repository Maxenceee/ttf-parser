#!/bin/bash

if [ "$(uname)" == "Darwin" ]; then
	MLX_DIR=libmlx_mac
	MLX_LIB="-L./$MLX_DIR -lmlx -framework OpenGL -framework AppKit"
else
	MLX_DIR=libmlx_linux
	MLX_LIB="-L./$MLX_DIR -lmlx -lX11 -lXext -lm"
fi

SRCS="main.c"

gcc $SRCS $MLX_LIB ../ttf_parser.a -g3
