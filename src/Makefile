# https://cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC=g++
IDIR=../include
CFLAGS=-I$(IDIR) -g

BUILDDIR=..
ODIR=obj# object files subdirectory
#LDIR=../lib

LIBS=-lm # https://stackoverflow.com/questions/44175151/what-is-the-meaning-of-lm-in-gcc

_DEPS = IPv4Address.hpp VLSM.hpp LinkedList.hpp FLSM.hpp Exercises.hpp
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS)) # https://stackoverflow.com/questions/32176074/function-patsubst-in-makefile

_OBJ = main.o IPv4Address.o VLSM.o FLSM.o Exercises.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILDDIR)/esercizi-subnetting: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	# https://stackoverflow.com/questions/31999634/what-is-core-in-the-command-rm-f-core-incdir
	rm -rf $(ODIR)
	rm -f *~ core $(INCDIR)/*~
