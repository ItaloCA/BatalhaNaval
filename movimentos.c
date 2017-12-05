#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tabuleiroBN.h"


void revelar_barco(BARCO embarcacao, int tipo){
	int i;
	TAB * proa = embarcacao.proa;
	if(embarcacao.direcao == 'c'){
		if(tipo <= 6){
			for (i = 0; i < 2; i++){
				proa->descoberto = 1;
				proa = proa->cima;
			}
		}
		else if(tipo > 6 && tipo <= 8){
			for (i = 0; i < 3; i++){
				proa->descoberto = 1;
				proa = proa->cima;
			}
		}
		else if(tipo == 9){
			for (i = 0; i < 5; i++){
				proa->descoberto = 1;
				proa = proa->cima;
			}
		}
	}
	if(embarcacao.direcao == 'b'){
		if(tipo <= 6){
			for (i = 0; i < 2; i++){
				proa->descoberto = 1;
				proa = proa->baixo;
			}
		}
		else if(tipo > 6 && tipo <= 8){
			for (i = 0; i < 3; i++){
				proa->descoberto = 1;
				proa = proa->baixo;
			}
		}
		else if(tipo == 9){
			for (i = 0; i < 5; i++){
				proa->descoberto = 1;
				proa = proa->baixo;
			}
		}
	}
	if(embarcacao.direcao == 'e'){
		if(tipo <= 6){
			for (i = 0; i < 2; i++){
				proa->descoberto = 1;
				proa = proa->esq;
			}
		}
		else if(tipo > 6 && tipo <= 8){
			for (i = 0; i < 3; i++){
				proa->descoberto = 1;
				proa = proa->esq;
			}
		}
		else if(tipo == 9){
			for (i = 0; i < 5; i++){
				proa->descoberto = 1;
				proa = proa->esq;
			}
		}
	}
	if(embarcacao.direcao == 'd'){
		if(tipo <= 6){
			for (i = 0; i < 2; i++){
				proa->descoberto = 1;
				proa = proa->dir;
			}
		}
		else if(tipo > 6 && tipo <= 8){
			for (i = 0; i < 3; i++){
				proa->descoberto = 1;
				proa = proa->dir;
			}
		}
		else if(tipo == 9){
			for (i = 0; i < 5; i++){
				proa->descoberto = 1;
				proa = proa->dir;
			}
		}
	}

}



int atacar(TAB *t, int x, int y, BARCO *b, BARCO *frota, int* vidas, int* hp_inimigo){
	int i;

	for (i = 0; i < y; i++){
		t = t->dir;
	}
	for (i = 0; i < x; i++){
		t = t->baixo;
	}	

	if(t->descoberto != -1 && t->descoberto != 1){


		if(t->tipo < 4){
			t->descoberto = 1;
			(b[(t->tipo) - 1]).pecasRest -= 1;

			if(t->tipo == 10){   //Caso JANGADA. Pode ser 1 tambem, sujeito a  mudanca
				if((frota[1]).pecasRest){
					(frota[1]).pecasRest = 0;
					((frota[1]).proa)->descoberto = 1;
				}
				else {
					(frota[2]).pecasRest = 0;
					((frota[2]).proa)->descoberto = 1;
				}
				*vidas--;
			}else                //Caso SUBMARINO
				*hp_inimigo--;

			return 0;
		}

		//OUTROS CASOS
		b[t->tipo - 1].pecasRest -= 1;
		if(t->celula != '#')
			t->descoberto = 1;
		else
			t->descoberto = -1;

		if(!(b[t->tipo - 1].pecasRest))
			revelar_barco(b[t->tipo + 1], t->tipo);
			*hp_inimigo--;

		return 0;


	}


	return 1;
}

int traduzir(char ataque[21], int * ataquex ,int * ataquey){
	printf("_I_\n");
	int aux_char;
	int  i = 0, aux_int,cont;
	aux_int = -1;
	aux_char = -1;
	/*for(i=0; ataque[i]!='/0';i++){
		ataque[i] = toupper(ataque[i]);
		printf("f\n");
	}*/i = 0;
	cont = 0;
	printf("_I_\n");
	while(ataque[i] != '/0'){
		if(/*ataque[i] >= 'A' && ataque[i] <= 'L'*/ ataque[i] == 'A' || ataque[i] == 'B' || ataque[i] == 'C' || ataque[i] == 'D' || ataque[i] == 'E' || ataque[i] == 'F' || ataque[i] == 'G' || ataque[i]=='H' || ataque[i]=='I' || ataque[i]=='J' || ataque[i]=='K' || ataque[i]=='L' )
			aux_char = ((int)ataque[i]) - 65;
		else if(/*ataque[i] >= '1' && ataque[i] <= '9'*/  ataque[i] =='1' ||ataque[i] =='2' ||ataque[i] =='3' ||ataque[i] =='4' ||ataque[i] =='5' ||ataque[i] =='6' ||ataque[i] =='7' ||ataque[i] =='8' || ataque[i] =='9' ){
			cont++;
			printf("w\n");
			if(cont > 1)
				aux_int = (aux_int*10) + (int)ataque[i];
			else
				aux_int = ((int)ataque[i]);
		}
		i++;
	}
	printf("_I_\n");
	aux_int--;
	if(aux_int > -1){
		printf("_I_\n");
		*ataquex = aux_int;
		*ataquey = aux_char;
		return 0; 
	}else
		return 1;
}
