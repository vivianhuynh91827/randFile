all: rand.o
	gcc -o program rand.o

rand.o: rand.c rand.h
	gcc -c rand.c

run:
	./program

clean:
	rm *.o
	rm program
	rm *~
