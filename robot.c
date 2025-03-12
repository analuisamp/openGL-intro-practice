/*
 * robot_extended.c
 * Braço robótico com várias juntas:
 *   - base (roda no eixo Y)
 *   - ombro (shoulder)
 *   - cotovelo (elbow)
 *   - pulso (wrist)
 *   - 2 dedos (finger1, finger2)
 *
 * Teclas:
 *   a/A -> base
 *   s/S -> ombro
 *   e/E -> cotovelo
 *   w/W -> pulso
 *   1/! -> dedo 1
 *   2/@ -> dedo 2
 * ESC   -> sair
 */

 #include <GL/glut.h>
 #include <stdlib.h>
 
 /* ângulos das juntas */
 static int baseRot   = 0;  /* rotação da base em Y */
 static int shoulder  = 0;  /* rotação do ombro */
 static int elbow     = 0;  /* rotação do cotovelo */
 static int wrist     = 0;  /* rotação do pulso */
 static int finger1   = 0;  /* rotação do dedo 1 */
 static int finger2   = 0;  /* rotação do dedo 2 */
 
 void init(void) 
 {
     glClearColor(0.0, 0.0, 0.0, 0.0);
     glShadeModel(GL_FLAT);
 }
 
 void display(void)
 {
     glClear(GL_COLOR_BUFFER_BIT);
 
     /* Salva a matriz inicial */
     glPushMatrix();
 
     /* ========== 1) BASE ========== */
     glRotatef((GLfloat)baseRot, 0.0, 1.0, 0.0);
     /* Desenha a base */
     glPushMatrix();
        glScalef(1.0, 0.2, 1.0);
        glutWireCube(1.0);
     glPopMatrix();
 
     /* Eleva o ponto de construção do braço */
     glTranslatef(0.0, -2.0, 0.0); // Ajuste o valor para mais ou menos

 
     /* ========== 2) OMBRO ========== */
     glTranslatef(-1.0, 0.0, 0.0);
     glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
     glTranslatef(1.0, 0.0, 0.0);
 
     /* Primeiro segmento (ombro -> cotovelo) */
     glPushMatrix();
        glScalef(2.0, 0.4, 1.0);
        glutWireCube(1.0);
     glPopMatrix();
 
     /* ========== 3) COTOVELO ========== */
     glTranslatef(1.0, 0.0, 0.0);
     glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
     glTranslatef(1.0, 0.0, 0.0);
 
     /* Segundo segmento (cotovelo -> pulso) */
     glPushMatrix();
        glScalef(2.0, 0.4, 1.0);
        glutWireCube(1.0);
     glPopMatrix();
 
     /* ========== 4) PULSO ========== */
     glTranslatef(1.0, 0.0, 0.0);
     glRotatef((GLfloat)wrist, 0.0, 0.0, 1.0);
     glTranslatef(0.5, 0.0, 0.0);
 
     /* Desenha o punho */
     glPushMatrix();
        glScalef(1.0, 0.2, 0.5);
        glutWireCube(1.0);
     glPopMatrix();
 
     /* ========== 5) MÃO ========== */
     /* Exemplo de "mão" maior para encaixar dedos */
     glTranslatef(0.7, 0.0, 0.0);
     glPushMatrix();
        glScalef(1.2, 0.3, 0.5);
        glutWireCube(1.0);
     glPopMatrix();
 
     /* ========== 6) DEDOS ========== */
     /* Dedo 1 */
     glPushMatrix();
        glTranslatef(0.6, 0.0, 0.3);
        glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0); 
        glScalef(0.5, 0.1, 0.1);
        glutWireCube(1.0);
     glPopMatrix();
 
     /* Dedo 2 */
     glPushMatrix();
        glTranslatef(0.6, 0.0, -0.3);
        glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);
        glScalef(0.5, 0.1, 0.1);
        glutWireCube(1.0);
     glPopMatrix();
 
     /* Restaura a matriz inicial */
     glPopMatrix();
 
     glutSwapBuffers();
 }
 
 void reshape (int w, int h)
 {
     glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(65.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glTranslatef(0.0, 0.0, -5.0);
 }
 
 /* Teclas para mover todas as juntas */
 void keyboard(unsigned char key, int x, int y)
 {
     switch (key) {
        /* base -> 'a'/'A' */
        case 'a':
          baseRot = (baseRot + 5) % 360; 
          glutPostRedisplay();
          break;
        case 'A':
          baseRot = (baseRot - 5) % 360;
          glutPostRedisplay();
          break;
 
        /* ombro -> 's'/'S' */
        case 's':
          shoulder = (shoulder + 5) % 360;
          glutPostRedisplay();
          break;
        case 'S':
          shoulder = (shoulder - 5) % 360;
          glutPostRedisplay();
          break;
 
        /* cotovelo -> 'e'/'E' */
        case 'e':
          elbow = (elbow + 5) % 360;
          glutPostRedisplay();
          break;
        case 'E':
          elbow = (elbow - 5) % 360;
          glutPostRedisplay();
          break;
 
        /* pulso -> 'w'/'W' */
        case 'w':
          wrist = (wrist + 5) % 360;
          glutPostRedisplay();
          break;
        case 'W':
          wrist = (wrist - 5) % 360;
          glutPostRedisplay();
          break;
 
        /* dedo1 -> '1'/'!' */
        case '1':
          finger1 = (finger1 + 5) % 360;
          glutPostRedisplay();
          break;
        case '!':
          finger1 = (finger1 - 5) % 360;
          glutPostRedisplay();
          break;
 
        /* dedo2 -> '2'/'@' */
        case '2':
          finger2 = (finger2 + 5) % 360;
          glutPostRedisplay();
          break;
        case '@':
          finger2 = (finger2 - 5) % 360;
          glutPostRedisplay();
          break;
 
        /* ESC para sair */
        case 27:
          exit(0);
          break;
        default:
          break;
     }
 }
 
 int main(int argc, char** argv)
 {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
     glutInitWindowSize(600, 600); 
     glutInitWindowPosition(100, 100);
     glutCreateWindow("Braço Robótico Extendido");
     init();
     glutDisplayFunc(display); 
     glutReshapeFunc(reshape);
     glutKeyboardFunc(keyboard);
     glutMainLoop();
     return 0;
 }
 