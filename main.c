#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tabuleiroBN.h"
#include "movimentos.h"

int main(int argc, char const *argv[]){
	//Variaveis	
	TAB *HUM, *COM;			// ponteiros para a primeira posiçao dos dois tabuleiros.
	BARCO barcos_HUM[9];	// vetor de embarcaçoes do Jogador.
	BARCO barcos_COM[9];	// vetor de enbarcaçoes do Computador.
	int vidasHUM = 8;
	int vidasCOM = 8;
	int jogar = 1;
	int ult_ataque_x, ult_ataque_y, ataque_x, ataque_y, c;
	char entrada[21];		//cadeia de caracteres que armazena a entrada do teclado.
	int rodada = 0, ataque;//contador de rodadas; variavel que verifica a validade da entrada.
	srand(time(NULL));		//define a seed da funçao rand() como sendo o relogio.
	//Iniciar Tabuleiro
	criar_tabuleiro(&COM);
	criar_tabuleiro(&HUM);
	poisicionando_barcos(HUM, barcos_HUM, 1);
	poisicionando_barcos(COM, barcos_COM, 0);

	//Jogo

	//Variaveis para a função atacarComp()
	int x;
	int y;
	int busca;
	int alvo;
	int atacProa;
	int passo;
	typedef struct secondAlvos{
		int alvo;
		int x;
		int y;
	}SA;
	
	while(jogar){
		while(vidasHUM && vidasCOM){
			imprimir(HUM, COM);
			rodada++;
			if(rodada > 1)        // A partir da segunda rodada exibe as coordenadas dos ultimos ataques
				printf("Ultimos Ataques:\n   Jogador: (%d, %c)\n   Bot:     (%d, %c)\n" , ult_ataque_x + 1, (char)ult_ataque_y + 65, x + 1, (char)y+65);		
			
			// Vez do jogador	
			printf("Digite as coordenadas (x,y) para o ataque: ");

			//laço que repete ate que o jogador entre coordenadas que nao foram atacadas
			ataque = 2;         // Se entrada = 1, a casa ja foi atacada, se entrada = 0 a casa em (x, y) pode ser atacada
			while(ataque){	
				if(ataque == 1)
					printf("Casa ja foi atacada, escolha outras coordenadas\n");
				gets(entrada);
				//Laço que repete ate que o jogador digite coordenadas validas
				while(traduzir(entrada, &ataque_x, &ataque_y)){
					printf("Entrada invalida!\n");
					gets(entrada);   
				}
				//Ataque do jogador
				ataque = atacar(COM, ataque_x, ataque_y, barcos_COM, barcos_HUM, &vidasHUM, &vidasCOM, 0);
			}

		    //Vez do Computador
			atacarComp(HUM, barcos_COM, barcos_HUM, &vidasHUM, &vidasCOM, &x, &y, &busca, &alvo, &passo, &atacProa);
		
			ult_ataque_x = ataque_x;
			ult_ataque_y = ataque_y;

		}

	//Vencedor e se quer jogar novamente
		imprimir(HUM, COM);
		printf("Ultimos Ataques:\n   Jogador: (%d, %c)\n   Bot:     (%d, %c)\n" , ult_ataque_x + 1, (char)ult_ataque_y + 65, x + 1, (char)y+65);
		if(vidasHUM)
			printf("\n---------- VOCÊ VENCEU! ----------\n\n");

		printf("Deseja jogar novamente? (Y/N)\n");
		scanf("%d" , &entrada);
		jogar = 0;
		for (c = 0; entrada[c] != '\0'; c++){
			if(entrada[c] == 'Y' || entrada[c] == 'y' || entrada[c] == 's' || entrada[c] == 'S')
				jogar = 1;
		}

	}

	return 0;
}