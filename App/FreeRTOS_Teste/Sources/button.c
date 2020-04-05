#include "gpio_x.h"

static uint8_t buttonState = 0;

void bInit(){
	PORTB_CLK(); //Ativa o clock gate da PORTB
	PORTB_Mode(0, INPUT); //Configura PTB0 como Input
	PORTB_PULLUP(0); //Ativa o PullUP
}
uint8_t bRead(){
	return buttonState;
}

void bDebounce(){
	static uint8_t tempo = 42;
	static uint8_t anterior = 0;
	static uint8_t atual = 0;

	anterior = atual;

	if(!PORTB_Read(0)){ //Bot�o ativo por Zero (PullUP)
		atual = 1;
	}
	else{
		atual = 0;
	}

	if (atual == anterior){ //Checa a estabiliza��o da porta
		tempo --;
	}
	else{
		anterior = atual;
		tempo = 42;
	}

	if (tempo == 0){ //Aguarda a estabiliza��o durante 42 execu��es da fun��o
		buttonState = atual;
		tempo = 12;
	}
}
