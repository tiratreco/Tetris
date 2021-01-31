

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include "tetris.h"

bool musica = true;
bool iluminacao = false;
int mseg = 1;
GLfloat perspectiva[4] = {16, 0, 1.0, 100.0};
GLfloat camera[9] = {-32.0, 4.8, 45.0, 10.0, 5.0, 0.0, -99999.0, -3.0, -10.0};
int indice = 0;


void init_glut(const char *window_name, int argc, char** argv);
void draw_object_smooth(void);
void display_callback(void);
void reshape_callback(int w, int h);
void animate_callback(void);
void timer_callback(int value);
void keyboard_callback(unsigned char key, int x, int y);
void info_modotexto();
GLint LoadTexture( const char * filename );

int main(int argc, char** argv){
    
	srand(time(NULL));
	
    info_modotexto();

   init_glut("Tetris 3D", argc, argv);
   glutMainLoop();

   return 0;
}

void init_glut(const char *nome_janela, int argc, char** argv){

    carregar();
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,100);
    glutCreateWindow(nome_janela);
	//glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //ILUMINACAO PREJUDICA A VISUALIZACAO DO JOGO,
    //UTILIZAMOS OUTRA ALTERNATIVA
    
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);  
 	glEnable(GL_COLOR_MATERIAL);


    /* define as funcões de callback */
    glutKeyboardFunc(keyboard_callback);
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutIdleFunc(animate_callback);
	glutTimerFunc(mseg, timer_callback,mseg);

    /* Inicia a iluminação */
    GLfloat light_position[4] = {-100.0, 4.8, 45.0, 0.0}; //posição da luz
	GLfloat light_color[4] = {0.5, 0.5, 0.5, 1.0};//luz ambiente
	GLfloat diffuse[4] = {0.5, 0.5 , 0.5, 0.0};//luz difusa
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};//luz especular
	GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};// Capacidade de brilho do material
	
	GLint especMaterial = 60;	



	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,cores[PRETO]);
    glMaterialfv(GL_FRONT, GL_SPECULAR,cores[PRETO]);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_color); 
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, light_position );
	



    glClearColor(0.0, 0.0, 0.0, 0.0);

    
   
    //Cria a textura
    glEnable(GL_TEXTURE_2D);
    GLuint texture;
	texture = LoadTexture("005briques.bmp" );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void reshape_callback(int w, int h){
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    glViewport (5, 0, (GLsizei) w, (GLsizei) h);
	
    gluPerspective(perspectiva[0],(float)w/(float)h,perspectiva[2],perspectiva[3]);
	gluLookAt (camera[0],camera[1],camera[2],camera[3],camera[4],camera[5],camera[6],camera[7],camera[8]);
    glMatrixMode (GL_MODELVIEW);	

}

void timer_callback(int value){
    glutTimerFunc(value, timer_callback, value);
    glutPostRedisplay();
    jogo();
}

void mudarPerspectiva (char botao){
	
	if(botao == 'w')
		camera[indice]++;
	else if (botao == 's')
		camera[indice]--;
	else if (botao == 'a')
		indice--;
	else if (botao == 'd')
		indice++;
	
	printf("%d  ", indice);
	printf("%.2f\n", camera[indice]);
}

void draw_object_smooth(void){
	if (iluminacao) glEnable(GL_LIGHTING);
	else glDisable(GL_LIGHTING);
		
	if (estado==MENU){
		menu();
	}
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
    for (int i=0; i<N_FACES; i++){
		if (i <= 5) 
			glColor3f(cores[moldura.cor][0], cores[moldura.cor][1], cores[moldura.cor][2]);
		else
			glColor3f(cores[moldura.cor+ESCURO][0], cores[moldura.cor+ESCURO][1], cores[moldura.cor+ESCURO][2]);
		glTexCoord2fv(tex_coords[i][0]);
        glNormal3fv(moldura.vertex_normals[moldura.faces[i][0]]);
        glVertex3fv(moldura.pontos[moldura.faces[i][0]]);
	   	glTexCoord2fv(tex_coords[i][1]);
        glVertex3fv(moldura.pontos[moldura.faces[i][1]]);
	   	glTexCoord2fv(tex_coords[i][2]);
        glVertex3fv(moldura.pontos[moldura.faces[i][2]]);
	}
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
	for (int i=0;i<ALTURA;i++){
		for (int j=0;j<BASE;j++){
			glBegin(GL_TRIANGLES);
    		for (int k=0; k<12; k++){
    			if (campo[i][j].ocupado){
    				if (k==6 || k==7 || k==8 || k==9 || k==0 || k==1)
    					glColor3f(cores[campo[i][j].cor+ESCURO][0], cores[campo[i][j].cor+ESCURO][1], cores[campo[i][j].cor+ESCURO][2]);
					else
						glColor3f(cores[campo[i][j].cor][0], cores[campo[i][j].cor][1], cores[campo[i][j].cor][2]);
					
		            glNormal3fv(campo[i][j].vertex_normals[campo[i][j].faces[k][0]]);
		            glVertex3fv(campo[i][j].pontos[campo[i][j].faces[k][0]]);
					
		            glNormal3fv(campo[i][j].vertex_normals[campo[i][j].faces[k][1]]);
		            glVertex3fv(campo[i][j].pontos[campo[i][j].faces[k][1]]);
		
		            glNormal3fv(campo[i][j].vertex_normals[campo[i][j].faces[k][2]]);
		            glVertex3fv(campo[i][j].pontos[campo[i][j].faces[k][2]]);
				}
			}
			glEnd();
		}
    }
    if (estado==EM_JOGO)mostrarPontos();
    if (estado==FIM){
		fim();
	}
    
}

void display_callback(void){
	gluLookAt (camera[0],camera[1],camera[2],camera[3],camera[4],camera[5],camera[6],camera[7],camera[8]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    draw_object_smooth();    
	
    glutSwapBuffers();
}


void animate_callback(void){
    glutPostRedisplay();
    
}


void info_modotexto(){
    
}

void keyboard_callback(unsigned char key, int x, int y){
	if (key == 27) exit(0);
	if (key == '2'){//iluminacao
		iluminacao=!iluminacao;
	}
	else if (key == ' '){
		if (estado==MENU) {
			estado = INICIANDO;
			PlaySound("TETRIS_THEME_SONG.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
		}
		else if(estado==FIM) {
			estado = MENU;	
			limparCampo();
			PlaySound("tic.wav", NULL, SND_ASYNC|SND_FILENAME);
		}
	}
	if (estado!=EM_JOGO) return;
	if (key == 'a' || key == 'A') mover(ESQUERDA);
	else if (key == 'd' || key == 'D') mover(DIREITA);
	else if (key == 's' || key == 'S') {
		pontos+=10;
		descerFigura();
	}
	else if (key == 'w' || key == 'W') rotacionar();
	else if (key == '1'){//musica
		if (musica) PlaySound("tic.wav", NULL, SND_ASYNC|SND_FILENAME);
		else PlaySound("TETRIS_THEME_SONG.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
		musica = !musica;
	}
	
	//else if (key == 'a' || key == 'A') mudarPerspectiva ('a');
	//else if (key == 'd' || key == 'D') mudarPerspectiva ('d');
	//else if (key == 's' || key == 'S') mudarPerspectiva ('s');
	//else if (key == 'w' || key == 'W') mudarPerspectiva ('w');
	
	atualizarFigura();
}

GLint LoadTexture( const char * filename )
{
  GLuint texture;
  char * data;

  FILE * file;
  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;
  data = (char *)malloc( TEXTURE_WIDTH * TEXTURE_HEIGHT * 3 );
  fread( data, TEXTURE_WIDTH * TEXTURE_HEIGHT * 3, 1, file );
  fclose( file );

  for(int i = 0; i < TEXTURE_WIDTH * TEXTURE_HEIGHT ; ++i)
  {
    int index = i*3;
    char B,R;
    B = data[index];
    R = data[index+2];

    data[index] = R;
    data[index+2] = B;
  }
  //return data;
  
  glGenTextures( 1, &texture);
  glBindTexture( GL_TEXTURE_2D, texture);
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
  
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, TEXTURE_WIDTH, TEXTURE_HEIGHT,GL_RGB, GL_UNSIGNED_BYTE, data );
  free( data );

  return texture;
}

