#define MENU 0
#define INICIANDO 1
#define EM_JOGO 2
#define FIM 3



#define PRETO 0
#define VERMELHO 1
#define AZUL 2
#define VERDE 3
#define BRANCO 4
#define AMARELO 5
#define LARANJA 6
#define CIANO 7
#define ROXO 8
#define ESCURO 9//deve ser sempre o ultimo

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


const GLfloat cores[ESCURO*2][3] = {
	{0.0, 0.0, 0.0 }, //preto
	{1.0, 0.0, 0.0 }, //vermelho
	{0.0, 0.0, 1.0 }, //azul
	{0.0, 1.0, 0.0 }, //verde
	{1.0, 1.0, 1.0 }, //branco
	{1.0, 1.0, 0.0 }, //amarelo
	{1.0, 0.7, 0.0 }, //laranja
	{0.0, 1.0, 1.0 }, //ciano
	{1.0, 0.0, 1.0 }, //roxo
		//escuros:
	{0.0, 0.0, 0.0 }, //preto
	{0.4, 0.0, 0.0 }, //vermelho
	{0.0, 0.0, 0.4 }, //azul
	{0.0, 0.4, 0.0 }, //verde
	{0.4, 0.4, 0.5 }, //branco
	{0.4, 0.4, 0.0 }, //amarelo
	{0.5, 0.3, 0.0 }, //laranja
	{0.0, 0.4, 0.4 }, //ciano
	{0.4, 0.0, 0.4 } //roxo
};

figura figuras[7] = {
    {{4, 5, 4, 5},{0, 0, 1, 1}, QUADRADO, AMARELO},
    {{3, 4, 5, 6},{1, 1, 1, 1}, LINHA, CIANO},
    {{3, 3, 4, 5},{0, 1, 1, 1}, LESQUERDA, AZUL},
    {{4, 5, 6, 6},{1, 1, 1, 0}, LDIREITA, LARANJA},
    {{4, 5, 5, 6},{1, 1, 0, 0}, EESQUERDA, VERMELHO},
    {{3, 4, 4, 5},{0, 0, 1, 1}, EDIREITA, VERDE},
    {{3, 4, 4, 5},{1, 1, 0, 1}, PIRAMIDE, ROXO}
};
