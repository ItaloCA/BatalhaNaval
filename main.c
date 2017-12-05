#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tabuleiroBN.h"
#include "movimentos.h"

int main(int argc, char const *argv[]){
//Variaveis	
	TAB *HUM, *COM;
	BARCO barcos_HUM[9];
	BARCO barcos_COM[9];
	int vidasHUM = 8;
	int vidasCOM = 8;
	int mira_x, mira_y, ult_alvo_x, ult_alvo_y, ult_ataque_x, ult_ataque_y, ataque_x, ataque_y;
	char ataque[21];
	int rodada = 0;
	srand(time(NULL));
//Iniciar
	criar_tabuleiro(&COM);
	criar_tabuleiro(&HUM);
	poisicionando_barcos(HUM, barcos_HUM);
	poisicionando_barcos(COM, barcos_COM);

//teste
	imprimir(HUM, COM);
	atacar(COM, 5, 5, barcos_COM, barcos_HUM, &vidasHUM, &vidasCOM);
	
//Jogo
	while(vidasHUM && vidasCOM){
		imprimir(HUM, COM);
		rodada++;
		if(rodada > 1)
			printf("Ultimos Ataques:\n   Jogador: (%d, %d)\n   Bot:     (%d, %d)\n" , ult_ataque_x, ult_ataque_y, ult_alvo_x, ult_alvo_y);		
		
		printf("Digite as coordenadas (x,y) para o ataque: ");

		scanf("%s", ataque);
/*	//nao implementado
		while(traduzir(ataque, &ataque_x, &ataque_y)){
			printf("Entrada invalida!\n");
			scanf("%s", ataque);   
		}
//*/
	
		atacar(COM, ataque_x, ataque_y, barcos_COM, barcos_HUM, &vidasHUM, &vidasCOM);


/*	//Vez do Computador

//*/
		vidasHUM -= 4; //teste
	}


	return 0;
}
