
CFLAGS = -I /home/iago/2018.1/TOPICOS-IV/cudd-3.0.0/cudd -I /home/iago/2018.1/TOPICOS-IV/cudd-3.0.0/util -I /home/iago/2018.1/TOPICOS-IV/cudd-3.0.0/
LFLAGS = -static -L /home/iago/2018.1/TOPICOS-IV/cudd-3.0.0/cudd/.libs/ -lcudd -lm

teste = main

default:	testprogram

testprogram: $(teste).o
	$(CC) $(teste).o -o testprogram $(LFLAGS)
$(teste).o:	$(teste).c
	$(CC) $(teste).c -c -o $(teste).o $(CFLAGS)
$(teste).c:
	$(CC) $(teste).c -c $(CFLAGS)
clean:
	rm -f *.o testprogram