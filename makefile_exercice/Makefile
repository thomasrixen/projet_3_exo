build : main.o module_a.o module_b.o
	@gcc -o prog $^

%.o : %.c %.h
	@gcc -c $<

clean:
	@rm -f *.o prog
