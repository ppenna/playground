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
BINDIR = $(CURDIR)/bin
INCDIR = $(CURDIR)/include
SRCDIR = $(CURDIR)/src

# Toolchain.
CC = gcc

# Toolchain configuration
CFLAGS = -O3
CFLAGS += -std=c99 -fno-builtin
CFLAGS += -pedantic -D _POSIX_C_SOURCE=200809L
CFLAGS += -Wall -Wextra -Werror -Wa,--warn
CFLAGS += -Winit-self -Wswitch-default -Wfloat-equal
CFLAGS += -Wundef -Wshadow -Wuninitialized -Wlogical-op
CFLAGS += -Wvla -Wredundant-decls
CFLAGS += -Wno-missing-profile
CFLAGS += -fno-stack-protector
CFLAGS += -Wno-unused-function
CFLAGS += -I $(INCDIR)

# Executable.
EXEC = mm

# Source files.
SRC = $(wildcard $(SRCDIR)/*.c)

# Builds executable.
all: all-debug all-release

# Create directories.
make-dirs:
	mkdir -p $(BINDIR)

# Builds release version.
all-release: make-dirs
	$(CC) $(CFLAGS) -D NDEBUG $(SRC) -o $(BINDIR)/$(EXEC)

# Builds debug version.
all-debug: make-dirs
	$(CC) $(CFLAGS) $(SRC) -o $(BINDIR)/$(EXEC)

# Cleans build objects.
clean:
	@rm -f $(BINDIR)/$(EXEC)
