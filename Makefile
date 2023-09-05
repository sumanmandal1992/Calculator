CC ?= gcc
DBUG := -g

CFLAGS = -std=c2x -Wall -fmax-errors=10 -Wextra -I$(IDIR) $(DBUG)
PKGCONFIG ?= 
SDLCONFIG ?=
MYSQLCONFIG ?=
LFLAGS := 
LIBS := -lm

IDIR := include
SRCDIR := src
ODIR := obj
BINDIR := bin
DBUGDIR = dbug
RDIR := release

_DEPS := %.h
DEPS := $(patsubst %, $(IDIR)/%, $(_DEPS))

# Required for creating directory
_OBJ := main.o stack.o calculate.o
OBJ := $(patsubst %, $(ODIR)/%, $(_OBJ))

# Required for creating directory
_BIN := calculate
BIN := $(patsubst %, $(BINDIR)/%, $(_BIN))

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

$(ODIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(LFLAGS) -c -o $@ $<

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
