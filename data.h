
#define PRETO 1
#define VERMELHO 2
#define AZUL 3
#define VERDE 4
#define BRANCO 5

#define QUADRADO 0
#define LINHA 1
#define LESQUERDA 2
#define LDIREITA 3
#define EESQUERDA 4
#define EDIREITA 5
#define PIRAMIDE 6

#define DIREITA 1
#define ESQUERDA 2
#define CIMA 3
#define BAIXO 4

#define BASE 10
#define ALTURA 20


//base: 10 blocos
//altura: 20 blocos

typedef struct bloco{
	GLfloat	pontos[8][3];
	GLfloat	vertex_normals[8][3];
	GLfloat face_normals[12][3];
	GLuint faces[12][3];
	bool ocupado;
	bool figura;
	int cor;
}bloco;

typedef struct figura{
	int x[4];
	int y[4];
	int tipo;
	int cor;
}figura;


const float cores[5][3] = {
	{0.0, 0.0, 0.0 }, //preto
	{1.0, 0.0, 0.0 }, //vermelho
	{0.0, 0.0, 1.0 }, //azul
	{0.0, 1.0, 0.0 }, //verde
	{1.0, 1.0, 1.0 }  //branco
};

figura figuras[7] = {
    {{4, 5, 4, 5},{0, 0, 1, 1}, QUADRADO, PRETO},
    {{3, 4, 5, 6},{1, 1, 1, 1}, LINHA, PRETO},
    {{3, 3, 4, 5},{0, 1, 1, 1}, LESQUERDA, PRETO},
    {{4, 5, 6, 6},{1, 1, 1, 0}, LDIREITA, PRETO},
    {{4, 5, 5, 6},{1, 1, 0, 0}, EESQUERDA, PRETO},
    {{3, 4, 4, 5},{0, 0, 1, 1}, EDIREITA, PRETO},
    {{3, 4, 4, 5},{1, 1, 0, 1}, PIRAMIDE, PRETO}
};

