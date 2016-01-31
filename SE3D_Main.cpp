// Scorched Earth 3D
// File: SE3D_Main.cpp
// Description: Main program file

// Author: Dave Kahler

// Last Modified: 2000.10.14
// Features currently implemented:
//   3D Plane with camera rotation and rotation-corrected translation
//   Primitive tank display list defined
//   Camera locked into a floating position and plane rotates
//   Physics vector trajectory system implemented
//   Landscape/Tank mode implemented
//   Game works
//   Text algorithm finalized, code cleaned up
//   4 corner lights working, modulated with textures
//   3D Terrain algorithm replaced with Cubic Bezier patch generator
//   Normals calculated correctly to simulate good lighting
//   4 Lights replaced with one due to bezier patch issues

// Todo:
//   

#include "SE3D_Vars.cpp"
#include "SE3D_Math.cpp"
#include "SE3D_Text.cpp"
#include "SE3D_Init.cpp"
#include "SE3D_Land.cpp"

// Sets up the tank display list
void seGenerateTank()
{
	glNewList(1,GL_COMPILE);
	 glBegin(GL_POLYGON);
	  glVertex3f(-5,0,-5);
	  glVertex3f(-5,0,5);
	  glVertex3f(5,0,5);
	  glVertex3f(5,0,-5);
	 glEnd();
	 glBegin(GL_POLYGON);
	  glVertex3f(-5,0,-5);
	  glVertex3f(-5,-3,-5);
	  glVertex3f(-5,-3,5);
	  glVertex3f(-5,0,5);
	 glEnd();
	 glBegin(GL_POLYGON);
	  glVertex3f(5,0,-5);
	  glVertex3f(5,-3,-5);
	  glVertex3f(5,-3,5);
	  glVertex3f(5,0,5);
	 glEnd();
	 glBegin(GL_POLYGON);
	  glVertex3f(-5,0,-5);
	  glVertex3f(-5,-3,-5);
	  glVertex3f(5,-3,-5);
	  glVertex3f(5,0,-5);
	 glEnd();
	 glBegin(GL_POLYGON);
	  glVertex3f(-5,-3,-8);
	  glVertex3f(-5,-3,-5);
	  glVertex3f(5,-3,-5);
	  glVertex3f(5,-3,-8);
	 glEnd();
	 glBegin(GL_POLYGON);
	  glVertex3f(-5,0,5);
	  glVertex3f(-5,-3,5);
	  glVertex3f(5,-3,5);
	  glVertex3f(5,0,5);
	 glEnd();
	 glBegin(GL_POLYGON);
	  glVertex3f(-5,-3,5);
	  glVertex3f(-5,-3,8);
	  glVertex3f(5,-3,8);
	  glVertex3f(5,-3,5);
	 glEnd();
	 glBegin(GL_POLYGON);
	  glVertex3f(-2,0,-5);
	  glVertex3f(2,0,-5);
	  glVertex3f(2,4,-9);
	  glVertex3f(-2,4,-9);
	 glEnd();
	glEndList();
}

// The all important display function
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// ONE - Display Text
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,800,0,600);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	se_interface();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 4/3, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_LIGHTING);
	// End ONE


	// TWO - Set up the field view
	glPushMatrix();

	glLoadIdentity();

	if ((turn==1 && p1mode==1) || (turn==2 && p2mode==1)) {
		glTranslatef(0,150,-450);
		glRotatef(ya,0,1,0);
	}
	if (turn==1 && p1mode==2) {
		glRotatef(t1y,0,-1,0);
		glTranslatef(-tank1x,300,-tank1z);
	}
	if (turn==2 && p2mode==2) {
		glRotatef(t2y,0,-1,0);
		glTranslatef(-tank2x,300,-tank2z);
	}
	GLfloat position1[]={0,0,0,1};
	glLightfv(GL_LIGHT0,GL_POSITION,position1);
	GLfloat direction1[]={0,-1,0};
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,direction1);

	glLoadIdentity();

	if ((turn==1 && p1mode==1) || (turn==2 && p2mode==1)) {
		glTranslatef(0,-150,-450);
		glRotatef(ya,0,1,0);
	}
	if (turn==1 && p1mode==2) {
		glRotatef(t1y,0,-1,0);
		glTranslatef(-tank1x,-tank1y-7,-tank1z);
	}
	if (turn==2 && p2mode==2) {
		glRotatef(t2y,0,-1,0);
		glTranslatef(-tank2x,-tank2y-7,-tank2z);
	}
	// End TWO
	

	// THREE - Display tanks and plane
	glDisable(GL_LIGHTING);
	glColor3f(1,0,0);
	glPushMatrix();
	 glTranslatef(tank1x,tank1y,tank1z);
	 glRotatef(t1y,0,1,0);
	 glColor3f(1,0,0);
	 glCallList(1);
	glPopMatrix();
	glPushMatrix();
	 glTranslatef(tank2x,tank2y,tank2z);
	 glRotatef(t2y,0,1,0);
	 glColor3f(0,0,1);
	 glCallList(1);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,tex1);

	se_disp_terrain();
	// End THREE


	// FOUR - Draw Projectile
	linelist *trav=listf->next;
	if (phy==1) {
		glDisable(GL_LIGHTING);
		if (turn==1)
			glColor3f(1,0,0);
		if (turn==2)
			glColor3f(0,0,1);
		while (trav->next!=NULL) {
			glPushMatrix();
			glBegin(GL_LINES);
			 glVertex3f(trav->xl,trav->yl,trav->zl);
			 glVertex3f(trav->next->xl,trav->next->yl,trav->next->zl);
			glEnd();
			trav=trav->next;
			glPopMatrix();
			glutSwapBuffers();
		}
		if (win==0) {
			glDisable(GL_LIGHTING);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluOrtho2D(0,800,0,600);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			dispstring("Miss!",0,300);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(70, 4/3, 1, 1000);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glEnable(GL_LIGHTING);
		}
		if (turn==1)
			turn=2;
		else turn=1;

		phy=0;
		glEnable(GL_LIGHTING);
	}
	// End FOUR


	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

// Keypress function
void keyboard(unsigned char keypress,int w,int h)
{
	if (keypress=='.')
		ya+=-5;
	if (keypress==',') 
		ya+=5;
	if (turn==1) {
		if (keypress=='[')
			t1y-=2;
		if (keypress==']')
			t1y+=2;
	}
	else {
		if (keypress==']')
			t2y-=2;
		if (keypress=='[')
			t2y+=2;
	}
	if (keypress=='z' && turn==1)
		project(t1a,t1y+180,1);
	if (keypress=='z' && turn==2)
		project(t2a,t2y+180,2);
	if (keypress=='q' && turn==1)
		t1a+=5;
	if (keypress=='a' && turn==1)
		t1a-=5;
	if (keypress=='q' && turn==2)
		t2a+=5;
	if (keypress=='a' && turn==2)
		t2a-=5;
	if (keypress=='w' && turn==1 && s1<=400)
		s1+=5;
	if (keypress=='s' && turn==1 && s1>0)
		s1-=5;
	if (keypress=='w' && turn==2 && s2<=400)
		s2+=5;
	if (keypress=='s' && turn==2 && s2>0)
		s2-=5;
	if (keypress=='p' && turn==1) {
		if (p1mode==1)
			p1mode=2;
		else p1mode=1;
	}
	if (keypress=='p' && turn==2) {
		if (p2mode==1)
			p2mode=2;
		else p2mode=1;
	}

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	seInitialize();                    // Setup various values
	seGenerateTerrain();               // Generate random cubic bezier patch
	seInterpolatePlot();               // Set all values in plot[][] array to something relevant
	seGenerateTankPos();               // Set tank location
	seGenerateTank();                  // Call the tank display list to put it into memory

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}