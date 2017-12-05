#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

int traduzir(char * ataque[5], int * ataquex ,int * ataquey){
	char aux;
	int  i = 0, aux;
	for(i=0; ataque[i]!='/0';i++)
		ataque[i] = toupper(ataque[i]);
	while(ataque[i]!= '/0'){
		if(ataque[i]=='A' || ataque[i]=='B' || ataque[i]=='C' || ataque[i]=='D' || ataque[i]=='E' ||ataque[i]=='L' || ataque[i]=='G' || ataque[i]=='H' || ataque[i]=='I' || ataque[i]=='J' || ataque[i]=='K' || ataque[i]=='L' )
			aux = ataque[i];
		else if(ataque[i] =='1' ||ataque[i] =='2' ||ataque[i] =='3' ||ataque[i] =='4' ||ataque[i] =='5' ||ataque[i] =='6' ||ataque[i] =='7' ||ataque[i] =='8' || ataque[i] =='9' ){
			
		}
	}



}
