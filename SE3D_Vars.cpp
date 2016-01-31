// Scorched Earth 3D
// File: SE3D_Vars.cpp
// Description: Includes, Globals, Structures

#include "glut.h"
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include "png/glpng.h"

#define C_POINTS 20

// Various Globals
int phy,turn,p1mode,p2mode,tex1,tank1x,tank1y,tank1z,tank2x,tank2y,tank2z;
double xa,ya,za,px,pz,t1y,t2y,height,xe,ze,win,t2a,t1a,s1,s2;

	int plot[401][401];
	int points[C_POINTS][2],m,n;
	double detailBias;

// Projectile point display list
struct linelist {
	double xl,yl,zl;
	linelist *next;
};
linelist *listf,*liste;