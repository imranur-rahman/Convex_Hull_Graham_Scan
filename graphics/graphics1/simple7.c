/* simple7.c 

   Draws in 3D, and translates/rotates it when user presses l/r/u/d/x/X,y/Y,z/Z.

   The translation is 

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


//keep track of global translation and rotation 
GLfloat pos[3] = {0,0,0};
GLfloat theta[3] = {0,0,0};

//cube drawn line or filled 
GLint fillmode = 0; 

/* forward declarations of functions */
void display(void);
void keypress(unsigned char key, int x, int y);
void draw_xy_rect(GLfloat z, GLfloat* color); 
void draw_cube(GLfloat z1, GLfloat z2); 
void draw_xy_rect(GLfloat z, GLfloat* col); 
void draw_xz_rect(GLfloat y, GLfloat* col); 
void draw_yz_rect(GLfloat x, GLfloat* col); 
void cube(); 
void draw_axes(); 



int main(int argc, char** argv) {

    /* open a window and initialize GLUT stuff */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(WINDOWSIZE, WINDOWSIZE);
  glutInitWindowPosition(100,100);
  glutCreateWindow(argv[0]);

  /* register callback functions */
  glutDisplayFunc(display); 
  glutKeyboardFunc(keypress);
  
  /* OpenGL init */
  /* set background color black*/
  glClearColor(0, 0, 0, 0);  
  glEnable(GL_DEPTH_TEST); 

  /* setup the camera (i.e. the projection transformation) */ 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, 1 /* aspect */, 1, 10.0); /* the frustrum is from z=-1 to z=-10 */
  /* camera is at (0,0,0) looking along negative y axis */
  
  //initialize the translation to bring the cube it in the view frustrum
  pos[2] = -5;

  //move it down, look at it from above 
  //pos[1] = -1.3;

  /* start the event handler */
  glutMainLoop();

  return 0;
}




/* this function is called whenever the window needs to be rendered */
void display(void) {

  //clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //clear all modeling transformations 
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();

  /* The default GL window is x=[-1,1], y= [-1,1] with the origin in
     the center.  The view frustrum was set up from z=-1 to z=-10. The
     camera is at (0,0,0) looking along negative z axis.
  */ 

 /* First we translate our local reference system. pos[] represents
    the cumulative translation entered by the user, and theta[] the
    rotation */
  glTranslatef(pos[0], pos[1], pos[2]);  
  glRotatef(theta[0], 1,0,0); //rotate theta[0] around x-axis
  glRotatef(theta[1], 0,1,0);
  glRotatef(theta[2], 0,0,1);
  
  /* Now we draw the object in the local reference system. Note that
     we draw the object in the local system, and we translate
     the system. */
  draw_axes();  
  cube();

  glFlush();
}



/* this function is called whenever  key is pressed */
void keypress(unsigned char key, int x, int y) {

  switch(key) {

    //ROTATIONS 
  case 'x':
    theta[0] += 5.0; 
    glutPostRedisplay();
    break;
  case 'y':
    theta[1] += 5.0;
    glutPostRedisplay();
    break;
  case 'z':
    theta[2] += 5.0;
    glutPostRedisplay();
    break;
  case 'X':
    theta[0] -= 5.0; 
    glutPostRedisplay();
    break;
  case 'Y':
    theta[1] -= 5.0; 
    glutPostRedisplay();
    break;
  case 'Z':
    theta[2] -= 5.0; 
    glutPostRedisplay();
    break;
    
    //TRANSLATIONS 
    //backward (zoom out)
  case 'b':
    pos[2] -= 0.5; 
    glutPostRedisplay();
    break;
    //forward (zoom in)
  case 'f':
    pos[2] += 0.5; 
    //glTranslatef(0,0, 0.5);
    glutPostRedisplay();
    break;
    //down 
  case 'd': 
     pos[1] -= 0.5; 
    //glTranslatef(0,0.5,0);
    glutPostRedisplay();
    break;
    //up
  case 'u': 
    pos[1] += 0.5; 
    //glTranslatef(0,-0.5,0);
    glutPostRedisplay();
    break;
    //left 
  case 'l':
    pos[0] -= 0.5; 
    glutPostRedisplay();
    break;
    //right
  case 'r':
    pos[0] += 0.5; 
    glutPostRedisplay();
    break;

    //fillmode 
  case 'c': 
    fillmode = !fillmode; 
     glutPostRedisplay();
    break;

  case 'q':
    exit(0);
    break;
  } 
}//keypress





//draw a square x=[-1,1], y=[-1,1] at depth z
void draw_xy_rect(GLfloat z, GLfloat* col) {
  glColor3fv(col);
  glBegin(GL_POLYGON);
  glVertex3f(-1,-1, z);
  glVertex3f(-1,1, z);
  glVertex3f(1,1, z);
  glVertex3f(1,-1, z);
  glEnd();
}


//draw a square y=[-1,1], z=[-1,1] at given x
void draw_yz_rect(GLfloat x, GLfloat* col) {
  glColor3fv(col);
  glBegin(GL_POLYGON);
  glVertex3f(x,-1, 1);
  glVertex3f(x,1, 1);
  glVertex3f(x,1, -1);
  glVertex3f(x,-1, -1);
  glEnd();
}


//draw a square x=[-1,1], z=[-1,1] at given y
void draw_xz_rect(GLfloat y, GLfloat* col) {
  glColor3fv(col);
  glBegin(GL_POLYGON);
  glVertex3f(-1,y, 1);
  glVertex3f(-1,y, -1);
  glVertex3f(1,y, -1);
  glVertex3f(1,y, 1);
  glEnd();
}

//draw a cube 
void cube() {
  GLfloat f = 1, b = -1;
 

  if (fillmode) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }


  /* back face  BLUE*/
  draw_xy_rect(b,blue);
  /* side faces  GREEN*/
  draw_yz_rect(-1, green);
  draw_yz_rect(1, green);
  /* front face  RED*/
  draw_xy_rect(f,red);

  /* middle z=0 face CYAN*/
  draw_xy_rect(0, cyan);
  /* middle x=0 face CYAN*/
  draw_yz_rect(0,cyan);
  /* middle y=0 face  CYAN*/
  draw_xz_rect(0,cyan);
}

void draw_axes() {
  glColor3fv(yellow); //yellow
  glBegin(GL_LINES);
  glVertex3i(-1,0,0);
  glVertex3i(1,0,0);
  glVertex3i(0,1,0);
  glVertex3i(0,-1,0);
  glVertex3i(0,0,1);
  glVertex3i(0,0,-1);
  glEnd();
}


