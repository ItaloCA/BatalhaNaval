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
	int ult_alvo_x, ult_alvo_y, ult_ataque_x, ult_ataque_y, ataque_x, ataque_y;
	char ataque[21];
	int rodada = 0, entrada;
	srand(time(NULL));
//Iniciar
	criar_tabuleiro(&COM);
	criar_tabuleiro(&HUM);
	poisicionando_barcos(HUM, barcos_HUM, 1);
	poisicionando_barcos(COM, barcos_COM, 0);

//Jogo

	int x;
	int y;

	int busca;
	int alvo;
	int atacProa;
	int passo;
	

	while(vidasHUM && vidasCOM){
		imprimir(HUM, COM);
		rodada++;
		if(rodada > 1)
			printf("Ultimos Ataques:\n   Jogador: (%d, %c)\n   Bot:     (%d, %c)\n" , ult_ataque_x + 1, (char)ult_ataque_y + 65, x + 1, (char)y+65);		
		
		printf("Digite as coordenadas (x,y) para o ataque: ");

		entrada = 2;
		while(entrada){	
			if(entrada == 1)
				printf("Celula ja foi atacada\n");
			gets(ataque);
	
			while(traduzir(ataque, &ataque_x, &ataque_y)){
				printf("Entrada invalida!\n");
				gets(ataque);   
			}

			entrada = atacar(COM, ataque_x, ataque_y, barcos_COM, barcos_HUM, &vidasHUM, &vidasCOM, 0);
		}

	    //Vez do Computador
		atacarComp(HUM, barcos_COM, barcos_HUM, &vidasHUM, &vidasCOM, &x, &y, &busca, &alvo, &passo, &atacProa);
	
		ult_ataque_x = ataque_x;
		ult_ataque_y = ataque_y;

	}

	imprimir(HUM, COM);
	printf("Ultimos Ataques:\n   Jogador: (%d, %c)\n   Bot:     (%d, %c)\n" , ult_ataque_x + 1, (char)ult_ataque_y + 65, x + 1, (char)y+65);

// QUEM VENCEU E SE QUER JOGAR DENOVO...

	return 0;
}

