
CFLAGS = -I /home/iago/2018.1/TOPICOS-IV/cudd-3.0.0/cudd -I /home/iago/2018.1/TOPICOS-IV/cudd-3.0.0/util -I /home/iago/2018.1/TOPICOS-IV/cudd-3.0.0/
LFLAGS = -static -L /home/iago/2018.1/TOPICOS-IV/cudd-3.0.0/cudd/.libs/ -lcudd -lm

testprogram: test.o
	$(CC) test.o -o testprogram $(LFLAGS)
	rm *.o
test.o: test.c
	$(CC) test.c -c -o test.o $(CFLAGS)
test.c:
	$(CC) test.c -c $(CFLAGS)
clean: ; rm -f *.o testprogram
