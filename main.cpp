// Scorched Earth 3D
// File: main.cpp
// Description: Main program file

// Author: Dave Kahler

// Last Modified: 2000.6.17
// Features currently implemented:
//   3D Plane with camera rotation and rotation-corrected translation
//   Primitive tank display list defined
//   Camera locked into a floating position and plane rotates
//   Physics vector trajectory system implemented
//   Landscape/Tank mode implemented
//   Game works
//   Text algorithm finalized, code cleaned up

#include "SE3D_Vars.cpp"
#include "SE3D_Math.cpp"
#include "SE3D_Text.cpp"
#include "SE3D_Init.cpp"
#include "SE3D_Land.cpp"

// Sets up the tank display list
void tank()
{
	glNewList(1,GL_COMPILE);
	 glColor3f(0,0,0);
	 glBegin(GL_POLYGON);
	  glVertex3f(-5,0,-5);
	  glVertex3f(-5,0,5);
	  glVertex3f(5,0,5);
	  glVertex3f(5,0,-5);
	 glEnd();
	 glColor4f(.3,.6,0,0);
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
		glTranslatef(0,-100,-450);
		glRotatef(ya,0,1,0);
		GLfloat position3[]={-200,40,200,1};
		glLightfv(GL_LIGHT3,GL_POSITION,position3);
		GLfloat direction3[]={-1,-1,1};
		glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,direction3);

		glLoadIdentity();
		glTranslatef(0,-100,-450);
		glRotatef(ya,0,1,0);
		GLfloat position2[]={200,40,-200,1};
		glLightfv(GL_LIGHT2,GL_POSITION,position2);
		GLfloat direction2[]={1,-1,-1};
		glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,direction2);

		glLoadIdentity();
		glTranslatef(0,-100,-450);
		glRotatef(ya,0,1,0);
		GLfloat position1[]={-200,40,-200,1};
		glLightfv(GL_LIGHT1,GL_POSITION,position1);
		GLfloat direction1[]={1,-1,1};
		glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction1);

		glLoadIdentity();
		glTranslatef(0,-100,-450);
		glRotatef(ya,0,1,0);
		GLfloat position[]={200,40,200,1};
		glLightfv(GL_LIGHT0,GL_POSITION,position);
		GLfloat direction[]={-1,-1,-1};
		glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,direction);
		glLoadIdentity();

		glTranslatef(0,-100,-450);
		glRotatef(ya,0,1,0);

	if (turn==1 && p1mode==2) {
		glRotatef(t1y,0,-1,0);
		glTranslatef(-tank1x,-10,-tank1z);
	}
	if (turn==2 && p2mode==2) {
		glRotatef(t2y,0,-1,0);
		glTranslatef(-tank2x,-10,-tank2z);
	}
	// End TWO
	
	// THREE - Display tanks and plane

	//glEnable(GL_SCISSOR_TEST);
	glPushMatrix();
	 glTranslatef(tank1x,5,tank1z);
	 glRotatef(t1y,0,1,0);
	 glCallList(1);
	glPopMatrix();
	glPushMatrix();
	 glTranslatef(tank2x,5,tank2z);
	 glRotatef(t2y,0,1,0);
	 glCallList(1);
	glPopMatrix();
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,tex1);
	GLfloat color[]={.05,.4,.1,1};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	glNormal3f(0,1,0);
	for (int i=0;i<=400;i+=10) {
		for (int j=0;j<=400;j+=10) {
			glBegin(GL_POLYGON);
			 glTexCoord2f(0,0);
			 glVertex3f(-200+j,0,-200+i);
			 glTexCoord2f(0,1);
			 glVertex3f(-200+j+10,0,-200+i);
			 glTexCoord2f(1,0);
			 glVertex3f(-200+j+10,0,-200+i+10);
			 glTexCoord2f(1,1);
			 glVertex3f(-200+j,0,-200+i+10);
			glEnd();
		}
	}

	se_disp_terrain();
	//glDisable(GL_SCISSOR_TEST);
	// End THREE

	// FOUR - Draw Projectile
	linelist *trav=listf->next;
	if (phy==1) {
		while (trav->next!=NULL) {
			glPushMatrix();
			glColor3f(0,0,0);
			glBegin(GL_LINES);
			 glVertex3f(trav->xl,trav->yl,trav->zl);
			 glVertex3f(trav->next->xl,trav->next->yl,trav->next->zl);
			glEnd();
			trav=trav->next;
			glPopMatrix();
			glutSwapBuffers();
		}
		if (win==0) {
			dispstring("Miss!",0,300);
		}
		if (turn==1)
			turn=2;
		else turn=1;

		phy=0;
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
		ya+=-10;
	if (keypress==',') 
		ya+=10;
	if (turn==1) {
		if (keypress=='[')
			t1y-=5;
		if (keypress==']')
			t1y+=5;
	}
	else {
		if (keypress==']')
			t2y-=5;
		if (keypress=='[')
			t2y+=5;
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
	SE3D_Init_Param();
	se_Generate_Terrain();
	glScissor(0,82,800,518);

	// Call the tank display list to put it into memory
	tank();

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}