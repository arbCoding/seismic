# Don't echo all the bash commands!
MAKEFLAGS += --silent
# Use the correct shell for bash scripts
# seemed to default to /bin/sh when I use /bin/bash
SHELL := /bin/bash
# Linux or Mac
uname_s := $(shell uname -s)

ifeq ($(uname_s), Linux)
	cxx = g++
else
	cxx = g++-12 # Homebrew g++ install I have
#	cxx = clang
endif

# Param always used
param = -std=c++20 -pedantic-errors -Wall
# Debug params only if debug is true
# Default should be to avoid shadowing, so after 6.5 add the
# -Wshadow prefix to give errors on shaowing (avoid doing it!)
#  Clang
#debug_param = -Weffc++ -Wextra -Wsign-conversion -Werror -Wshadow -ggdb
# G++
debug_param = -fanalyzer -Weffc++ -Wextra -Wsign-conversion -Werror -ggdb
# debug_param = -fanalyzer -Weffc++ -Wextra -Wsign-conversion -Werror -ggdb
# Release params only if debug is false
release_param = -O2 -DNDEBUG

debug = true

ifeq ($(debug), true)
	params = $(param) $(debug_param)
else
	params = $(param) $(release_param)
endif

# Where the source code files are being stored
src_prefix = ./src/
# Header prefix
hdr_prefix = $(src_prefix)header/

all: read_sac_test sac_class_test

read_sac_test: $(src_prefix)read_sac_test.cpp $(hdr_prefix)read_sac.cpp
	@echo "Building read_sac_test..."
	$(cxx) -o read_sac_test $(src_prefix)read_sac_test.cpp $(hdr_prefix)read_sac.cpp -I$(hdr_prefix) $(params)

sac_class_test: $(src_prefix)sac_class_test.cpp $(hdr_prefix)sac_class.cpp $(hdr_prefix)read_sac.cpp
	@echo "Building sac_class_test..."
	$(cxx) -o sac_class_test $(src_prefix)sac_class_test.cpp $(hdr_prefix)sac_class.cpp $(hdr_prefix)read_sac.cpp -I$(hdr_prefix) $(params)

clean:
	rm -rf read_sac_test sac_class_test *.dSYM
