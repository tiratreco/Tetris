#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "tetris.h"
//gcc main.c -std=c99 -o main
//-lglut -lGLU -lGL
//g++ main.c -o main -lglut -lGLU -lGL
int main(){
	srand(time(NULL));
	iniciar();
	geraFigura();
	for (int i = 0; i < 1000; i++){
		descerFigura();
		Sleep(100);
		exibir();
	}
}