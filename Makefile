.PHONY: all clean

all:
	make -j6 -C  src

clean:
	make -C src clean