main: main.c utils.o stack.o cal.o
	gcc -o out main.c utils.o stack.o cal.o
	make clear

stack.o: stack.c stack.h
	gcc -c -o stack.o stack.c

utils.o: utils.c utils.h
	gcc -c -o utils.o utils.c

cal.o: cal.c cal.h
	gcc -c -o cal.o cal.c

clear: utils.o stack.o cal.o
	rm utils.o stack.o cal.o


