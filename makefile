all: main.o rand.o
	gcc -o program main.o rand.o

main.o: main.c rand.h
	gcc -c main.c

rand.o: rand.c rand.h
	gcc -c struct.c

run:
	./program

clean:
	rm *.o
	rm program
	rm *~
