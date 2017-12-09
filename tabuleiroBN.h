//typedef struct tabuleiro TAB;

//typedef struct barco BARCO;

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

int inserir(TAB*, BARCO*, int, int, int, int);

void poisicionando_barcos(TAB*, BARCO [9]);

void criar_tabuleiro(TAB**);

void imprimir(TAB*, TAB*);
