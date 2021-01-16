// #define Z_FUNDO -20
// #define Z_FRENTE -19
// 
// typedef struct cubo{
// 	GLfloat	pontos[8][3];
// 	GLuint faces[12][3];
// 	bool figura;
// 	cubo *prox;
// }cubo;
// 
// cubo *cubos = NULL;
// int num_cubos = 0;
// 
// cubo pushCubo (bool figura){
// 	cubo cub = (cubo*)malloc(sizeof(cubo));
// 	cub->figura = figura;
// 	cub->prox = cubos;
// 	cubos = cub;
// 	num_cubos++;
// 	return cub;
// }
// 
// void popCubos (cubo *cub){
// 	if (cubos==NULL) return;
// 	if (cub == cubos){
// 		cubos = cub->prox;
// 		free(cub);
// 		num_cubos--;
// 		return;
// 	}
// 	ponto *anterior = cuboAnterior(cubo* cub);
// 	anterior->prox = cub->prox;
// 	free(cub);
// 	num_cubos--;
// }
// 
// ponto* cuboAnterior(cubo* cub){
// 	cubo *atual = cubos;
// 	cubo *anterior = NULL;
// 	while (atual!=NULL){
// 		if (atual==cub) return anterior;
// 		anterior = atual;
// 		atual = atual->prox;
// 	}
// 	return NULL;
// }
// 
// ponto* addPontos ()
// 
// void adicionarPontosFigura(){
// 	for (int i=0;i<4;i++){
// 		pushPonto(true, figura_atual.y, figura_atual.x, Z_FUNDO);
// 		pushPonto(true, figura_atual.y, figura_atual.x+1, Z_FUNDO);
// 		pushPonto(true, figura_atual.y+1, figura_atual.x+1, Z_FUNDO);
// 		pushPonto(true, figura_atual.y+1, figura_atual.x, Z_FUNDO);
// 		pushPonto(true, figura_atual.y, figura_atual.x, Z_FRENTE);
// 		pushPonto(true, figura_atual.y, figura_atual.x+1, Z_FRENTE);
// 		pushPonto(true, figura_atual.y+1, figura_atual.x+1, Z_FRENTE);
// 		pushPonto(true, figura_atual.y+1, figura_atual.x, Z_FRENTE);
// 	}
// }
// 
// void removePontosFigura(){
// 	ponto *atual = pontos;
// 	while (atual!=NULL){
// 		if (atual->figura){
// 			popPonto(atual);
// 			atual = pontos;
// 		}
// 		else atual = atual->prox;
// 	}
// }
// 
// GLuint faces[N_FACES][3] = {
	//fundo
//     {0, 2, 1},	
//     {0, 3, 2},
//     	
	//frente	
//     {0, 3, 7},
// 	{0,7,4},
// 			
	//direita
// 	{3,2,6},
// 	{3,6,7},
// 			
	//esquerda
// 	{0,4,5},
// 	{0,5,1},
// 			
	//cima
// 	{4,7,6},
// 	{4,6,5},	
// 		
	//atrás
// 	{1,2,6},
// 	{1,6,5}
// };
// 