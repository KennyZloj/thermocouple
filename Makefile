CFLAGS          += -Wall
INC             +=
DEF             ?=
CC              ?= gcc
OBJ             := $(subst .c,.o,$(shell ls *.c))
LIBS		+= -lm

# Compile C files
%.o: %.c
	@echo 'Compiling $@...'
	$(CC) -c -o $@ $< $(CFLAGS) $(INC) $(DEF)

$(basename $(OBJ)): $(OBJ)
	@echo 'Assembling $@...'
	$(CC) $@.o -o $@ $(CFLAGS) $(LIBS)

all: $(basename $(OBJ))

clean:
	@rm -f $(basename $(OBJ)) $(OBJ)
