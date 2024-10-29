testbigint: testbigint.o bigint.o
	cc -o $@ $^

%.o: %.c *.h Makefile
	cc -c -o $@ $<
