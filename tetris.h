


//base: 10 blocos
//altura: 20 blocos
#include "data.h"

bool blocoOcupado(int);

bloco campo[ALTURA][BASE];
figura figura_atual;
int pontos;


#include "visual.h"

int estado = 0;

void iniciar (){
	estado = 1;
	pontos = 0;
	for (int i=0;i<ALTURA;i++){
		for (int j=0;j<BASE;j++){
			campo[i][j].ocupado = false;
			campo[i][j].figura = false;
			campo[i][j].cor = BRANCO;
		}
	}
	preencherPontos();
	preencherFaces();
	calcularNormaisVertices();
	calcularNormaisFaces();
}

void exibir(){
	for (int i=0;i<ALTURA;i++){
		for (int j=0;j<BASE;j++){
			if(campo[i][j].ocupado) printf("%c ", 219);
			else printf("%c ", 176);
		}
		printf("        ");
		for (int j=0;j<BASE;j++){
			if(campo[i][j].figura) printf("%c ", 219);
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


bool blocoOcupado(int direcao){
	switch (direcao){
	case CIMA:
		break;
	case BAIXO:
		for (int i = 0; i < 4; i++){
			if (figura_atual.y[i]==19 || (campo[figura_atual.y[i]+1][figura_atual.x[i]].ocupado && !campo[figura_atual.y[i]+1][figura_atual.x[i]].figura)) return true;
		}
		break;
	case ESQUERDA:
		for (int i = 0; i < 4; i++){
			if (figura_atual.x[i]==0 || (campo[figura_atual.y[i]][figura_atual.x[i]-1].ocupado && !campo[figura_atual.y[i]][figura_atual.x[i]-1].figura)) return true;
		}
		break;
	case DIREITA:
		for (int i = 0; i < 4; i++){
			if (figura_atual.x[i]==9 || (campo[figura_atual.y[i]][figura_atual.x[i]+1].ocupado && !campo[figura_atual.y[i]][figura_atual.x[i]+1].figura)) return true;
		}
		break;
	default:
		break;
	}
	return false;
}

void mover(int direcao){
	printf("%d", direcao);
	if (blocoOcupado(direcao)) return;
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
			printf("esquerda");
		}
		break;
	case DIREITA:
		for (int i = 0; i < 4; i++){
			figura_atual.x[i]++;
			printf("DIREITA");
		}
		break;
	default:
		printf("default");
		break;
	}
}

void rotacionar(){
	int x_pivo = figura_atual.x[1];
	int y_pivo = figura_atual.y[1];
	int x_des, y_des;
	switch(figura_atual.tipo){
	case QUADRADO:
		break;
	case LINHA:
		for (int i = 0; i < 4; i++){
			int aux = figura_atual.y[i];
			figura_atual.y[i]=figura_atual.x[i];
			figura_atual.x[i]=aux;
		}
		x_des = figura_atual.x[1] - x_pivo;
		y_des = figura_atual.y[1] - y_pivo;
		for(int i = 0; i < 4; i++){{
			figura_atual.y[i]-=x_des;
			figura_atual.x[i]-=y_des;
		}
		break;
	default:
		break;
	}
}


void fixaFigura(){
	for (int i = 0; i < 4; i++){
		campo[figura_atual.y[i]][figura_atual.x[i]].ocupado = true;
		campo[figura_atual.y[i]][figura_atual.x[i]].figura = false;
		campo[figura_atual.y[i]][figura_atual.x[i]].cor = figura_atual.cor;
	};
}

void geraFigura(){
	//int n = rand()%7;
	inserirFigura(LINHA); 
}

int tiraLinhas(){
	int pontos = 0;
	for (int i=0;i<ALTURA;i++) {
		bool apagar = true;
		for (int j=0;j<BASE;j++) {
			if (!campo[i][j].ocupado || campo[i][j].figura){//certo?
				apagar = false;
				break;
			}
		}
		if (apagar){
			pontos++;
			for (int j=0;j<BASE;j++) {
				campo[i][j].ocupado = false;
			}
			for (int k=i;k>0;k--) for (int j=0;j<BASE;j++) {//FALTA COPIAR COR
				if (campo[k-1][j].ocupado){
					campo[k-1][j].ocupado = false;
					campo[k][j].ocupado = true;
				}
			}
			i--;
		}
	}
	return pontos;
}

void descerFigura(){
	if(blocoOcupado(BAIXO)){
		fixaFigura();
		pontos += tiraLinhas();
		geraFigura();
	}else{
		mover(BAIXO);
	}
	atualizarFigura();
}

void jogo(){
	if (estado==0) {
		iniciar();
		geraFigura();
		return;
	}
	descerFigura();
	//Sleep(1000);
	exibir();
	
}