#include <math.h>

#define Z_FUNDO 0
#define Z_FRENTE 1

#define N_VERTICE 15
#define N_FACES 15
float xa = -5;
float ya = 0;
float xb = -5;
float yb = 20;
float xc = 14;
float yc = 0;
float xd = 14;
float yd = 20;
float xe = -5;
float ye = 24;
float xf = 14;
float yf = 24;

struct ponto{
    float x;
    float y;
    float z;
};

struct moldura{
	GLfloat	pontos[N_VERTICE][3];
	GLfloat	vertex_normals[N_VERTICE][3];
	GLfloat face_normals[N_FACES][3];
	GLuint faces[N_FACES][3];
	int cor;
};

moldura moldura;


void normalizar(ponto * n){
	GLfloat length;
	
	length = (GLfloat) sqrt((n->x * n->x) + (n->y * n->y) + (n->z * n->z));
		
	if (length == 0.0f)
		length =  1.0f;

	n->x = n->x / length;
	n->y = n->y / length;
	n->z = n->z / length;
}
void preencherMolduras(){
	moldura.cor = BRANCO;
	moldura.pontos[0][0] = ya;
	moldura.pontos[0][1] = xa;
	moldura.pontos[0][2] = Z_FRENTE;
	moldura.pontos[1][0] = 0;
	moldura.pontos[1][1] = 0;
	moldura.pontos[1][2] = Z_FRENTE;
	moldura.pontos[2][0] = 0;
	moldura.pontos[2][1] = 10;
	moldura.pontos[2][2] = Z_FRENTE;
	moldura.pontos[3][0] = yc;
	moldura.pontos[3][1] = xc;
	moldura.pontos[3][2] = Z_FRENTE;
	moldura.pontos[4][0] = yb;
	moldura.pontos[4][1] = xb;
	moldura.pontos[4][2] = Z_FRENTE;
	moldura.pontos[5][0] = 20;
	moldura.pontos[5][1] = 0;
	moldura.pontos[5][2] = Z_FRENTE;
	moldura.pontos[6][0] = 20;
	moldura.pontos[6][1] = 10;
	moldura.pontos[6][2] = Z_FRENTE;
	moldura.pontos[7][0] = yd;
	moldura.pontos[7][1] = xd;
	moldura.pontos[7][2] = Z_FRENTE;
	moldura.pontos[8][0] = ye;
	moldura.pontos[8][1] = xe;
	moldura.pontos[8][2] = Z_FRENTE;
	moldura.pontos[9][0] = yf;
	moldura.pontos[9][1] = xf;
	moldura.pontos[9][2] = Z_FRENTE;
	
	moldura.pontos[10][0] = ya;
	moldura.pontos[10][1] = xa;
	moldura.pontos[10][2] = Z_FUNDO;
	
	moldura.pontos[11][0] = 0;
	moldura.pontos[11][1] = 0;
	moldura.pontos[11][2] = Z_FUNDO;
	
	moldura.pontos[12][0] = 20;
	moldura.pontos[12][1] = 0;
	moldura.pontos[12][2] = Z_FUNDO;
	
	moldura.pontos[13][0] = 20;
	moldura.pontos[13][1] = 10;
	moldura.pontos[13][2] = Z_FUNDO;
	
	moldura.pontos[14][0] = 0;
	moldura.pontos[14][1] = 10;
	moldura.pontos[14][2] = Z_FUNDO;
	
	moldura.pontos[15][0] = yc;
	moldura.pontos[15][1] = xc;
	moldura.pontos[15][2] = Z_FUNDO;
	
	
	moldura.faces[0][0] = 0;
	moldura.faces[0][1] = 4;
	moldura.faces[0][2] = 1;
	
	moldura.faces[1][0] = 1;
	moldura.faces[1][1] = 4;
	moldura.faces[1][2] = 5;
	
	moldura.faces[2][0] = 2;
	moldura.faces[2][1] = 6;
	moldura.faces[2][2] = 3;
	
	moldura.faces[3][0] = 3;
	moldura.faces[3][1] = 6;
	moldura.faces[3][2] = 7;
	
	moldura.faces[4][0] = 4;
	moldura.faces[4][1] = 8;
	moldura.faces[4][2] = 7;
	
	moldura.faces[5][0] = 7;
	moldura.faces[5][1] = 8;
	moldura.faces[5][2] = 9;
	
	moldura.faces[5][0] = 7;
	moldura.faces[5][1] = 8;
	moldura.faces[5][2] = 9;
	//profundidade
	moldura.faces[6][0] = 0;
	moldura.faces[6][1] = 11;
	moldura.faces[6][2] = 10;
	
	moldura.faces[7][0] = 0;
	moldura.faces[7][1] = 1;
	moldura.faces[7][2] = 11;
	
	moldura.faces[8][0] = 1;
	moldura.faces[8][1] = 11;
	moldura.faces[8][2] = 5;
	
	moldura.faces[9][0] = 11;
	moldura.faces[9][1] = 12;
	moldura.faces[9][2] = 5;
	
	moldura.faces[10][0] = 5;
	moldura.faces[10][1] = 13;
	moldura.faces[10][2] = 12;
	
	moldura.faces[11][0] = 5;
	moldura.faces[11][1] = 6;
	moldura.faces[11][2] = 13;
	
	moldura.faces[12][0] = 14;
	moldura.faces[12][1] = 2;
	moldura.faces[12][2] = 13;
	
	moldura.faces[13][0] = 2;
	moldura.faces[13][1] = 6;
	moldura.faces[13][2] = 13;
	
	moldura.faces[14][0] = 2;
	moldura.faces[14][1] = 14;
	moldura.faces[14][2] = 15;
	
	moldura.faces[15][0] = 3;
	moldura.faces[15][1] = 2;
	moldura.faces[15][2] = 15;

	//calcula normais face
	float x[3], y[3], z[3];
    ponto a, b, n;
        
    for(int k = 0; k < N_FACES; k++){// numero de faces
        x[0] = moldura.pontos[moldura.faces[k][0]][0];
        y[0] = moldura.pontos[moldura.faces[k][0]][1];
        z[0] = moldura.pontos[moldura.faces[k][0]][2];

        x[1] = moldura.pontos[moldura.faces[k][1]][0];
        y[1] = moldura.pontos[moldura.faces[k][1]][1];
        z[1] = moldura.pontos[moldura.faces[k][1]][2];

        x[2] = moldura.pontos[moldura.faces[k][2]][0];
        y[2] = moldura.pontos[moldura.faces[k][2]][1];
        z[2] = moldura.pontos[moldura.faces[k][2]][2];

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

        moldura.face_normals[k][0] = n.x;
        moldura.face_normals[k][1] = n.y;
        moldura.face_normals[k][2] = n.z;
	}
	
	//calcula normais vertice
    for(unsigned int k = 0; k < N_VERTICE; k++){//numero de vertices
        n.x = 0.0;
        n.y = 0.0;
        n.z = 0.0;
        for(int l = 0; l < 12; l++){
            if(moldura.faces[l][0] == k || moldura.faces[l][1] == k || moldura.faces[l][2] == k){
                n.x += moldura.face_normals[l][0];
                n.y += moldura.face_normals[l][1];
                n.z += moldura.face_normals[l][2];
            }
        }
        
        n.x /= 3.0;
        n.y /= 3.0;
        n.z /= 3.0;        
        
		normalizar(&n);
        moldura.vertex_normals[k][0] = n.x;
        moldura.vertex_normals[k][1] = n.y;
        moldura.vertex_normals[k][2] = n.z;        
    }
}

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

void output(int x, int y, char *string){
  int len, i;

  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
  }
}
