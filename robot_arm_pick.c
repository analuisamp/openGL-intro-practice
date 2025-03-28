#include <GL/glut.h>
#include <stdlib.h>

// Ângulos de rotação de cada junta
static int baseRot = 0;
static int shoulder = 0;
static int elbow = 0;
static int wrist = 0;
static int finger1 = 0;
static int finger2 = 0;

// Estado do objeto
static float objetoX = 2.5, objetoY = 0.2, objetoZ = 0.0; // Posição inicial do objeto
static int pegandoObjeto = 0; // 0 = não pegando, 1 = segurando

void init(void) 
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
   glEnable(GL_DEPTH_TEST); // Ativa o Z-buffer para evitar sobreposição errada
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();
   gluLookAt(0.0, 3.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glPushMatrix();

   // Base (rotação no eixo Y)
   glRotatef((GLfloat) baseRot, 0.0, 1.0, 0.0);
   glColor3f(0.5, 0.5, 0.5); // Cinza
   glPushMatrix();
   glScalef(1.5, 0.4, 1.5);
   glutSolidCube(1.0);
   glPopMatrix();

   // Ombro (rotação no eixo Z)
   glTranslatef(0.0, 0.4, 0.0);
   glRotatef((GLfloat) shoulder, 0.0, 0.0, 1.0);
   glTranslatef(1.0, 0.0, 0.0);
   glColor3f(1.0, 0.0, 0.0); // Vermelho
   glPushMatrix();
   glScalef(2.0, 0.4, 1.0);
   glutSolidCube(1.0);
   glPopMatrix();

   // Cotovelo (rotação no eixo Y)
   glTranslatef(1.0, 0.0, 0.0);
   glRotatef((GLfloat) elbow, 0.0, 1.0, 0.0);
   glTranslatef(1.0, 0.0, 0.0);
   glColor3f(0.0, 0.0, 1.0); // Azul
   glPushMatrix();
   glScalef(2.0, 0.4, 1.0);
   glutSolidCube(1.0);
   glPopMatrix();

   // Pulso (rotação no eixo X)
   glTranslatef(1.0, 0.0, 0.0);
   glRotatef((GLfloat) wrist, 1.0, 0.0, 0.0);
   glTranslatef(0.5, 0.0, 0.0);
   glColor3f(0.0, 1.0, 0.0); // Verde
   glPushMatrix();
   glScalef(1.0, 0.2, 0.5);
   glutSolidCube(1.0);
   glPopMatrix();

   // Mão (base dos dedos)
   glTranslatef(0.7, 0.0, 0.0);
   glColor3f(1.0, 1.0, 0.0); // Amarelo
   glPushMatrix();
   glScalef(1.2, 0.3, 0.5);
   glutSolidCube(1.0);
   glPopMatrix();

   // Dedo 1
   glPushMatrix();
   glTranslatef(0.6, 0.0, 0.3);
   glRotatef((GLfloat) finger1, 0.0, 0.0, 1.0);
   glColor3f(1.0, 0.5, 0.0); // Laranja
   glScalef(0.5, 0.1, 0.1);
   glutSolidCube(1.0);
   glPopMatrix();

   // Dedo 2
   glPushMatrix();
   glTranslatef(0.6, 0.0, -0.3);
   glRotatef((GLfloat) finger2, 0.0, 0.0, 1.0);
   glColor3f(1.0, 0.5, 0.0);
   glScalef(0.5, 0.1, 0.1);
   glutSolidCube(1.0);
   glPopMatrix();

   // Se o robô está segurando o objeto, o objeto segue a mão
// Se o robô está segurando o objeto, o objeto segue a mão
   if (pegandoObjeto) {
      objetoX = 3.2;  // Ajuste para alinhar com a posição da mão
      objetoY = 0.5;  // Ajuste para alinhar melhor verticalmente
      objetoZ = 0.0;  // Mantém o eixo Z correto
   }

   // Desenha o objeto (cubo marrom)
   glPushMatrix();
   if (pegandoObjeto) {
      // Faz o objeto seguir a garra corretamente
      glTranslatef(3.0, 0.0, 0.0); // Ajuste para alinhar com os dedos
   }
   glTranslatef(objetoX, objetoY, objetoZ);
   glColor3f(0.6, 0.3, 0.2); // Marrom (cor do objeto)
   glutSolidCube(0.4);
   glPopMatrix();


   // Caixa onde o objeto será colocado
   glPushMatrix();
   glTranslatef(-2.5, 0.2, 0.0);
   glColor3f(0.3, 0.3, 0.3); // Cinza escuro
   glutWireCube(1.0);
   glPopMatrix();

   glPopMatrix();
   glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'p': // Alterna entre pegar e soltar o objeto
            pegandoObjeto = !pegandoObjeto;
            if (!pegandoObjeto) {
                // Define nova posição do objeto ao soltar
                objetoX = 2.5; 
                objetoY = 0.2;
                objetoZ = 0.0;
            }
            glutPostRedisplay();
            break;
            
        // Movimentação da base
        case 'b': 
            baseRot = (baseRot + 5) % 360;
            glutPostRedisplay();
            break;
        case 'B': 
            baseRot = (baseRot - 5) % 360;
            glutPostRedisplay();
            break;

        // Movimentação do ombro
        case 's': 
            shoulder = (shoulder + 5) % 360;
            glutPostRedisplay();
            break;
        case 'S': 
            shoulder = (shoulder - 5) % 360;
            glutPostRedisplay();
            break;

        // Movimentação do cotovelo
        case 'e': 
            elbow = (elbow + 5) % 360;
            glutPostRedisplay();
            break;
        case 'E': 
            elbow = (elbow - 5) % 360;
            glutPostRedisplay();
            break;

        // Movimentação do pulso
        case 'w': 
            wrist = (wrist + 5) % 360;
            glutPostRedisplay();
            break;
        case 'W': 
            wrist = (wrist - 5) % 360;
            glutPostRedisplay();
            break;

        // Abrir e fechar dedo 1
        case '1': 
            finger1 = (finger1 + 5) % 360;
            glutPostRedisplay();
            break;
        case '!': 
            finger1 = (finger1 - 5) % 360;
            glutPostRedisplay();
            break;

        // Abrir e fechar dedo 2
        case '2': 
            finger2 = (finger2 + 5) % 360;
            glutPostRedisplay();
            break;
        case '@': 
            finger2 = (finger2 - 5) % 360;
            glutPostRedisplay();
            break;

        case 27: // Tecla ESC para sair
            exit(0);
            break;
    }
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(600, 600);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Braço Robótico Pegando Objetos");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
