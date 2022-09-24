DEBUG := g
CC := gcc

CFLAGS = -std=c2x -Wall -fmax-errors=10 -Wextra -I$(IDIR)
PKGCONFIG ?= 
LFLAGS := 
LIBS := 

# Defining directory
IDIR := include
SRCDIR := src
ODIR := obj
BINDIR := bin
RDIR := release

_DEPS := calculation.h error.h stack.h
DEPS := $(patsubst %, $(IDIR)/%, $(_DEPS))

# Required for creating directory
_OBJ := main.o calculation.o stack.o error.o
OBJ := $(patsubst %, $(ODIR)/%, $(_OBJ))

# Required for creating directory
_BIN := calculate
BIN := $(patsubst %, $(BINDIR)/%, $(_BIN))

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(LIBS) $^

$(ODIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $(CFLAGS) $(LFLAGS) $<

# Create obj directory if not exist
$(OBJ): | $(ODIR)

$(ODIR):
	mkdir $(ODIR)

# Create bin directory if not exist
$(BIN): | $(BINDIR)

$(BINDIR):
	mkdir $(BINDIR)

run:
	./$(BINDIR)/$(_BIN)

.PHONY: clean

clean:
	rm -f $(BIN) $(ODIR)/* 
