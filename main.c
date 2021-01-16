#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include "tetris.h"
//gcc main.c -std=c99 -o main 
//-lglut -lGLU -lGL
//g++ main.c -o main -lglut -lGLU -lGL
int main(){
	srand(time(NULL));
	iniciar();
	inserirFigura(PIRAMIDE);
	atualizarFigura();
	exibir();
	mover(BAIXO);
	atualizarFigura();
	exibir();
	mover(ESQUERDA);
	atualizarFigura();
	exibir();
	mover(DIREITA);
	atualizarFigura();
	exibir();
	mover(CIMA);
	atualizarFigura();
	exibir();
}