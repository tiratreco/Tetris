
//*********************************************************************
//  Modelagem Geométrica 3D usando OpenGL
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
    
int mseg = 10;
/* Determina se vamos usar Gouraud ou Flat shading */
unsigned char use_gouraud = 1;

/* Determina se vamos usar Z-buffering */
unsigned char use_depth_test = 1;

/* Determina se Liga a Luz */
unsigned char use_light = 1;

/* Determina se vamos habilitar as características do material */
unsigned char use_material = 1;



/**********************************************************************/
/*                  Declaração de funções forward                     */
/**********************************************************************/
void init_glut(const char *window_name, int argc, char** argv);
void draw_object_smooth(void);
void draw_object_flat(void);
void display_callback(void);
void reshape_callback(int w, int h);
void animate_callback(void);
void timer_callback(int value);
void keyboard_callback(unsigned char key, int x, int y);
void keyboard_callback_special(int key, int x, int y);
void info_modotexto();

/**********************************************************************/
/*                                                                    */
/*                       Função principal (main)                      */
/*                                                                    */
/**********************************************************************/

int main(int argc, char** argv){
    
	srand(time(NULL));
	iniciar();
	geraFigura();
	
    info_modotexto();
   /* inicia o GLUT e alguns parâmetros do OpenGL */

   init_glut("Desenhando Objetos em 3D", argc, argv);

   /* função de controlo do GLUT */
   glutMainLoop();

   return 0;
}

/**********************************************************************/
/*                                                                    */
/*                         Definição de funções                       */
/*                                                                    */
/**********************************************************************/


/*
 * inicia o GLUT e alguns parâmetros do OpenGL
 */
void init_glut(const char *nome_janela, int argc, char** argv){
    /* inicia o GLUT */
    glutInit(&argc,argv);

    /* inicia o display usando RGB e double-buffering */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,100);
    glutCreateWindow(nome_janela);

    /* define as funcões de callback */
    glutKeyboardFunc(keyboard_callback);
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutSpecialFunc(keyboard_callback_special);

//    glutIdleFunc(animate_callback);
	glutTimerFunc(mseg, timer_callback,mseg);

    /* Inicia a iluminação */
    GLfloat light_position[] = {-1.0, 1.0, 1.0, 0.0};
	GLfloat light_color[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


    /* Inicia as características gerais dos materiais */
	GLfloat mat_ambient_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_diffuse);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    /* Ativa o modelo de sombreagem de "Gouraud". */
    glShadeModel(GL_SMOOTH);

    /* Ativa o z-buffering, de modo a remover as superfícies escondidas */
    glEnable(GL_DEPTH_TEST);

    /* define a cor com a qual o ecrã será apagado */
    glClearColor(1.0, 1.0, 1.0, 1.0);

    /* define a cor de desenho inicial (azul) */
    glColor3f(0.0, 0.0, 1.0);
}

/*
 * Processa o reshape da janela
 */
void reshape_callback(int w, int h){

    /* muda para o modo GL_PROJECTION e reinicia a projecção */
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    /* define a zona da janela onde se vai desenhar */
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	
    /* Define a forma do "viewing volume" para termos *
     * uma projecção de perspectiva (3D).             */
    gluPerspective(30, (float)w/(float)h, 1.0, 100.0);

	/* Transformação de visão */
    gluLookAt (5.0, 10.0, 50.0, 5.0, 10.0, -19.0, 99999.0, 1.0, 0.0);

    /* muda para o modo GL_MODELVIEW (não pretendemos alterar a projecção
     * quando estivermos a desenhar no display) */
    glMatrixMode (GL_MODELVIEW);	

}

void timer_callback(int value){
    glutTimerFunc(value, timer_callback, value);
    glutPostRedisplay(); // Manda redesenhar o display em cada frame
}

/*
 * Desenha o objeto, triângulo por triângulo, definindo os vetores
 * normais de cada vértice (ideal para usar com Gouraud shading).
 */
void draw_object_smooth(void){
    GLuint k;

    /* Desenha todos os triângulos do objeto */
    glBegin(GL_TRIANGLES);
    	for (int i=0;i<ALTURA;i++){
			for (int j=0;j<BASE;j++){
        		for (k=0; k<12; k++){
		            glNormal3fv(campo[i][j].vertex_normals[campo[i][j].faces[k][0]]);
		            glVertex3fv(campo[i][j].pontos[campo[i][j].faces[k][0]]);
		
		            glNormal3fv(campo[i][j].vertex_normals[campo[i][j].faces[k][1]]);
		            glVertex3fv(campo[i][j].pontos[campo[i][j].faces[k][1]]);
		
		            glNormal3fv(campo[i][j].vertex_normals[campo[i][j].faces[k][2]]);
		            glVertex3fv(campo[i][j].pontos[campo[i][j].faces[k][2]]);
				}
			}
        }
    glEnd();
}

/*
 * Desenha o objeto, triângulo por triângulo, utilizando um vetor
 * normal para cada triângulo (ideal para usar com flat shading).

 * função para controlar o display 
 */
void display_callback(void){
    
    /* Apaga o video e o depth buffer, e reinicia a matriz */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    /* faz variar o ângulo de rotação entre 0 e 360 graus, e roda o *
     * referencial segundo o eixo (1, 1, 0).                        */
    /* Desenha o objeto */
    draw_object_smooth();    

    /* Troca os buffers, mostrando o que acabou de ser desenhado */
    glutSwapBuffers();
}

/*
 * Função necessária para a animação
 */
void animate_callback(void){
    glutPostRedisplay(); /* Manda redesenhar o display em cada frame */
}


void info_modotexto(){
    
}

/*
 * Controle das teclas normais
 */
void keyboard_callback(unsigned char key, int x, int y){
    if (key==27) exit(0); /* Esc: sai do programa */
}


/*
 * Controle das teclas especiais (Cursores, F1 a F12, etc...)
 */
void keyboard_callback_special(int key, int x, int y){
    switch(key){
        case 1:
            glColor3f(0.0, 0.0, 1.0);      /* F1: muda a cor para azul */
            break;

        case 2:
            glColor3f(0.0, 1.0, 0.0);      /* F2: muda a cor para verde */
            break;

        case 3:
            glColor3f(1.0, 0.0, 0.0);      /* F3: muda a cor para vermelho */
            break;
            
        case 4:                      /* F4: liga/desliga a luz */
            if (use_light==1){
               use_light=0;
               glDisable(GL_LIGHTING);
            }else{
               use_light=1;
               glEnable(GL_LIGHTING);
            }
            break;
            
        case 5:                      /* F5: liga/desliga o gouraud shading */
            if (use_gouraud==1){
               use_gouraud=0;
               glShadeModel(GL_FLAT);
               
            }else{
               use_gouraud=1;
               
            }
            break;

        case 6:                          /* F6: liga/desliga o Z-buffering */
            if (use_depth_test==1){
               use_depth_test=0;
               glDisable(GL_DEPTH_TEST);
            }else{
               use_depth_test=1;
               glEnable(GL_DEPTH_TEST);
            }
            break;

    }
    glutPostRedisplay();
}


