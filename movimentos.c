#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tabuleiroBN.h"


void revelar_barco(BARCO embarcacao, int tipo){
	int i;
	printf("\nREVELANDO\n\n");
	printf("%d %c %d %c\n", embarcacao.pecasRest, embarcacao.direcao, (embarcacao.proa)->tipo, (embarcacao.proa)->celula);
	TAB * proa = embarcacao.proa;
	if(embarcacao.direcao == 'c'){
		if(tipo <= 6){
			
		}
		else if(tipo <= 8){
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
			
		}
		else if(tipo <= 8){
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
			
		}
		else if(tipo <= 8){
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
			
		}
		else if(tipo <= 8){
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



int atacar(TAB *t, int x, int y, BARCO *b, BARCO *frota, int* vidas, int* hp_inimigo, int COMatacando){
	int i;

	for (i = 0; i < y; i++){
		t = t->dir;
	}
	for (i = 0; i < x; i++){
		t = t->baixo;
	}	

	if(t->descoberto != -1 && (t->descoberto != 1 || COMatacando)){


		if(t->tipo < 4){

			if(!COMatacando || t->tipo == 0)
				t->descoberto = 1;
			else
				t->descoberto = -1;
			if(t->tipo)
				(b[(t->tipo) - 1]).pecasRest -= 1;

			if(t->tipo == 1){   //Caso JANGADA. Pode ser 1 tambem, sujeito a  mudanca
				if((frota[1]).pecasRest){
					(frota[1]).pecasRest = 0;
					if(!COMatacando)
						((frota[1]).proa)->descoberto = -1;
					else
						((frota[1]).proa)->descoberto = 1;
				}
				else {
					(frota[2]).pecasRest = 0;
					if(!COMatacando)
						((frota[2]).proa)->descoberto = -1;
					else
						((frota[2]).proa)->descoberto = 1;
				}
				*vidas--;
			}else                //Caso SUBMARINO
				*hp_inimigo--;

			return 0;
		}

		//OUTROS CASOS
		b[t->tipo - 1].pecasRest--;
		if(t->celula != '#' && !COMatacando)
			t->descoberto = 1;
		else
			t->descoberto = -1;

		if(b[t->tipo - 1].pecasRest < 1)
			if(!COMatacando)
				revelar_barco(b[t->tipo - 1], t->tipo);
			*hp_inimigo--;

		return 0;


	}


	return 1;
}
//*
int atacarComp(TAB *t, BARCO *frota, BARCO *b, int* hp_inimigo, int* vidas, int *x, int *y, int *busca, int *alvo, int *passo, int *atacProa){
	
	//Parametros
	TAB *tabu = t;
	BARCO *meus_barc = frota;
	BARCO *inim_barc = b;
	int *vid_hi = hp_inimigo;
	int *vid_mi = vidas;
	int i;


	if(!(*busca)){
		//Jogada rand utilizando a funcao atacar
		*x = rand()%12;
		*y = rand()%12;

		atacar(tabu, *x, *y, inim_barc, meus_barc, vid_mi, vid_hi, 1);
		
		for (i = 0; i < *y; i++){
			t = t->dir;
		}
		for (i = 0; i < *x; i++){
			t = t->baixo;
		}

		if(t->celula != 'O'){
			if(b[t->tipo - 1].pecasRest != 0){
				*busca = 1;
				*alvo = t->tipo - 1;
			}
		}	
		return 0;
	}else{ //BUSCA
		
		//Indo para a posicao da jogada anterior
		for (i = 0; i < *y; i++){
			t = t->dir;
		}
		for (i = 0; i < *x; i++){
			t = t->baixo;
		}

		//SISTEMA DE BUSCA

		if(t->celula == '#'){
			*alvo = t->tipo - 1;
			if(*passo == 0){
			//PASSO ZERO
				if(t->cima != NULL){
					atacar(tabu, *x-1, *y, inim_barc, meus_barc, vid_mi, vid_hi, 1);
					*x--;
					if(t->celula == '#' && t->tipo - 1 == *alvo){
						return 0;
					}else{
						*passo++;
						return 0;
					}

				}else{
					atacar(tabu, *x, *y+1, inim_barc, meus_barc, vid_mi, vid_hi, 1);
					*y++;
					return 0;
				}
			}else if(*passo == 1){
			//PASSO UM
				atacar(tabu, *x+1, *y+1, inim_barc, meus_barc, vid_mi, vid_hi, 1);
				*x++;
				*y++;
				if(t->celula == '#' && t->tipo - 1 == *alvo){
						return 0;
					}else{
						*passo++;
						return 0;
					}
			}else if(*passo == 1){
			//PASSO DOIS
				atacar(tabu, *x+1, *y-1, inim_barc, meus_barc, vid_mi, vid_hi, 1);
				*x++;
				*y--;
				if(t->celula == '#' && t->tipo - 1 == *alvo){
						return 0;
					}else{
						*passo++;
						return 0;
					}
			}
			else if(*passo == 1){
			//PASSO TRES
				atacar(tabu, *x-1, *y-1, inim_barc, meus_barc, vid_mi, vid_hi, 1);
				*x--;
				*y--;
				if(t->celula == '#' && t->tipo - 1 == *alvo){
						return 0;
					}else{
						*passo++;
						return 0;
					}
			}
		}else if(t->celula == '^' || *atacProa == 1){
			//SE ACHAR UMA PROA CIMA, DIRECAO BAIXO
			while((t->baixo)->descoberto == -1 && (t->baixo)->celula != 'v'){
				*x++;
			}
			atacar(tabu, *x+1, *y, inim_barc, meus_barc, vid_mi, vid_hi, 1);
			*x++;
			if(b[t->tipo - 1].pecasRest != 0){
				*busca = 1;
				*atacProa = 1;
				return 0;
			}else{
				*busca = 0;
				*alvo = 0;
				*atacProa = 0;
				return 0;
			}
		}else if(t->celula == 'v'){
			//SE ACHAR UMA PROA BAIXO
			while((t->cima)->descoberto == -1 && (t->cima)->celula != '^'){
				*x--;
			}
			atacar(tabu, *x-1, *y, inim_barc, meus_barc, vid_mi, vid_hi, 1);
			*x--;
			if(b[t->tipo - 1].pecasRest != 0){
				*busca = 1;
				*atacProa = 1;
				return 0;
			}else{
				*busca = 0;
				*alvo = 0;
				*atacProa = 0;
				return 0;
			}
		}else if(t->celula == '<'){
			//SE ACHAR UMA PROA ESQUERDA
			while((t->dir)->descoberto == -1 && (t->dir)->celula != '>'){
				*y++;
			}
			atacar(tabu, *x, *y+1, inim_barc, meus_barc, vid_mi, vid_hi, 1);
			*y++;
			if(b[t->tipo - 1].pecasRest != 0){
				*busca = 1;
				*atacProa = 1;
				return 0;
			}else{
				*busca = 0;
				*alvo = 0;
				*atacProa = 0;
				return 0;
			}
		}else if(t->celula == '>'){
			//SE ACHAR UMA PROA DIREITA
			while((t->esq)->descoberto == -1 && (t->esq)->celula != '<'){
				*y--;
			}
			atacar(tabu, *x, *y-1, inim_barc, meus_barc, vid_mi, vid_hi, 1);
			*y--;
			if(b[t->tipo - 1].pecasRest != 0){
				*busca = 1;
				*atacProa = 1;
				return 0;
			}else{
				*busca = 0;
				*alvo = 0;
				*atacProa = 0;
				return 0;
			}
		}
	}
}
//*/
int traduzir(char ataque_o[21], int * ataquex ,int * ataquey){

	int aux_char;
	int  i = 0, aux_int,cont;
	char ataque[21];
	strcpy(ataque, ataque_o);
	aux_int = -1;
	aux_char = -1;
	
	for (i = 0; i < 21; i++){
		if(ataque[i] >= 'a' && ataque[i]<= 'l')
			ataque[i] = ataque_o[i] - 32;
	}

	i = 0;
	cont = 0;

	while(ataque[i] != '\0'){

		if(ataque[i] >= 'A' && ataque[i] <= 'L')
			aux_char = ((int)ataque[i]) - 65;
		else if(ataque[i] >= '0' && ataque[i] <= '9' ){
			cont++;

			if(cont > 1 && aux_int == 1)
				aux_int = (aux_int*10) + ((int)ataque[i] - 48);
			else
				aux_int = ((int)ataque[i]) - 48;
		}
		i++;
	}
	aux_int--;

	if(aux_int > -1 && aux_char > -1){
		*ataquex = aux_int;
		*ataquey = aux_char;
		if(*ataquex < 12 && *ataquey < 12)
			return 0;

	}

	return 1;
}