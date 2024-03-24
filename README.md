# TrueType Font (.ttf) File Parser in C with MLX Graphical Implementation

This project is a TrueType Font (.ttf) file parser implemented in the C language, accompanied by a graphical implementation using the MLX (MiniLibX) library.

## Introduction

TrueType Font (.ttf) files are widely used to represent fonts in modern computer systems. This parser extracts essential data from .ttf files, such as glyph, header, and index tables, for use in various applications.

The graphical implementation provided with this project utilizes the MLX library, a simplified graphics library for C programming on macOS and Linux, developed by L'école 42.

## Prerequisites

Before you can use this project, make sure you have the following dependencies installed:

- A compatible C compiler (gcc recommended)
- The MLX library (MiniLibX) installed on your system (for graphical implementation)

## Understanding the TrueType Font (.ttf) Format

The TrueType Font (.ttf) format is a widely used font file format that contains data necessary for rendering fonts on computer systems. It consists of several tables, including glyph data, header information, and index tables.

- **Glyph Data**: Contains information about individual characters (glyphs), such as their outlines, metrics, and hints.
- **Header Information**: Provides metadata about the font file, including its version, revision, and various flags.
- **Index Tables**: Help locate specific data within the font file, such as glyph outlines and character mappings.

Understanding the structure and contents of these tables is essential for parsing .ttf files and utilizing the font data effectively.

For more info about TTF tables, see [Apple TrueType-Reference-Manual](https://developer.apple.com/fonts/TrueType-Reference-Manual/)

## Usage

1. Clone this repository to your machine:
	```bash
	git clone https://github.com/Maxenceee/ttf_parser.git
	```

2. Compile the lib using the make file
	```bash
	make
	```

3. Include the lib and use it
	```c
	#include "font.h"

	...

	create_new_font("ttf", "path/to/file.ttf", "fontname");
	```