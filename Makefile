CC=gcc
FLAGS=-Wall -Werror -O3

all: hencode hdecode hanalysis

hencode: hencode.o tree.o CodeTable.o
	$(CC) -o hencode hencode.o tree.o CodeTable.o

hencode.o: hencode.c tree.h CodeTable.h
	$(CC) $(FLAGS) -c hencode.c

CodeTable.o: CodeTable.c CodeTable.h
	$(CC) $(FLAGS) -c CodeTable.c

hdecode: hdecode.o tree.o
	$(CC) -o hdecode hdecode.o tree.o

hdecode.o: hdecode.c tree.h
	$(CC) $(FLAGS) -c hdecode.c

hanalysis: hanalysis.o tree.o CodeTable.o
	$(CC) -o hanalysis hanalysis.o tree.o CodeTable.o

hanalysis.o: hanalysis.c tree.h
	$(CC) $(FLAGS) -c hanalysis.c

tree.o: tree.c tree.h
	$(CC) $(FLAGS) -c tree.c


clean:
	rm *.o
	rm *.huff
	rm hencode
	rm hdecode