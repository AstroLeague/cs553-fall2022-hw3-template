GCC=gcc
CFLAGS=-Wall

all: cpubench

cpubench: cpubench.c
	$(GCC) $(CFLAGS) -o $@ $<

clean: cpubench
	rm -rf cpubench