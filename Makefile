CFLAGS          += -Wall
INC             +=
DEF             ?=
CC              ?= gcc
OBJ             := $(subst .c,.o,$(shell ls *.c))
LIBS		+= -lm

all: $(basename $(OBJ))

check: cppcheck $(basename $(OBJ))

cppcheck:
	@echo "cppcheck version: $(shell cppcheck --version)"
	@if [ $(.SHELLSTATUS) -ne 0 ]; then \
		sudo apt install cppcheck -y; fi
	@cppcheck *.c --enable=all --suppress=missingIncludeSystem 2>errors.txt

# Compile C files
%.o: %.c
	@echo 'Compiling $@...'
	$(CC) -c -o $@ $< $(CFLAGS) $(INC) $(DEF)

$(basename $(OBJ)): $(OBJ)
	@echo 'Assembling $@...'
	$(CC) $@.o -o $@ $(CFLAGS) $(LIBS)

clean:
	@rm -f $(basename $(OBJ)) $(OBJ)
