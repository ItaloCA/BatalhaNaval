all: main.o tabuleiroBN.o movimento.o
	gcc main.o tabuleiroBN.o movimento.o -o batalhanaval

main: tabuleiroBN.h movimento.h main.c
	gcc -g -c main.c

tabuleiro: tabuleiroBN.c tabuleiroBN.h
	gcc -g -c tabuleiroBN.c

movimento: tabuleiroBN.h movimento.h movimento.c
	gcc -g -c movimento.c

clean:
	rm -f *.o
	rm batalhanaval