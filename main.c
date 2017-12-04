#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tabuleiroBN.h"

int main(int argc, char const *argv[]){
	
	TAB* HUM, *COM;
	BARCO barcJo1[9];
	BARCO barcCom[9];
	int contJo1 = 8;
	int contCom = 8;
	srand(time(NULL));

	criar_tabuleiro(&COM);
	criar_tabuleiro(&HUM);
	poisicionando_barcos(HUM,barcJo1);
	printf("%d\n",rand()%12 );
	printf("%d\n",rand()%12 );


	imprimir(HUM, COM);

	return 0;
}

