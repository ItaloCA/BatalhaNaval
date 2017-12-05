all: main.o tabuleiroBN.o movimentos.o
	gcc main.o tabuleiroBN.o movimentos.o -o batalhanaval

main: tabuleiroBN.h movimentos.h main.c
	gcc -g -c main.c

tabuleiro: tabuleiroBN.c tabuleiroBN.h
	gcc -g -c tabuleiroBN.c

movimento: tabuleiroBN.h movimentos.h movimentos.c
	gcc -g -c movimentos.c

clean:
	rm -f *.o
	rm batalhanaval