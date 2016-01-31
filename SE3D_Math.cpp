// Scorched Earth 3D
// File: SE3D_Math.cpp
// Description: Math algorithms

// Degree cosine
double dcos(double angle)
{
	return (cos((angle/180)*3.141592653589));
}

// Degree sine
double dsin(double angle)
{
	return (sin((angle/180)*3.141592653589));
}

// Tests for a particle collision with the playing surface (Since the surface is a plane right now,
//  this function is currently trivial)
int IsCollision(int collx,int collz)
{
	printf("\nCOLL: %d %d   %d\n",collx,collz,plot[collx+200][collz+200]);
	if (height>plot[collx+200][collz+200] && plot[collx+200][collz+200]!=0)
		return 0;
	if (height>plot[collx+200+1][collz+200+1] && plot[collx+200][collz+200]==0)
		return 0;
	return 1;
}

// Determines the flight path of the projectile
void project(double theta,double beta,int tank)
{
	double projx,projz;
	phy=1;
	const double fg=1;
	struct vector {
		double i,j,m;
	};
	vector P;

	if (turn==1) {
		p1mode=1;
		P.m=s1;
	}
	if (turn==2) {
		p2mode=1;
		P.m=s2;
	}

	P.i=P.m*dcos(theta);
	P.j=P.m*dsin(theta);
	printf("%f\n",P.i);
	if (tank==1) {
		projx=tank1x;
		height=tank1y;
		projz=tank1z;
	}
	else {
		projx=tank2x;
		height=tank2y;
		projz=tank2z;
	}

	// Delete the previous LL
	linelist *prev,*now=listf;
	while (now!=NULL) {
		prev=now;
		now=now->next;
		delete prev;
	}
	listf=new linelist;
	liste=new linelist;
	listf=liste;
	listf->next=liste;
	liste->next=NULL;


	do {
		projx+=(P.m*dcos(theta)*dsin(beta))/500;
		projz+=(P.m*dcos(theta)*dcos(beta))/500;
		height+=P.j/500;
		P.j-=fg;
		
		linelist *mlist=new linelist;
		mlist->xl=projx;
		mlist->yl=height;
		mlist->zl=projz;
		liste->next=mlist;
		liste=mlist;

	} while (!IsCollision(projx,projz));
	liste->next=NULL;
	xe=liste->xl;
	ze=liste->zl;
	if (tank==1)
		if ((xe>(tank2x-5)) && (xe<(tank2x+5)) && (ze>(tank2z-5)) && (ze<(tank2z+5)))
			win=1;
	if (tank==2)
		if ((xe>(tank1x-5)) && (xe<(tank1x+5)) && (ze>(tank1z-5)) && (ze<(tank1z+5)))
			win=2;
}

//calc norm of two vectors
void cross(double u_i,double u_j,double u_k,double v_i,double v_j,double v_k,double *norm_i,double *norm_j,double *norm_k)
{
	*norm_i=((v_k*u_j)-(v_j*u_k));
	*norm_j=-((v_k*u_i)-(v_i*u_k));
	*norm_k=((v_j*u_i)-(v_i*u_j));
}
