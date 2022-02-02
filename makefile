build:
	@gcc -Wall bit.c -o prog
	@./prog

clean:
	@rm -f ./exe/*

%: ./src/%.c
	@gcc -Wall -o ./exe/$@ $<
	@./exe/$@
