

/* 
 
   Plantilla generada autom�ticamente por glutSkel.
   Paco Abad (http://www.dsic.upv.es/~fjabad), Universidad Polit�cnica de Valencia.
   Valencia 2007 
   
*/


#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <string>
#include <time.h>
#include <GL/glut.h>

// Debes implementar las siguientes dos funciones (en un fichero aparte).
void inicia(void);			// Esta funci�n se llamar?una vez, antes de dibujar nada.
void dibuja(void);  // Esta funci�n se llamar?cada vez que haya que dibujar
							// la escena.
void click(int x, int y); // El usuario ha pinchado con el rat�n en la posici�n x, y
int clickX = -1, clickY;   // Coordenadas donde el usuario hizo clic

/* Variables globales que pueden serte �tiles */
int anchoV, altoV;		// Tama�o actual de la ventana
bool mostrarEjes = false;	// Mostrar ejes?


/* Variables para el modo de exploraci�n de objetos */
static float lat=35, lon=0;  // Direcci�n de la posici�n de la c�mara
static float dist2Obj=3;    // Distancia de la c�mara al objeto
static int ultx, ulty;	// �ltima posici�n del puntero del rat�n
#define DEG_PER_WIDTH 580.0f // Girar tantos grados por ancho de ventana
#define DEG_PER_HEIGHT 360.0f // Girar tantos grados por alto de ventana
#define DIST_PER_HEIGHT 5.0f  // Acercar/alejar tantas unidades por alto de ventana

// Nada
#define MODE_NONE 0
// Acercar / alejar la c�mara
#define MODE_DISTANCE 1
// Rotar la c�mara alrededor del objeto
#define MODE_ROTATE 2
static int mode = MODE_NONE;   // Tipo de movimiento de la c�mara

/* Declaraci�n adelantada de funciones de ayuda */
void drawAxis(float length);
void init(void);
void onReshape(int w, int h);

bool game_over = false;
int n_rmplace = 9;
std::string str_winner = "No winner.";
time_t c_start,t_start, c_end,t_end; 
char str_time[50];
int subwinid;
int winmainid;

/* Escibe una cadena de caracteres en la posici�n actual */
void drawString (char *s)
{
  while (*s)
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, *s++);
};
void subDisplay (void)
{
  /* Borra la subventana */
  glutSetWindow (subwinid);
  glClearColor (0.25, 0.25, 0.25, 0.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* Escibe varias informaciones en la subventana */
  glColor3f (1.0, 0.0, 1.0);
  glRasterPos2f (0.3, 0.65);
  char rmplace[2];
  _itoa(n_rmplace, rmplace, 10);
  std::string buff = rmplace;
  std::string str1= "Remain Place: " + buff;
  drawString (const_cast<char*>(str1.c_str()));

  glRasterPos2f (0.5, 0.3);
  std::string str = "Winner: " + str_winner;
  drawString (const_cast<char*>(str.c_str()));

  glRasterPos2f(0.1, 0.3);
  if (!game_over)
  {	
	c_end = clock();
	t_end = time(NULL) ; 
  }
	sprintf(str_time, "Time: %f s.", difftime(t_end, t_start));
	drawString(str_time);
 
  glutSwapBuffers();
};
void subReshape (int w, int h)
{
  glViewport (0, 0, w, h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluOrtho2D (0.0, 1.0, 0.0, 1.0);
};
/* Esta funci�n se encargad de dibujar la escena */
void onDisplay(void)
{
	glutSetWindow(winmainid);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();

	// En vez de usar gluLookAt, aplico la transformaci�n equivalente.
	// Recuerda que para situar la c�mara, las transformaciones se escriben en el 
	// orden en el que se quieren aplicar, con los par�metros negados
	glTranslatef(0, 0, -dist2Obj);
	glRotatef(lat, 1.0f, 0.0f, 0.0f);
	glRotatef(-lon, 0.0f, 1.0f, 0.0f);

	if (clickX!=-1) {
		// Estamos en modo pick
		glPushMatrix();
		if (!game_over)
		{
			click(clickX, clickY);
		}
		glPopMatrix();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		clickX = -1;
	}

	// Dibujar los ejes
	if (mostrarEjes) drawAxis(1);

    // El objeto se dibuja aqu?
	dibuja();
	glutSetWindow(subwinid);
	glutPostRedisplay();
	glutSetWindow(winmainid);
	// Se intercambian los buffers
	glutSwapBuffers();

	// Comprobaci�n de errores de OpenGL
	static GLenum glerr;
	if ((glerr=glGetError())!=GL_NO_ERROR) {
		fprintf(stderr, "Error OpenGL: %s (0x%X)\n", gluErrorString(glerr), glerr);
	}
}

/* TODO: Funci�n de atenci�n de los eventos de rat�n */
void onMouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
		  if (state == GLUT_DOWN) {
			  /* Guardamos la posici�n actual del puntero */
			  ultx = x;
			  ulty = y;
			  mode = MODE_ROTATE;
		  } else {
			  mode = MODE_NONE;
		  }
         break;
      case GLUT_RIGHT_BUTTON:
		  if (state == GLUT_DOWN) {
			  /* Guardamos la posici�n actual del puntero */
			  ultx = x;
			  ulty = y;
			  mode = MODE_DISTANCE;
          } else mode = MODE_NONE;
         break;
	  case GLUT_MIDDLE_BUTTON:
		  if (state == GLUT_DOWN) {
			clickX=x;
			clickY=altoV-y;
			glutPostRedisplay();
		  }
		  break;
      default:
         break;
   }
}

// GLUT llama a esta funci�n cuando se mueve el rat�n mientras hay un bot�n pulsado
void onMouseMove(int x, int y) 
{
	if (mode == MODE_ROTATE) {
		lon += (ultx-x)*DEG_PER_WIDTH/anchoV;
		if (lon < 0.0) lon += 360;
		else if (lon >= 360.0) lon -= 360;

		lat += (y-ulty)*DEG_PER_HEIGHT/altoV;
		if (lat <= -90.0f) lat = -89.9f;
		else if (lat >= 90.0f) lat = 89.9f;
    } else if (mode == MODE_DISTANCE) {
		dist2Obj += (ulty-y)*DIST_PER_HEIGHT/altoV;
    } 
	ultx=x;
	ulty=y;

    if (mode != MODE_NONE)
	    glutPostRedisplay();
}
   
// TODO: Se ha pulsado la tecla almacenada en "key"
void onKeyDown(unsigned char key, int x, int y) {
	switch(key) {
		case 'E':
		case 'e':
			mostrarEjes=!mostrarEjes;
			break;
		case 'Q':
		case 'q':
		case 27:
			exit(0);
			break;
	}
	// Redibujar el frame
	glutPostRedisplay();
}

void TimerFunc(int type)
{
	if (type == 0)
	{
		subDisplay();
	}
	glutTimerFunc(1000, TimerFunc, 0);
}



int main(int argc, char** argv)
{
	c_start = clock();
	t_start = time(NULL) ; 
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
   glutInitWindowSize (512, 512); 
   glutInitWindowPosition (100, 100);
   winmainid = glutCreateWindow ("GPC");
   init ();

   subwinid = glutCreateSubWindow (winmainid, 5, 5, 200, 100);
   glutDisplayFunc (subDisplay);
   glutReshapeFunc (subReshape);
   glutMainLoop();
   return 0;   
}


// Funci�n para dibujar unos ejes del tama�o dado
void drawAxis(float length) {
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(length, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, length, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, length);
	glEnd();
}



// Inicializaci�n de OpenGL
void init(void) 
{
	char cwd[_MAX_PATH];
	_getcwd(cwd, sizeof(cwd));
	printf("El directorio actual es: %s\n", cwd);

	glClearColor (0.0, 0.0, 0.0, 0.0);

   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glutDisplayFunc(onDisplay); 
   glutReshapeFunc(onReshape); 
   glutKeyboardFunc(onKeyDown);
   glutMouseFunc(onMouse);
   glutMotionFunc(onMouseMove);
   glutTimerFunc(1000, TimerFunc, 0); 

   inicia();
   
}

/* Callbacks */
// Definici�n de la c�mara y del viewport, siempre que se cambie el tama�o de la ventana
void onReshape(int w, int h)
{
	if (h==0) h=1;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)w/h, 0.01, 10); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	anchoV=w;
	altoV=h;

	glutSetWindow (subwinid);
	glutReshapeWindow (w - 10, h / 10);
	glutPositionWindow (5, 5);
	glutSetWindow (winmainid);
}
