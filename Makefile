
all:
	gcc -c chip.c
	gcc -c main.c
	gcc -c match.c
	gcc -c combi.c
	gcc -c terminal.c
	gcc -o bin {chip,main,match,combi,terminal}.o

clean:
	rm -f bin *.o
