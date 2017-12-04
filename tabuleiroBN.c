#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*Documentação

Valores para descoberto:
	-1 : * (Destruido mas não por completo)
	 0 : Não descoberto
	 1 : Destruido por total


Valores para tipo
	 0 : Agua
	 2 : Submarino 1
	 3 : Submarino 2
	 4 : Fragata 1
	 5 : Fragata 2
	 6 : Fragata 3
	 7 : Destroyer 1
	 8 : Destroyer 2
	 9 : Porta aviões
	 10: Jangada
*/
typedef struct tabuleiro{
	struct tabuleiro *cima;
	struct tabuleiro *esq;
	struct tabuleiro *dir;
	struct tabuleiro *baixo;
	char celula;
	short int descoberto;
	short int tipo;
}TAB;

typedef struct barco{
	short int pecasRest;
	TAB* proa;
	char direcao;
}BARCO;

int inserir(TAB *t,BARCO * b , int x , int y, int d, int tipo){
	int i;
	TAB *aux;
	for (i = 0; i < y; i++)
		t = t->baixo;
	for (i = 0; i < x; i++)
		t = t->dir;
	if(t->celula == ' '){
		if(d == 0){
			for(i = 0 ; i < b->pecasRest && aux != NULL ; i++){
				aux = t->esq;
				if (aux->celula != ' ')
					aux = NULL;
			}if(aux != NULL){
				for (i = 0; i < b->pecasRest; ++i){
					t->tipo = tipo;	
					t->descoberto = 1;	
					if(i == 0)
						t->celula = '>';
					else if(i == b->pecasRest - 1)
						t->celula = '<';
					else 
						t->celula = '#';
				}return 1;
			}else
				return 0;
		}
		if(d == 1){
			for(i = 0 ; i < b->pecasRest && aux != NULL ; i++){
				aux = t->dir;
				if (aux->celula != ' ')
					aux = NULL;
			}if(aux != NULL){
				for (i = 0; i < b->pecasRest; ++i){
					t->tipo = tipo;
					t->descoberto = 1;
					if(i == 0)
						t->celula = '<';
					else if(i == b->pecasRest - 1)
						t->celula = '>';
					else 
						t->celula = '#';
				}return 1;
			}else 
				return 0;
		}
		if(d == 2){
			for(i = 0 ; i < b->pecasRest && aux != NULL ; i++){
				aux = t->cima;
				if (aux->celula != ' ')
					aux = NULL;
			}if(aux != NULL){
				for (i = 0; i < b->pecasRest; ++i){
					t->tipo = tipo;
					t->descoberto = 1;
					if(i == 0)
						t->celula = 'v';
					else if(i == b->pecasRest - 1)
						t->celula = '^';
					else 
						t->celula = '#';
				}return 1;
			} else
				return 0;
		}
		if(d == 3){
			for(i = 0 ; i < b->pecasRest && aux != NULL ; i++){
				aux = t->baixo;
				if (aux->celula != ' ')
					aux = NULL;
			}if(aux != NULL){
				for (i = 0; i < b->pecasRest; ++i){
					t->tipo = tipo;
					t->descoberto = 1;
					if(i == 0)
						t->celula = '^';
					else if(i == b->pecasRest - 1)
						t->celula = 'v';
					else 
						t->celula = '#';
				}return 1;
			}else
				return 0;
		}

	}else
		return 0;
	



}

void poisicionando_barcos(TAB* t, BARCO b[9]){
	int barcos = 0,x,y;
	while(barcos <= 8){
		b[barcos].pecasRest = 0;
		b[barcos].proa = NULL;
		b[barcos].direcao = ' ';
		barcos++;
	}barcos = 0;
	b[8].pecasRest = 5;
	x = rand()%12;
	y = rand()%12;
	b->direcao = rand()%12;
	inserir(t , &b[8] , 6,6,1,7);
}

void criar_tabuleiro(TAB** r){
	int i, j;
	(*r) = (TAB*)malloc(sizeof(TAB));
	TAB* p = *r , *inicio = (*r);
	p->cima = NULL;
	p->esq = NULL;
	p->celula = 'O';
	p->tipo = 0;
	p->descoberto = 0;



	for (i = 0; i < 12; i++){
		p->dir = (TAB*)malloc(sizeof(TAB));
		(p->dir)->cima = NULL;
		(p->dir)->esq = p;
		p = p->dir;
		p->celula = 'O';
		p->tipo = 0;
		p->descoberto = 0;
	}
	
	p->dir = NULL;

	
	TAB*superior;
	superior = inicio;

	for(i=0; i<10; i++){
		superior->baixo = (TAB*)malloc(sizeof(TAB));
		p = superior->baixo;
		p->cima = superior;
		p->celula = 'O';
		p->tipo = 0;
		p->descoberto = 0;
		p->esq = NULL;


		for(j=0; j<11; j++){

				p->dir = (TAB*)malloc(sizeof(TAB));

				(p->dir)->esq = p;
				
				p = p->dir;
				p->celula = 'O';
				p->tipo = 0;
				p->descoberto = 0;
				
				superior = superior->dir;
				superior->baixo = p;
				p->cima = superior;		


		}

		p->dir = NULL;

		inicio = inicio->baixo;
		superior = inicio;
	}


	superior->baixo = (TAB*)malloc(sizeof(TAB));
	p = superior->baixo;
	p->cima = superior;
	p->celula = 'O';
	p->tipo = 0;
	p->descoberto = 0;
	p->esq = NULL;
	p->baixo = NULL;

	for (i = 0; i < 11; i++){

		p->dir = (TAB*)malloc(sizeof(TAB));

		(p->dir)->esq = p;
		
		p = p->dir;
		p->celula = 'O';
		p->tipo = 0;
		p->descoberto = 0;
		
		superior = superior->dir;
		superior->baixo = p;
		p->cima = superior;
		p->baixo = NULL;

	}

	p->dir = NULL;

}


void imprimir(TAB* t, TAB* e){
	int i,j;
	TAB* lh = t, *lc = e;
	printf("           JOGADOR 1                      COMPUTADOR\n");
	printf("    A B C D E F G H I J K L        A B C D E F G H I J K L \n");
	for (i = 1; i < 13; i++){
		if(i<10)
			printf(" %d| ", i);
		else
			printf("%d| ", i);
		for (j = 0; j < 24; j++){
			if(j<12){
				if(t->descoberto == 1){
					printf("%c ", t->celula);
					t = t->dir;
				}else if(t->descoberto == -1){
					printf("* ");
					t = t->dir;
				}else{
					printf("  ");
					t = t->dir;
				}
			}
			else{
				if(j == 12){
					if(i<10)
						printf("|   %d| ", i);
					else
						printf("|  %d| ", i);					
				}
				if(e->descoberto == 1){
					printf("%c ", e->celula);
					e = e->dir;
				}else if(e->descoberto == -1){
					printf("* ");
					e = e->dir;
				}else{
					printf("  ");
					e = e->dir;
				}
			}
		}

		lh = lh->baixo;
		t = lh;
		lc = lc->baixo;
		e = lc;
		printf("|\n");

	}
	printf("\n");

}

