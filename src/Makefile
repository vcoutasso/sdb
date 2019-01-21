all: main.o sequential.o
	gcc -g main.o sequential.o -o ../bin/sdb

main.o: main.c sequential.h
	gcc main.c -o main.o -c -Wall -pedantic

sequential.o: sequential.c sequential.h
	gcc sequential.c -o sequential.o -c -Wall -pedantic

clean:
	rm *.o
