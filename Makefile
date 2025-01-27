all: prog

clean:
	rm -rf *.o prog

temp_api.o: temp_api.c
	gcc -c -o temp_api.o temp_api.c

Cur.o: Cur.c 
	gcc -c -o Cur.o Cur.c

prog: Cur.o temp_api.o
	gcc -o prog Cur.o temp_api.o




