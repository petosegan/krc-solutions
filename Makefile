CFLAGS=-Wall -g -lm

SOURCES=$(wildcard *.c)
EXECUTABLES=$(SOURCES:%.c=%)

all: $(EXECUTABLES)
	echo "Done"

clean:
	rm -f $(EXECUTABLES)
