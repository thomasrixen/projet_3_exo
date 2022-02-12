CC=gcc
CCARGS= -Wall -o 
CCTEST=-I$(HOME)/local/include
THREADS = -lpthread

build:
	@gcc -Wall bit.c -o prog
	@./prog

clean:
	@rm -f ./exe/*

%: ./src/%.c
	@gcc -Wall -o ./exe/$@ $< $(THREADS)
	@./exe/$@

supple:
	@gcc -Wall -o ./exe/bit_manip ./supp/bit_manip.c
