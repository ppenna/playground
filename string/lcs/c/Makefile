# Copyright (C) 2023 Pedro Henrique Penna <pedrohenriquepenna@outlook.com>

# Directories
BINDIR = $(CURDIR)

# Source Files
SRC = $(wildcard *.c)

# Name of Executable File
EXEC = lcs.elf

# Default Run Arguments
ARGS ?= foobar

#===============================================================================
# Compiler Configuration
#===============================================================================

# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Og -g
CFLAGS += -std=c11 -fno-builtin -pedantic
CFLAGS += -Wall -Wextra -Werror -Wa,--warn
CFLAGS += -Winit-self -Wswitch-default -Wfloat-equal
CFLAGS += -Wundef -Wshadow -Wuninitialized -Wlogical-op
CFLAGS += -Wredundant-decls
CFLAGS += -Wno-missing-profile

#===============================================================================
# Build Rules
#===============================================================================

# Builds everything.
all: build

# Runs.
run: $(EXEC)
	@$(BINDIR)/$(EXEC) $(ARGS)

# Builds all artifacts.
build: $(EXEC)

# Cleans up all build artifacts.
clean:
	@rm -f $(BINDIR)/*.elf

# Builds a single executable file.
%.elf: $(SRC)
	@$(CC) $(CFLAGS) $< -o $(BINDIR)/$@
