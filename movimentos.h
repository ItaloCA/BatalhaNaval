typedef struct secondAlvos{
	int alvo;
	int x;
	int y;
}SA;

void revelar_barco(BARCO, int);

int atacar(TAB *t, int x, int y, BARCO *b, BARCO *frota, int* vidas, int* hp_inimigo, int, short int*);

int traduzir(char *,int*,int*);

int atacarComp(TAB *t, BARCO *frota, BARCO *b, int*, int*, int*, int*, int*, int*, int*, SA*);
