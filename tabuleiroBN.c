#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Valores para descoberto:
	-1 : * (Destruido mas não por completo)
	 0 : Não descoberto
	 1 : Destruido por total


Valores para tipo:
	 0 : Água
	 1 : Jangada
	 2 : Submarino 1
	 3 : Submarino 2
	 4 : Fragata 1
	 5 : Fragata 2
	 6 : Fragata 3
	 7 : Destroyer 1
	 8 : Destroyer 2
	 9 : Porta aviões
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
	TAB* proa_final;
	char direcao;
}BARCO;

int inserir(TAB *t,BARCO * b , int x , int y, int d, int tipo, int revelar){
	/*
	Função:
		-inserir()
	Parametros:
		-TAB *t: Tabuleiro
		-BARCO * b: Um elemento do vetor de barcos recebido da função poisicionando_barcos() 
		-x: Coluna
		-y: Linha
		-d: Direção para qual o barco deve ser posicionado
		-tipo: Qual barco será inserido
		-revelar: Se deve-se ou não revelar o conteúdo inserido
	Descrição:
		-Insere em um tabuleiro "t", um barco de um certo "tipo" no ponto "(x,y)" com a struct barco "b"
		sendo usada para auxiliar na insersao e um int revelar para
		saber se devemos ou nao revelar as pecas inseridas
	*/

	int i;
	TAB *aux;
	for (i = 0; i < y; i++)
		t = t->baixo;
	for (i = 0; i < x; i++)
		t = t->dir;
	aux = t;
	if(t->celula == 'O'){
		if(tipo == 1 ){
			b->proa = t;
			b->proa_final = t;
			t->celula = '&';
			t->tipo = tipo;
			if(revelar)
				t->descoberto = 1;
			return 1;
		}
		else if(tipo < 4){
			b->proa = t;
			b->proa_final = t;
			t->celula = '@';
			t->tipo = tipo;
			if(revelar)
				t->descoberto = 1;
			return 1;
		}aux = t;
		if(d == 0){
			for(i = 0 ; aux != NULL && i < b->pecasRest ; i++){
				if (aux->celula != 'O')
					aux = NULL;
				else
					aux = aux->esq;
			}if(aux != NULL){
				for (i = 0; i < b->pecasRest; ++i){
					t->tipo = tipo;	
					if(revelar)
						t->descoberto = 1;	
					if(i == 0){
						b->proa = t;
						b->direcao = 'e';
						t->celula = '>';
					}else if(i == b->pecasRest - 1){
						t->celula = '<';
						b->proa_final = t; 
					}else
						t->celula = '#';
					t = t->esq;	
				}
				return 1;
			}else
				return 0;
		}
		if(d == 1){
			for(i = 0 ; aux != NULL && i < b->pecasRest ; i++){
				if (aux->celula != 'O')
					aux = NULL;
				else
					aux = aux->dir;
			}if(aux != NULL){
				for (i = 0; i < b->pecasRest; ++i){
					t->tipo = tipo;
					if(revelar)
						t->descoberto = 1;
					if(i == 0){
						t->celula = '<';
						b->direcao = 'd';
						b->proa = t;
					}else if(i == b->pecasRest - 1){
						b->proa_final = t; 
						t->celula = '>';
					}
					else 
						t->celula = '#';
					t = t->dir;
				}
				return 1;
			}else 
				return 0;
		}
		if(d == 2){
			for(i = 0 ;aux != NULL && i < b->pecasRest ; i++){
				if (aux->celula != 'O')
					aux = NULL;
				else
					aux = aux->cima;
			}if(aux != NULL){
				for (i = 0; i < b->pecasRest; ++i){
					t->tipo = tipo;
					if(revelar)
						t->descoberto = 1;
					if(i == 0){
						b->proa = t;
						b->direcao = 'c';
						t->celula = 'v';
					}else if(i == b->pecasRest - 1){
						b->proa_final = t; 
						t->celula = '^';
					}
					else 
						t->celula = '#';
					t = t->cima;
				}
				return 1;
			} else
				return 0;
		}
		if(d == 3){
			for(i = 0 ; aux != NULL && i < b->pecasRest ; i++){
				if (aux->celula != 'O')
					aux = NULL;
				else
					aux = aux->baixo;
			}if(aux != NULL){
				for (i = 0; i < b->pecasRest; ++i){
					t->tipo = tipo;
					if(revelar)
						t->descoberto = 1;
					if(i == 0){
						b->proa  = t;
						b->direcao = 'b';
						t->celula = '^';
					}else if(i == b->pecasRest - 1){
						b->proa_final = t;
						t->celula = 'v';
					}
					else 
						t->celula = '#';
					t = t->baixo;
				}
				return 1;
			}else
				return 0;
		}

	}else
		return 0;
	return 0;
}
void poisicionando_barcos(TAB* t, BARCO b[9], int revelar){
	/*
	Função:
		-poisicionando_barcos()
	Parametros:
		-TAB* t: Tabuleiro
		-BARCO b[9]: Vetor de Barcos
		-revelar: Variável que decide se deve-se ou nao revelar
	o conteudo inserido no tabuleiro
	Descricao:
		-Recebe um ponteiro para tabuleiro "t", um vetor de Barcos "b"
		onde esse vetor de Barcos sera preenchido com os devido número
		de peças que cada barco precisa, e depois irá usar outra função para
		preencher o tabuleiro com tais barcos. O inteiro revelar é usado
		para saber se é necessário revelar as peças inseridas.
	*/

	int barcos = 0,x,y,i,d;
	while(barcos <= 8){
		if(barcos < 3)
			b[barcos].pecasRest = 1;
		else if(barcos < 6)
			b[barcos].pecasRest = 2;
		else if(barcos < 8)
			b[barcos].pecasRest = 3;
		else if(barcos < 9)
			b[barcos].pecasRest = 5;
		b[barcos].proa = NULL;
		b[barcos].direcao = ' ';
		barcos++;
	}barcos = 1;
	while(barcos < 10){
		x = rand()%12;
		y = rand()%12;
		d = rand()%4;
		i = inserir(t , &b[barcos - 1] , x , y , d , barcos, revelar);
		if(i == 1){
			barcos++;
		}
	}
}

void criar_tabuleiro(TAB** r){
	/*
	Função:
		-criar_tabuleiro()
	Parametros:
		-TAB **r: Ponteiro para tabuleiro
	Descrição:
		-Recebe um ponteiro para tabuleiro "r",
		cria um tabuleiro 12x12 com r apontando para
		sua posicao inicia (0,0).
	*/

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
	/* 
	Função:
		-imprimir()
	Parametros:
		-TAB* t: Tabuleiro do usuário
		-TAB* e: Tabuleiro do computador
	Descrição:
		-Recebe dois tabuleiros, "t" e "e", que serão impressos na tela.
	*/

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

void limpar_tabuleiro(TAB* t, int f){
	int i;
	TAB* inicio = t->baixo;
	TAB* ant = t;

	for (i = 0; i < 144; i++){
		t->celula = 'O';
		t->descoberto = 0;
		t->tipo = 0;
		
		if(t->dir != NULL){	
			if(f)
				ant = t;
			t = t->dir;
		}
		else{
			if(f)
				ant = t;
			t = inicio;
			if(inicio->baixo != NULL)
				inicio = inicio->baixo;
		}

		free(ant);
	}

}