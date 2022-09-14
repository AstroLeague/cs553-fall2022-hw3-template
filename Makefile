GCC=gcc
CFLAGS=-Wall -Werror -O3

all: cpubench.c
	$(GCC) $(CFLAGS) -o cpubench $<

clean:
	rm -rf cpubench
