#include <math.h>


#define Z_FUNDO -20
#define Z_FRENTE -19

struct ponto{
    float x;
    float y;
    float z;
};
  

void preencherPontos(){
	for (int i=0;i<ALTURA;i++){
		for (int j=0;j<BASE;j++){
			campo[i][j].pontos[0][0] = i;
			campo[i][j].pontos[0][1] = j;
			campo[i][j].pontos[0][2] = Z_FUNDO;
			campo[i][j].pontos[1][0] = i;
			campo[i][j].pontos[1][1] = j;
			campo[i][j].pontos[1][2] = Z_FRENTE;
			campo[i][j].pontos[2][0] = i+1;
			campo[i][j].pontos[2][1] = j;
			campo[i][j].pontos[2][2] = Z_FRENTE;
			campo[i][j].pontos[3][0] = i+1;
			campo[i][j].pontos[3][1] = j;
			campo[i][j].pontos[3][2] = Z_FUNDO;
			campo[i][j].pontos[4][0] = i;
			campo[i][j].pontos[4][1] = j+1;
			campo[i][j].pontos[4][2] = Z_FUNDO;
			campo[i][j].pontos[5][0] = i;
			campo[i][j].pontos[5][1] = j+1;
			campo[i][j].pontos[5][2] = Z_FRENTE;
			campo[i][j].pontos[6][0] = i+1;
			campo[i][j].pontos[6][1] = j+1;
			campo[i][j].pontos[6][2] = Z_FRENTE;
			campo[i][j].pontos[7][0] = i+1;
			campo[i][j].pontos[7][1] = j+1;
			campo[i][j].pontos[7][2] = Z_FUNDO;
		}
	}
}

void preencherFaces(){
	for (int i=0;i<ALTURA;i++){
		for (int j=0;j<BASE;j++){
			campo[i][j].faces[0][0] = 0;
			campo[i][j].faces[0][1] = 2;
			campo[i][j].faces[0][2] = 1;
			campo[i][j].faces[1][0] = 0;
			campo[i][j].faces[1][1] = 3;
			campo[i][j].faces[1][2] = 2;
			campo[i][j].faces[2][0] = 0;
			campo[i][j].faces[2][1] = 3;
			campo[i][j].faces[2][2] = 7;
			campo[i][j].faces[3][0] = 0;
			campo[i][j].faces[3][1] = 7;
			campo[i][j].faces[3][2] = 4;
			campo[i][j].faces[4][0] = 3;
			campo[i][j].faces[4][1] = 2;
			campo[i][j].faces[4][2] = 6;
			campo[i][j].faces[5][0] = 3;
			campo[i][j].faces[5][1] = 6;
			campo[i][j].faces[5][2] = 7;
			campo[i][j].faces[6][0] = 0;
			campo[i][j].faces[6][1] = 4;
			campo[i][j].faces[6][2] = 5;
			campo[i][j].faces[7][0] = 0;
			campo[i][j].faces[7][1] = 5;
			campo[i][j].faces[7][2] = 1;
			campo[i][j].faces[8][0] = 4;
			campo[i][j].faces[8][1] = 7;
			campo[i][j].faces[8][2] = 6;
			campo[i][j].faces[9][0] = 4;
			campo[i][j].faces[9][1] = 6;
			campo[i][j].faces[9][2] = 5;
			campo[i][j].faces[10][0] = 1;
			campo[i][j].faces[10][1] = 2;
			campo[i][j].faces[10][2] = 6;
			campo[i][j].faces[11][0] = 1;
			campo[i][j].faces[11][1] = 6;
			campo[i][j].faces[11][2] = 5;
		}
	}
}

void normalizar(ponto * n){
	GLfloat length;
	
	length = (GLfloat) sqrt((n->x * n->x) + (n->y * n->y) + (n->z * n->z));
		
	if (length == 0.0f)
		length =  1.0f;

	n->x = n->x / length;
	n->y = n->y / length;
	n->z = n->z / length;
}
    
void calcularNormaisFaces(){

	for (int i=0;i<ALTURA;i++){
		for (int j=0;j<BASE;j++){
		    float x[3], y[3], z[3];
		    ponto a, b, n;
		        
		    for(int k = 0; k < 12; k++){
		        x[0] = campo[i][j].pontos[campo[i][j].faces[k][0]][0];
		        y[0] = campo[i][j].pontos[campo[i][j].faces[k][0]][1];
		        z[0] = campo[i][j].pontos[campo[i][j].faces[k][0]][2];
		    
		        x[1] = campo[i][j].pontos[campo[i][j].faces[k][1]][0];
		        y[1] = campo[i][j].pontos[campo[i][j].faces[k][1]][1];
		        z[1] = campo[i][j].pontos[campo[i][j].faces[k][1]][2];
		    
		        x[2] = campo[i][j].pontos[campo[i][j].faces[k][2]][0];
		        y[2] = campo[i][j].pontos[campo[i][j].faces[k][2]][1];
		        z[2] = campo[i][j].pontos[campo[i][j].faces[k][2]][2];
		        
		        a.x = x[2]- x[0];
		        a.y = y[2]- y[0];
		        a.z = z[2]- z[0];
		        
		        b.x = x[2]- x[1];
		        b.y = y[2]- y[1];
		        b.z = z[2]- z[1];
		        
		        n.x = a.y * b.z - a.z * b.y;
		        n.y = a.z * b.x - a.x * b.z;
		        n.z = a.x * b.y - a.y * b.x;
		       
		        normalizar(&n);
		        
		        campo[i][j].face_normals[k][0] = n.x;
		        campo[i][j].face_normals[k][1] = n.y;
		        campo[i][j].face_normals[k][2] = n.z;
			}
		}
    }
}

void calcularNormaisVertices(){
	for (int i=0;i<ALTURA;i++){
		for (int j=0;j<BASE;j++){
		    ponto n;
		    for(unsigned int k = 0; k < 8; k++){
		        n.x = 0.0;
		        n.y = 0.0;
		        n.z = 0.0;
		        for(int l = 0; l < 12; l++){
		            if(campo[i][j].faces[l][0] == k || campo[i][j].faces[l][1] == k || campo[i][l].faces[l][2] == k){
		                n.x += campo[i][j].face_normals[l][0];
		                n.y += campo[i][j].face_normals[l][1];
		                n.z += campo[i][j].face_normals[l][2];
		            }
		        }
		        
		        n.x /= 3.0;
		        n.y /= 3.0;
		        n.z /= 3.0;        
		        
    			normalizar(&n);
		        campo[i][j].vertex_normals[k][0] = n.x;
		        campo[i][j].vertex_normals[k][1] = n.y;
		        campo[i][j].vertex_normals[k][2] = n.z;        
		    }
		}
	}
}        