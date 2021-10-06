./run: mainfile.o functions.o
	gcc -o run mainfile.o functions.o
mainfile.o:mainfile.c adj.h
	gcc -c mainfile.c
functions.o:functions.c adj.h
	gcc -c functions.c
