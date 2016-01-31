// Scorched Earth 3D
// File: SE3D_Init.cpp
// Description: Various initialization routines

void seInitialize(void)
{
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutCreateWindow("3D Scorched Earth");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 4/3, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0,0,0,0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	tank1x=50;
	tank1z=30;
	tank2x=-100;
	tank2z=-80;
	t1y=-90;
	t2y=90;
	turn=1;
	t1a=60;
	t2a=60;
	s1=s2=200;
	p1mode=p2mode=1;

	glLineWidth(3.0);
	tex1=pngBind("ground.png",0,PNG_SOLID,NULL,GL_REPEAT,GL_NEAREST,GL_NEAREST);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glEnable(GL_LIGHTING); 

	GLfloat ambience[]={.5,.2,.2,1};
	GLfloat color[]={.3,.1,0,1};
	GLfloat specular[]={.5,.9,.9,1};
	
	glEnable(GL_LIGHT0);
	glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,.3);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambience);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,45);
	glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,color);
	glMaterialfv(GL_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);

	glLoadIdentity();

	listf=new linelist;
	liste=new linelist;
	listf=liste;
	listf->next=liste;
	liste->next=NULL;
}