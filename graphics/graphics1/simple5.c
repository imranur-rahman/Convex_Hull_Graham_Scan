/* simple5.c 
   
   Same as simple4.c,  but with a timerfunc() that increases the radious of the polygon. 
   
   OpenGL 1.x
   Laura Toma
 */



#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
//this allows this code to compile both on apple and linux platforms
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


/* global variables */
const int WINDOWSIZE = 500; 

//we predefine some colors for convenience 
GLfloat red[3] = {1.0, 0.0, 0.0};
GLfloat green[3] = {0.0, 1.0, 0.0};
GLfloat blue[3] = {0.0, 0.0, 1.0};
GLfloat black[3] = {0.0, 0.0, 0.0};
GLfloat white[3] = {1.0, 1.0, 1.0};
GLfloat gray[3] = {0.5, 0.5, 0.5};
GLfloat yellow[3] = {1.0, 1.0, 0.0};
GLfloat magenta[3] = {1.0, 0.0, 1.0};
GLfloat cyan[3] = {0.0, 1.0, 1.0};

GLint fillmode = 0;
float r = .1; //initial radius 
int n = 6; 


/* this is the global translation; it is updated when the user presses
   L/R/U/D */
GLfloat pos[3] = {0,0,0};


/* the radius in the animated polygon is increasing or decreasing */
#define  DECREASING  0
#define INCREASING  1
int mode = INCREASING;  //whether the radius is increasing or decreasing 


/* forward declarations of functions */
void display(void);
void keypress(unsigned char key, int x, int y);
void  timerfunc(); 
void draw_ngon(); 



int main(int argc, char** argv) {

    /* open a window and initialize GLUT stuff */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(WINDOWSIZE, WINDOWSIZE);
  glutInitWindowPosition(100,100);
  glutCreateWindow(argv[0]);
  
  /* register callback functions */
  glutDisplayFunc(display); 
  glutKeyboardFunc(keypress);
  glutIdleFunc(timerfunc); 

  /* OpenGL init */
  /* set background color black*/
  glClearColor(0, 0, 0, 0);   

  /* start the event handler */
  glutMainLoop();

  return 0;
}



/* draw n-gon with n vertices and radious r centered at (0,0). Note
   that r and n are global variables that are updated by the
   keypress() function */
void draw_ngon() {

  int i; 
  float a = 2*M_PI/n; 
 
  if (fillmode) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  
 /* draw a polygon with n vertices  centered at (0,0) */
  glBegin(GL_POLYGON);
  for (i=0; i<= n; i++) {
    glVertex2f(r*cos(a*i), r*sin(a*i));
  }
  glEnd();
}


/* this function is called whenever the window needs to be rendered */
void display(void) {

  //clear the screen
  glClear(GL_COLOR_BUFFER_BIT);
 //clear all transformations 
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();

  /* The default GL window is [-1,1]x[-1,1] with the origin in the
     center
  */ 
  
  /* First we translate our local reference system. pos[] represents
     the cumulative translation entered by the user */
  glTranslatef(pos[0], pos[1], pos[2]); 

  /* Now we draw the object in the local reference system. Note that
     we always draw the polygon in the local system, and we translate the
     system. */
  draw_ngon();
  
  /* execute the drawing commands */
  glFlush();
}



/* this function is called whenever  key is pressed */
void keypress(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    exit(0);
    break;

  case '+': 
    r *= 1.1; 
    glutPostRedisplay();
    break; 
  case '-': 
    r *= .9; 
    glutPostRedisplay();
    break; 
	
  case '<': 
    n--; 
    glutPostRedisplay();
    break; 
	
  case '>': 
    n++; 
    glutPostRedisplay();
    break; 

  case 'l': 
	pos[0] -= 0.2; 
	glutPostRedisplay();
	break; 
  case 'r': 
	pos[0] += 0.2; 
	glutPostRedisplay();
	break;

  case 'u': 
    pos[1] += 0.2;
    glutPostRedisplay();
    break;

  case 'd': 
    pos[1] -= 0.2;
    glutPostRedisplay();
    break;

  case 'f': 
    fillmode = !fillmode; 
    glutPostRedisplay();
    break;
    
  } 
}




/* this function is called every millisecond or so, if the */ 
void timerfunc() {
  
  //if the radius is increasing and it got larger than 1, switch to DECREASING
  if (mode == INCREASING && r >1) {
    mode = DECREASING; 
  }
  //if the radius is decreasing and it got too small, switch to INCREASING
  if (mode == DECREASING && r < .1) {
    mode = INCREASING; 
  }
  
  //update the radius based on the mode 
  if (mode == INCREASING) 
    r  *=  1.01; 
  if (mode == DECREASING)  
    r /= 1.01; 

  //call display()
  glutPostRedisplay(); 

}
