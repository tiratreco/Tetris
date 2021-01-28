
//*********************************************************************
//  Modelagem Geom�trica 3D usando OpenGL
//  Codigo Exemplo
//*********************************************************************

/* Inclui os headers do OpenGL, GLU, e GLUT */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "tetris.h"
    
int mseg = 1;
GLfloat perspectiva[4] = {16, 0, 1.0, 100.0};
GLfloat camera[9] = {-32.0, 5.0, 45.0, 10.0, 5.0, 0.0, -99999.0, -3.0, -10.0};
int indice = 0;

/**********************************************************************/
/*                  Declara��o de fun��es forward                     */
/**********************************************************************/
void init_glut(const char *window_name, int argc, char** argv);
void draw_object_smooth(void);
void display_callback(void);
void reshape_callback(int w, int h);
void animate_callback(void);
void timer_callback(int value);
void keyboard_callback(unsigned char key, int x, int y);
void info_modotexto();

/**********************************************************************/
/*                                                                    */
/*                       Fun��o principal (main)                      */
/*                                                                    */
/**********************************************************************/

int main(int argc, char** argv){
    
	srand(time(NULL));
	iniciar();
	
    info_modotexto();
   /* inicia o GLUT e alguns par�metros do OpenGL */

   init_glut("Desenhando Objetos em 3D", argc, argv);

   /* fun��o de controlo do GLUT */
   glutMainLoop();

   return 0;
}

/**********************************************************************/
/*                                                                    */
/*                         Defini��o de fun��es                       */
/*                                                                    */
/**********************************************************************/


/*
 * inicia o GLUT e alguns par�metros do OpenGL
 */
void init_glut(const char *nome_janela, int argc, char** argv){
    /* inicia o GLUT */
    glutInit(&argc,argv);

    /* inicia o display usando RGB e double-buffering */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,100);
    glutCreateWindow(nome_janela);
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    
        /* Ativa o modelo de sombreagem de "Gouraud". */
    glShadeModel(GL_SMOOTH);

    /* Ativa o z-buffering, de modo a remover as superf�cies escondidas */
    glEnable(GL_DEPTH_TEST);  
 	glEnable(GL_COLOR_MATERIAL);


    /* define as func�es de callback */
    glutKeyboardFunc(keyboard_callback);
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);

    glutIdleFunc(animate_callback);
	glutTimerFunc(mseg, timer_callback,mseg);

    /* Inicia a ilumina��o */
    GLfloat light_position[4] = {0.0, 5.0, 45.0, 0.0}; //posi��o da luz
	GLfloat light_color[4] = {1.0, 1.0, 1.0, 1.0};//luz ambiente
	GLfloat diffuse[4] = {0.7, 0.7 , 0.7, 1.0};//luz difusa
	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};//luz especular
	GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};// Capacidade de brilho do material
	
	GLint especMaterial = 60;	


    /* Inicia as caracter�sticas gerais dos materiais */
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);//reflet�ncia do material
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);//concentra��o do brilho
    glMaterialfv(GL_FRONT, GL_DIFFUSE,cores[PRETO]);
    glMaterialfv(GL_FRONT, GL_SPECULAR,cores[PRETO]);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_color); //ativa a luz ambiente

	//parametros da luz de numero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, light_position );
	



    /* define a cor com a qual o ecr� ser� apagado */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* define a cor de desenho inicial (azul) */
}

/*
 * Processa o reshape da janela
 */
void reshape_callback(int w, int h){
    /* muda para o modo GL_PROJECTION e reinicia a projec��o */
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    /* define a zona da janela onde se vai desenhar */
    glViewport (5, 0, (GLsizei) w, (GLsizei) h);
	
    /* Define a forma do "viewing volume" para termos *
     * uma projec��o de perspectiva (3D).             */
    gluPerspective(perspectiva[0],(float)w/(float)h,perspectiva[2],perspectiva[3]);

	/* Transforma��o de vis�o */
    gluLookAt (camera[0],camera[1],camera[2],camera[3],camera[4],camera[5],camera[6],camera[7],camera[8]);

    /* muda para o modo GL_MODELVIEW (n�o pretendemos alterar a projec��o
     * quando estivermos a desenhar no display) */
    glMatrixMode (GL_MODELVIEW);	

}

void timer_callback(int value){
    glutTimerFunc(value, timer_callback, value);
    
    jogo();
    glutPostRedisplay(); // Manda redesenhar o display em cada frame
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
  
/*
 * Desenha o objeto, tri�ngulo por tri�ngulo, definindo os vetores
 * normais de cada v�rtice (ideal para usar com Gouraud shading).
 */
void draw_object_smooth(void){
    GLuint k;

    /* Desenha todos os tri�ngulos do objeto */
    
    	for (int i=0;i<ALTURA;i++){
			for (int j=0;j<BASE;j++){
				glBegin(GL_TRIANGLES);
        		for (k=0; k<12; k++){
        			if (campo[i][j].ocupado){
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
	//else if (key == 'a' || key == 'A') mover(ESQUERDA);
	//else if (key == 'd' || key == 'D') mover(DIREITA);
	//else if (key == 's' || key == 'S') descerFigura();
	//else if (key == 'w' || key == 'W') rotacionar();
	
	else if (key == 'a' || key == 'A') mudarPerspectiva ('a');
	else if (key == 'd' || key == 'D') mudarPerspectiva ('d');
	else if (key == 's' || key == 'S') mudarPerspectiva ('s');
	else if (key == 'w' || key == 'W') mudarPerspectiva ('w');
	
	atualizarFigura();
}



