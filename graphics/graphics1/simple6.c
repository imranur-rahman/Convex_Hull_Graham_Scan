/*  
    simple6.c 
   
    Draws a cube in 3D. 
 
    For 3D rendering: 
    //initialize depth buffer 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
    //enable depth testing 
    glEnable(GL_DEPTH_TEST); 
    //setup camera 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(..); 

    when rendering, use glVertex3f(..) instead of glVertex2f(..)


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
void draw_xy_rect(GLfloat z, GLfloat* c); 
void draw_cube(GLfloat z1, GLfloat z2); 

 
 
 
int main(int argc, char** argv) { 
 
  /* open a window and initialize GLUT stuff */ 
  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
  //note: in 3D need to also initialize depth buffer  
  glutInitWindowSize(WINDOWSIZE, WINDOWSIZE);
  glutInitWindowPosition(100,100); 
  glutCreateWindow(argv[0]); 
  
  /* register callback functions */
  glutDisplayFunc(display); 
  glutKeyboardFunc(keypress);
  
  /* OpenGL init */ 
  /* set background color black*/ 
  glClearColor(0, 0, 0, 0);  
  /* note: in 3D need to enable depth-testing.  This triggers hidden
     surface removal */
  glEnable(GL_DEPTH_TEST); 
  
  /* setup the camera (i.e. the projection transformation) */ 
  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity(); 
  gluPerspective(60, 1, 1, 10.0); 
  /* aspect=1; the frustrum is from z=-1 to z=-10 */ 
  /* DEFAULT: camera is at (0,0,0) looking along negative z axis */ 
 
  /* start the event handler */ 
  glutMainLoop(); 
  
  return 0; 
} 
 



/* this function is called whenever  key is pressed */
void keypress(unsigned char key, int x, int y) { 
  switch(key) { 
  case 'q': 
    exit(0); 
    break; 
  } 
} 
 
 
/* this function is called whenever the window needs to be rendered */
void display(void) { 

  //clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 
  //clear all modeling transformations 
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
  
  /* The default GL window is x=[-1,1], y= [-1,1] with the origin in
     the center. The view frustrum was set up from z=-1 to z=-10. The
     camera is at (0,0,0) looking along negative z axis. 
  */ 

  //this won't show anything, because it's right on the edge of the 
  //view frustrum and the camera is inside it at position (0,0,0) 
  //draw_cube(1, -1);  we need to translate it first
 
  glTranslatef(0,0,-3); 
  draw_cube(1, -1); 
  
  /* execute the drawing commands */
  glFlush(); 
} 
 
 




//draw a rectangle  x=[-1,1]  by y= [-1,1]  at specified z, of specified color 
void draw_xy_rect(GLfloat z,  GLfloat* c) { 
  glColor3fv(c); 
  glBegin(GL_POLYGON); 
  glVertex3f(-1,-1, z); 
  glVertex3f(-1,1, z); 
  glVertex3f(1,1, z); 
  glVertex3f(1,-1, z); 
  glEnd(); 
} 
 

void draw_cube(GLfloat z1, GLfloat z2) { 
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
 
  //front face at z=z1 with RED 
  draw_xy_rect(z1,red); 
 
  //back face at z=z2 with BLUE 
  draw_xy_rect(z2,blue); 
 
  //draw the sides  
  glColor3fv(yellow); 
  glBegin(GL_POLYGON); 
  glVertex3f(-1,-1, z1); 
  glVertex3f(-1,1, z1); 
  glVertex3f(-1,1, z2); 
  glVertex3f(-1,-1, z2); 
  glEnd(); 
 
  glColor3fv(cyan); 
  glBegin(GL_POLYGON); 
  glVertex3f(1,-1, z1); 
  glVertex3f(1,1, z1); 
  glVertex3f(1,1, z2); 
  glVertex3f(1,-1, z2); 
  glEnd(); 
}
 
 
