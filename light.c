#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Variável global para rotação das luzes
int angle = 0;

// Posições globais das luzes
GLfloat lightR_position[] = {0.0, 2.0, 0.0, 1.0};
GLfloat lightG_position[] = {2.0, 0.0, 0.0, 1.0};
GLfloat lightB_position[] = {-2.0, 0.0, 0.0, 1.0};

void toggleLight(GLenum light)
{
   GLboolean isEnabled;
   glGetBooleanv(light, &isEnabled);
   if (isEnabled) {
      printf("Desativando luz %d\n", light - GL_LIGHT0);
      glDisable(light);
   } else {
      printf("Ativando luz %d\n", light - GL_LIGHT0);
      glEnable(light);
   }
   glutPostRedisplay();
}

void init(void) 
{
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };

   GLfloat lightR_diffuse[] = {1.0, 0.0, 0.0, 1.0};
   GLfloat lightG_diffuse[] = {0.0, 1.0, 0.0, 1.0};
   GLfloat lightB_diffuse[] = {0.0, 0.0, 1.0, 1.0};

   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0); // vermelha
   glEnable(GL_LIGHT1); // verde
   glEnable(GL_LIGHT2); // azul
   glEnable(GL_DEPTH_TEST);

   glLightfv(GL_LIGHT0, GL_DIFFUSE, lightR_diffuse);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, lightG_diffuse);
   glLightfv(GL_LIGHT2, GL_DIFFUSE, lightB_diffuse);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix();

   // Atualiza posição da luz vermelha se estiver ativa
   if (glIsEnabled(GL_LIGHT0)) {
      glPushMatrix();
      glRotatef(angle, 1.0, 0.0, 0.0);
      glLightfv(GL_LIGHT0, GL_POSITION, lightR_position);
      glPopMatrix();
   }

   // Verde (GL_LIGHT1)
   if (glIsEnabled(GL_LIGHT1)) {
      glPushMatrix();
      glRotatef(angle, 0.0, 1.0, 0.0);
      glLightfv(GL_LIGHT1, GL_POSITION, lightG_position);
      glPopMatrix();
   }

   // Azul (GL_LIGHT2)
   if (glIsEnabled(GL_LIGHT2)) {
      glPushMatrix();
      glRotatef(angle, 0.0, 0.0, 1.0);
      glLightfv(GL_LIGHT2, GL_POSITION, lightB_position);
      glPopMatrix();
   }

   glutSolidSphere(1.0, 20, 16);
   glPopMatrix();
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(40.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0.0, 0.0, 5.0,   // olho
             0.0, 0.0, 0.0,   // centro
             0.0, 1.0, 0.0);  // cima
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'r':
         toggleLight(GL_LIGHT0); // luz vermelha
         break;
      case 'g':
         toggleLight(GL_LIGHT1); // luz verde
         break;
      case 'b':
         toggleLight(GL_LIGHT2); // luz azul
         break;
      case 27: // ESC
         exit(0);
         break;
   }
}

void mouse(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      angle = (angle + 10) % 360;
      glutPostRedisplay();
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Rotação de Luzes Coloridas");
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMainLoop();
   return 0;
}
