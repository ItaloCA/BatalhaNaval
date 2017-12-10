#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tabuleiroBN.h"

void revelar_barco(BARCO embarcacao, int tipo){
	/*
	Função:
		-revelar_barco()
	Parametros:
		-struct barco a ser revelado
		-inteiro tipo do barco
	Descrição:
		-Define descoberto para 1 de cada casa ocupada pelo barco.
		Começa pela proa marcada na struct barco, segue a direçao
		marcada definindo descoberto para 1
*/
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
	/*
	Função:
		-atacar()
	Parametros:
		-ponteiro para a struct tabuleiro TAB*
		-inteiro linha x 
		-inteiro coluna y
		-vetor de barcos do inimigo BARCO* b
		-vetor dos próprios barcos BARCO* frota
		-inteiro vidas do atacante vidas passado por parametro
		-inteiro vidas do inimigo hp_inimigo passado por parametro
		-inteiro que indica se o atacante é humano ou maquina 
	Descrição:
		-Move o ponteiro t para a posição a ser atacada,
		se a casa nao for um barco atingido parcialmente [*]
		e o computador esta atacando ou é uma celula nao ata-
		cada pelo humano ataca a celula, modificando as vari-
		áveis descoberto, as peças restantes do barco e a vi-
		da do inimigo (se um barco for acertado) e vida do a-
		tacante se ele acertar a jangada.
*/
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

			if(t->tipo == 1){
				//Caso JANGADA. Pode ser 1 tambem, sujeito a  mudanca
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
			}else
				//Caso SUBMARINO
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

int atacarComp(TAB *t, BARCO *frota, BARCO *b, int* hp_inimigo, int* vidas, int *x, int *y, int *busca, int *alvo, int *passo, int *atacProa){
	/*
	Função:
		-atacarComp()
	Recebe como parâmetros:
		-TAB *t: Tabuleiro
		-BARCO *frota: Barcos do inimigo
		-BARCO *b: Seus barcos
		-hp_inimigo: Vidas do inimigo
		-vidas: Suas vidas
		-x, y: Coordenadas do último ataque
		-busca: Binário se estamos procurando um barco que atingimos ou não
		-alvo: Barco a qual estamos procurando
		-passo: Número do passo que estamos no Sistema de Passos
		-atacProa: Binário de quando atacamos uma proa
	Descrição: 
		-A função realiza os ataques do computador.
		Primeiramente atacamos em randon, ate que encontremos
		um pedaço de barco(<,#,>,@,&). Ao encontrarmos, iniciamos sua busca
		utilizando do Sistema de Passos e ao destruirmos, por completo,
		retornamos às jogadas em randon.
	*/

	//Parametros
	TAB *tabu = t;
	BARCO *meus_barc = frota;
	BARCO *inim_barc = b;
	int *vid_hi = hp_inimigo;
	int *vid_mi = vidas;


	if(!(*busca)){
		//Jogada rand utilizando a função atacar
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
	}else{
		//BUSCA
		
		//Indo para a posição da jogada anterior
		for (i = 0; i < *y; i++){
			t = t->dir;
		}
		for (i = 0; i < *x; i++){
			t = t->baixo;
		}

		//SISTEMA DE PASSOS

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
			}else if(*passo == 2){
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
			else if(*passo == 3){
			//PASSO TRÊS
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
			//SE ACHAR UMA PROA PRA CIMA: DIREÇÃO BAIXO
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
			//SE ACHAR UMA PROA PRA BAIXO: DIREÇÃO CIMA
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
			//SE ACHAR UMA PROA PRA ESQUERDA: DIREÇÃO DIREITA
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
			//SE ACHAR UMA PROA PRA DIREITA: DIREÇÃO ESQUERDA
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

int traduzir(char ataque_o[21], int * ataquex ,int * ataquey){
	/*
	Função
		-traduzir()
	Parâmetros:
		-Cadeia de caracteres da entrada.
		-Inteiro passado como parametro ataquex que receberá o numero da linha.
		-Inteiro passado como parametro ataquex que receberá o numero da coluna.
	Descrição:
		-Recebe a string entrada pelo jogador
		e traduz para a maquina, retirando os va-
		lores para a linha e coluna que deverão
		ser atacados.
	*/

	int aux_char;				// representa a coluna.
	int  i = 0, aux_int,cont;	// indice i para laço; aux_int representa a linha; cont que conta os algarismos encontrados.
	char ataque[21];			// string copia.
	strcpy(ataque, ataque_o);	
	aux_int = -1;
	aux_char = -1;
	
	// Laço que torna as letras, que representam colunas, em maiúsculas.
	for (i = 0; i < 21; i++){
		if(ataque[i] >= 'a' && ataque[i]<= 'l')
			ataque[i] = ataque_o[i] - 32;
	}

	i = 0;
	cont = 0;

	// Laço que procura letras e atribui um inteiro correspondente a coluna aux_char e os numeros a linha aux_int.
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

	// Se a entrada foi reconhecida e traduzida atribui as coordenadas (x,y) em ataquex e ataquey. 
	if(aux_int > -1 && aux_char > -1){
		*ataquex = aux_int;
		*ataquey = aux_char;
		if(*ataquex < 12 && *ataquey < 12)
			return 0;

	}
	// Se não foi possivel traduzir a entrada ou se foi inválida, retorna erro.
	return 1;
}