CC=gcc
CCARGS=-Wall -o
CCTEST=-I$(HOME)/local/include

build:
	@gcc -Wall bit.c -o prog
	@./prog

clean:
	@rm -f ./exe/*

%: ./src/%.c
	@gcc -Wall -o ./exe/$@ $<
	@./exe/$@

supple:
	@gcc -Wall -o ./exe/bit_manip ./supp/bit_manip.c
