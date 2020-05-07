#
# MIT License
#
# Copyright(c) 2020 Pedro Henrique Penna <pedrohenriquepenna@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

# Directories.
export BINDIR = $(CURDIR)/bin
export INCDIR = $(CURDIR)/include
export SRCDIR = $(CURDIR)/src

# Toolchain.
CC = gcc

# Toolchain configuration
export CFLAGS += -std=c99 -fno-builtin
export CFLAGS += -pedantic -D _POSIX_C_SOURCE=200809L
export CFLAGS += -Wall -Wextra -Werror -Wa,--warn
export CFLAGS += -Winit-self -Wswitch-default -Wfloat-equal
export CFLAGS += -Wundef -Wshadow -Wuninitialized -Wlogical-op
export CFLAGS += -Wvla -Wredundant-decls
export CFLAGS += -Wno-missing-profile
export CFLAGS += -fno-stack-protector
export CFLAGS += -Wno-unused-function
export CFLAGS += -I $(INCDIR)

# Source files.
export SRC = $(wildcard $(SRCDIR)/utils/*.c)

#===============================================================================
# Top-Level Rules
#===============================================================================

# Builds executable.
all: make-dirs | all-math

# Cleans build objects.
clean: clean-math

# Create directories.
make-dirs:
	mkdir -p $(BINDIR)

#===============================================================================
# Math
#===============================================================================

# Builds math examples.
all-math:
	cd $(SRCDIR)/math && $(MAKE) all

# Cleans build objects.
clean-math:
	cd $(SRCDIR)/math && $(MAKE) clean
