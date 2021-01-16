


//base: 10 blocos
//altura: 20 blocos
#include "data.h"

bloco campo[ALTURA][BASE];
figura figura_atual;

void iniciar (){
	for (int i=0;i<ALTURA;i++){
		for (int j=0;j<BASE;j++){
			campo[i][j].ocupado = false;
			campo[i][j].figura = false;
			campo[i][j].cor = BRANCO;
		}
	}
}

void exibir(){
	for (int i=0;i<ALTURA;i++){
		for (int j=0;j<BASE;j++){
			if(campo[i][j].ocupado) printf("%c ", 219);
			else printf("%c ", 176);
		}
		printf("\n");
	}
	printf("\n\n\n\n\n");
}

void atualizarFigura(){
	for (int i=0;i<ALTURA;i++) for (int j=0;j<BASE;j++) if (campo[i][j].figura == true){
		campo[i][j].ocupado = false;
		campo[i][j].figura = false;
		campo[i][j].cor = BRANCO;
	}
	for (int i=0;i<4;i++){
		campo[figura_atual.y[i]][figura_atual.x[i]].ocupado = true;
		campo[figura_atual.y[i]][figura_atual.x[i]].figura = true;
	}
}

void inserirFigura(int id){
	for (int i=0;i<4;i++){
		figura_atual.x[i] = figuras[id].x[i];
		figura_atual.y[i] = figuras[id].y[i];
	}
	figura_atual.cor = figuras[id].cor;
	figura_atual.tipo = figuras[id].tipo;
}

void mover(int direcao){
	switch (direcao){
	case CIMA:
		for (int i = 0; i < 4; i++){
			figura_atual.y[i]--;
		}
		break;
	case BAIXO:
		for (int i = 0; i < 4; i++){
			figura_atual.y[i]++;
		}
		break;
	case ESQUERDA:
		for (int i = 0; i < 4; i++){
			figura_atual.x[i]--;
		}
		break;
	case DIREITA:
		for (int i = 0; i < 4; i++){
			figura_atual.x[i]++;
		}
		break;
	default:
		break;
	}
}

bool blocoOcupado(int direcao){
	switch (direcao){
	case CIMA:
		break;
	case BAIXO:
		for (int i = 0; i < 4; i++){
			if (figura_atual.y[i]==19) return true;//toca o fundo
			if (campo[figura_atual.y[i]+1][figura_atual.x[i]].ocupado) return true;//toca uma peca
		}
		break;
	case ESQUERDA:
		for (int i = 0; i < 4; i++){
			if (figura_atual.y[i]==0) return true;//toca a lateral
			if (campo[figura_atual.y[i]][figura_atual.x[i]-1].ocupado) return true;//toca uma peca
		}
		break;
	case DIREITA:
		for (int i = 0; i < 4; i++){
			if (figura_atual.y[i]==9) return true;//toca a lateral
			if (campo[figura_atual.y[i]][figura_atual.x[i]+1].ocupado) return true;//toca uma peca
		}
		break;
	default:
		break;
	}
	return false;
}

void fixaFigura(){
	for (int i = 0; i < 4; i++){
		campo[figura_atual.y[i]][figura_atual.x[i]].ocupado = true;
		campo[figura_atual.y[i]][figura_atual.x[i]].figura = false;
		campo[figura_atual.y[i]][figura_atual.x[i]].cor = figura_atual.cor;
	};
}

void geraFigura(){
	inserirFigura(rand()%7); 
}

void descerFigura(){
	mover(BAIXO);
	if(blocoOcupado(BAIXO)){
		fixaFigura();
	}
	geraFigura();
}