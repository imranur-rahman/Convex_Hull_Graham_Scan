/* 
   simple1.c 
   
   draws a white filled rectangle on a black background  in 2D
 
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




/* forward declarations of functions */
void display(void);
void keypress(unsigned char key, int x, int y);
void draw_something(); 



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
  
  /* OpenGL init */
  /* set background color black*/
  glClearColor(0, 0, 0, 0);   
  /* here we can enable depth testing and double buffering and so on */

  /* give control to the event handler */
  glutMainLoop();

  return 0;
}


/* this function is called whenever the window needs to be rendered */
void display(void) {
  //clear the screen
  glClear(GL_COLOR_BUFFER_BIT); 
 //clear all transformations 
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
  
  /* the default GL window is [-1,1]x[-1,1] with the origin in the
     center  */
  draw_something(); 
  
  /* execute the drawing commands */
  glFlush();
}




/* this function is called whenever  key is pressed */
void keypress(unsigned char key, int x, int y) {
  switch(key) {
  case 'q':
    exit(0);
    break;
  } 
}


/* draw something  in [-1,1]x[-1,1]*/
void draw_something() {

  //set polygons style: filled or contour 
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
  glColor3fv(white);   /* set draw color white */

  glBegin(GL_POLYGON);
  glVertex2f(-0.5,-0.5);
  glVertex2f(-0.5,0.5);
  glVertex2f(0.5,0.5);
  glVertex2f(0.5,-0.5);
  glEnd();
}
