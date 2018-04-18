/* 
   simple3.c 

   draws a scene made of lines, points and polygons 

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
void draw_polygon(); 
void draw_rectangle(); 
void draw_lines();
void draw_line_fan(); 
void draw_points(); 



int main(int argc, char** argv) {

  /* open a window  and initialize GLUT stuff */
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

  /* give control to the event handler */
  glutMainLoop();

  return 0;
}



/* this function is called whenever the window needs to be rendered */
void display(void) {
  
  //clear the screen
  glClear(GL_COLOR_BUFFER_BIT );
  //clear all transformations 
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();


  /* the default GL window is [-1,1]x[-1,1] with the origin in the
     center. draw some objects  with vertices in [-1,1]x[-1,1] 
  */
  draw_polygon();
  draw_rectangle();
  draw_lines();
  draw_line_fan();
  draw_points();

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




/* draw a polygon with vertices in [-1,1]x[-1,1] */
void draw_polygon(){

  //contour only 
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  /* set draw color blue */
  glColor3fv(blue);  
  
  glBegin(GL_POLYGON);
  glVertex2f(-0.5,-0.5);
  glVertex2f(-0.5,0.5);
  glVertex2f(0.5,0.5);
  glVertex2f(0.5,-0.5);
  glEnd();
}

/* draw a polygon with vertices in [-1,1]x[-1,1] */
void draw_rectangle() {
  glColor3fv(red);  //set color red
  glRectf(0.0, 0.0, 0.2, 0.3);
}

/* draw some lines in [-1,1]x[-1,1] */
void draw_lines() {
  //set color yellow 
  glColor3fv(yellow);
  glBegin(GL_LINES);
  glVertex2f(-1.0,-1.0);
  glVertex2f(1.0,1.0);
  glVertex2f(-1.0,-0.8);
  glVertex2f(1.0,0.8);
  glEnd();
}

/* draw a line fan in [-1,1]x[-1,1] */
void draw_line_fan() {
  int i;
  float step=0.1, x0 = 0.3,y0=0.3, x1,x2,y1,y2;

  glColor3fv(green); //set color green 
  for (i=0; i<10; i++) {
    x1 = x0+ i*step;
    y1 = y0;
    x2 = x0;
    y2 = y0+i*step;
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
  }
}

/* draw some point in [-1,1]x[-1,1] */
void draw_points() {
  int i;
  glColor3fv(cyan);
  glBegin(GL_POINTS);
  for (i=0; i<10;i++) {
    glVertex2f(-0.5+i*0.03, 0.8);   
  }
  glEnd();
}



