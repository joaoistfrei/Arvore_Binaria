all:
	gcc -c arvbin.c -I . -o compilado.o
	gcc main.c compilado.o -I . -o main.exe

run:
	./main.exe