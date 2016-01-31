

#include <time.h>
#include <stdlib.h>

void seGenerateTankPos()
{

	if (plot[tank1x][tank1z]!=0) {
		tank1y=plot[tank1x+200][tank1z+200]+5;
	}
	else {
		tank1y=plot[tank1x+200+1][tank1z+200+1]+5;
	}
	if (plot[tank2x+200][tank2z+200]!=0) {
		printf("PLOT: %d %d",tank2x+200,tank2z+200);
		tank2y=plot[tank2x+200][tank2z+200]+5;
	}
	else {
		tank2y=plot[tank2x+200+1][tank2z+200+1]+5;
	}

	printf("%d %d\n",tank1y,tank2y);
}

void se_debug_plot(void)
{
	int i,j;

	for (i=0;i<=400;i++) {
		for (j=0;j<=400;j++) {
			printf("%d",plot[i][j]);
			getch();
		}
	}
}

void seInterpolatePlot(void)
{
	int i,j,temph,k;

	for (i=0;i<=400;i++) {
		j=0;
		while (j<=400) {
			temph=plot[i][j];
			if (plot[i][j]!=temph && plot[i][j]!=0) {
				for (k=temph;k<=j;k++) {
					plot[i][k]=plot[i][temph]+(k*int((plot[i][j]-plot[i][temph])/(1/detailBias)));
				}
			}
			else {
				if (plot[i][j]==temph)
					j++;
				if (plot[i][j]==0)
					j++;
			}
		}
	}
}

void seGenerateTerrain(void)
{
	// Explanation: This function will generate a cubic Bezier patch
	//  That means we'll need a control structure of [4][4]. Other
	//  variables to consider will be LoD and normal generation.

	// Control point data structure
	struct Points {
		double x,y,z;
	};
	Points control[4][4];

	// Cycle through control points and randomize them
	srand((unsigned)time(NULL));
	for (int l=0;l<4;l++) {
		for (int m=0;m<4;m++) {
			control[l][m].x=133*m;
			control[l][m].y=rand()%100;
			if (rand()%3==1)
				control[l][m].y*=-1;
			control[l][m].z=133*l;
		}
	}

	// Generate the Bezier patch
	// B1(t) = t * t * t
    // B2(t) = 3 * t * t * (1 - t)
    // B3(t) = 3 * t * (1 - t) * (1 - t)
    // B4(t) = (1 - t) * (1 - t) * (1 - t)

	detailBias=.01;
	Points tempCurve[4];
	double newx,newy,newz;

	for (double i=0;i<=1;i+=detailBias) {
		for (int j=0;j<4;j++) {
			tempCurve[j].x= control[j][0].x*(i*i*i)+
							control[j][1].x*(3*i*i*(1-i))+
							control[j][2].x*(3*i*(1-i)*(1-i))+
							control[j][3].x*((1-i)*(1-i)*(1-i));
			tempCurve[j].y= control[j][0].y*(i*i*i)+
							control[j][1].y*(3*i*i*(1-i))+
							control[j][2].y*(3*i*(1-i)*(1-i))+
							control[j][3].y*((1-i)*(1-i)*(1-i));
			tempCurve[j].z= control[j][0].z*(i*i*i)+
							control[j][1].z*(3*i*i*(1-i))+
							control[j][2].z*(3*i*(1-i)*(1-i))+
							control[j][3].z*((1-i)*(1-i)*(1-i));
			//printf("%f ",tempCurve[j].x);
		}
		for (double k=0;k<=1;k+=detailBias) {
			newx= tempCurve[0].x*(k*k*k)+
				  tempCurve[1].x*(3*k*k*(1-k))+
				  tempCurve[2].x*(3*k*(1-k)*(1-k))+
				  tempCurve[3].x*((1-k)*(1-k)*(1-k));
			newy= tempCurve[0].y*(k*k*k)+
				  tempCurve[1].y*(3*k*k*(1-k))+
				  tempCurve[2].y*(3*k*(1-k)*(1-k))+
				  tempCurve[3].y*((1-k)*(1-k)*(1-k));
			newz= tempCurve[0].z*(k*k*k)+
				  tempCurve[1].z*(3*k*k*(1-k))+
				  tempCurve[2].z*(3*k*(1-k)*(1-k))+
				  tempCurve[3].z*((1-k)*(1-k)*(1-k));

			
			plot[int(newx)][int(newz)]=int(newy);
			plot[int(newx)-1][int(newz)]=int(newy);
			plot[int(newx)+1][int(newz)]=int(newy);
			plot[int(newx)][int(newz)-1]=int(newy);
			plot[int(newx)][int(newz)+1]=int(newy);
			plot[int(newx)-1][int(newz)+1]=int(newy);
			plot[int(newx)+1][int(newz)-1]=int(newy);
			plot[int(newx)-1][int(newz)-1]=int(newy);
			plot[int(newx)+1][int(newz)+1]=int(newy);
			//printf("%f: %d\n",k,int(newx));
		}
		//printf("\n");
	}
}

/*
// OBSOLETE
void se_Generate_Terrain(void)
{
	int i,j,r,num,k,height,extent=1,l=0,e;

	srand((unsigned)time(NULL));
	//printf("%d",rand()%10);
	for (k=1;k<=C_POINTS;k++) {
		do {
			m=i=rand()%400;
			n=j=rand()%400;
			num=rand()%100;
			printf("%d %d %d\n",i,j,num);
		} while ((i-num)<0 || (i+num)>399 || (j-num)<0 || (j+num)>399);
		points[k-1][0]=i;
		points[k-1][1]=j;
		plot[i][j]=num;
	}
	for (k=1;k<=C_POINTS;k++) {
		height=plot[points[k-1][0]][points[k-1][1]];
		l=0;
		extent=1;
		while (height!=0) {
			while (l<=extent) {
				plot[points[k-1][0]+extent][points[k-1][1]+l]=height;
				l++;
			}
			l=-1;
			while (l>=-extent) {
				plot[points[k-1][0]+extent][points[k-1][1]+l]=height;
				l--;
			}
			l=extent;
			e=extent;
			while (e>=-extent) {
				plot[points[k-1][0]+e][points[k-1][1]+l]=height;
				e--;
			}
			l=0;
			while (l<=extent) {
				plot[points[k-1][0]-extent][points[k-1][1]+l]=height;
				l++;
			}
			l=-1;
			while (l>=-extent) {
				plot[points[k-1][0]-extent][points[k-1][1]+l]=height;
				l--;
			}
			l=-extent;
			e=extent;
			while (e>=-extent) {
				plot[points[k-1][0]+e][points[k-1][1]+l]=height;
				e--;
			}
			if (height>0)
				height--;
			if (height<0)
				height++;
			extent++;
			if ((points[k-1][0]+extent>399) ||
				(points[k-1][0]-extent<0)   ||
				(points[k-1][1]+extent>399) ||
				(points[k-1][1]-extent<0))
				break;
		}
	}
}
*/

void se_disp_terrain(void)
{
	double cx,cy,cz;
	double bias=(1/detailBias);
	int inc=(400/bias);

	glColor3f(0,1,0);
	//GLfloat color[]={.3,.2,.1,1};
	//glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);
	for (int i=inc-1;i<=(399-inc);i+=inc) {
		for (int j=inc-1;j<=(399-inc);j+=inc) {
			
			/*cross(-200+i+inc-(-200+i),
				  plot[i+inc][j]-(plot[i][j]),
				  0,
				  0,
				  plot[i][j+inc]-(plot[i][j]),
				  -200+j+inc-(-200+j),
				  &cx,&cy,&cz);*/


			/*cx/=sqrt((cx*cx)+(cy*cy)+(cz*cz));
			cy/=sqrt((cx*cx)+(cy*cy)+(cz*cz));
			cz/=sqrt((cx*cx)+(cy*cy)+(cz*cz));
			glNormal3f(-cx,-cy,-cz);*/

			/*GLfloat color2[]={0,0,.5,1};
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color2);
			glBegin(GL_LINES);
			 glVertex3f(-200+i,plot[i][j],-200+j);
			 glVertex3f(-cx,-cy,-cz);
			glEnd();

			printf("%f %f %f\n",-cx,-cy,-cz);

			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,color);*/

			//glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			 glTexCoord2f(0,0);
			 cross(-200+i+inc-(-200+i),
				   plot[i+inc][j]-(plot[i][j]),
				   0,
				   0,
				   plot[i][j+inc]-(plot[i][j]),
				   -200+j+inc-(-200+j),
				   &cx,&cy,&cz);
			 glNormal3f(-cx,-cy,-cz);
			 glVertex3f(-200+i,plot[i][j],-200+j);
			 glTexCoord2f(0,1);
			 cross(-200+i-(-200+i+inc),
				   plot[i][j]-(plot[i+inc][j]),
				   0,
				   0,
				   plot[i+inc][j+inc]-(plot[i+inc][j]),
				   -200+j+inc-(-200+j),
				   &cx,&cy,&cz);
			 glNormal3f(cx,cy,cz);
			 if (i==0)
				i--;
			 glVertex3f(-200+i+inc,plot[i+inc][j],-200+j);
			 //if (i==391)
				//printf("%d ",plot[399][j]);
			 if (i==-1)
				i++;
			 glTexCoord2f(1,1);
			 if (j==0)
				j--;
			 if (i==0)
				 i--;
			 glVertex3f(-200+i+inc,plot[i+inc][j+inc],-200+j+inc);
			 if (j==-1)
				j++;
			 if (i==-1)
				 i++;
			 if (j==0)
				 j--;
			 glTexCoord2f(1,0);
			 glVertex3f(-200+i,plot[i][j+inc],-200+j+inc);
			 if (j==-1)
				 j++;
			glEnd();
			/*//glEnable(GL_LIGHTING);

			cross(0,
				  plot[i+inc][j]-(plot[i+inc][j+inc]),
				  -200+j-(-200+j+inc),
				  -200+i+inc-(-200+i),
				  plot[i+inc][j+inc]-(plot[i][j+inc]),
				  0,
				  &cx,&cy,&cz);

			cx/=sqrt((cx*cx)+(cy*cy)+(cz*cz));
			cy/=sqrt((cx*cx)+(cy*cy)+(cz*cz));
			cz/=sqrt((cx*cx)+(cy*cy)+(cz*cz));
			glNormal3f(-cx,-cy,-cz);

			//glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			 glTexCoord2f(0,0);
			 if (j==0)
				j--;
			 glVertex3f(-200+i,plot[i][j+inc],-200+j+inc);
			 if (j==-1)
				j++;
			 glTexCoord2f(0,1);
			 if (j==0)
				j--;
			 if (i==0)
				i--;
			 glVertex3f(-200+i+inc,plot[i+inc][j+inc],-200+j+inc);
			 if (j==-1)
				j++;
			 if (i==-1)
				i++;
			 glTexCoord2f(1,0);
			 if (i==0)
				i--;
			 glVertex3f(-200+i+inc,plot[i+inc][j],-200+j);
			 if (i==-1)
				i++;
			glEnd();
			if (j==0)
				j--;
			glEnable(GL_LIGHTING);*/
		}
		if (i==0)
			i--;
		
	}
	//printf("\n");

	/*glColor3f(1,0,0);
	for (int m=0;m<400;m++) {
		for (int n=0;n<400;n++) {
			glBegin(GL_LINES);
			 glVertex3f(-200+m,0,-200+n);
			 glVertex3f(-200+m,plot[m][n],-200+n);
			glEnd();
			//if ((m==399 || n==399) && plot[m][n]!=0)
				//printf("%d ",plot[m][n]);
		}
		//if ((m==399 || n==399) && plot[m][n]!=0)
			//printf("\n");
	}*/



		/*glBegin(GL_POLYGON);
		 glTexCoord2f(0,0);
		 glNormal3f(1,1,0);
		 glVertex3f(-200+points[k-1][1],plot[points[k-1][0]][points[k-1][1]],-200+points[k-1][0]);
		 glTexCoord2f(5,0);
		 glVertex3f(-200+points[k-1][1]+plot[points[k-1][0]][points[k-1][1]],
					0,
					-200+points[k-1][0]+plot[points[k-1][0]][points[k-1][1]]);
		 glTexCoord2f(0,5);
		 glVertex3f(-200+points[k-1][1]+plot[points[k-1][0]][points[k-1][1]],
					0,
					-200+points[k-1][0]-plot[points[k-1][0]][points[k-1][1]]);
		glEnd();

		glBegin(GL_POLYGON);
		 glTexCoord2f(0,0);
		 glNormal3f(-1,1,0);
		 glVertex3f(-200+points[k-1][1],plot[points[k-1][0]][points[k-1][1]],-200+points[k-1][0]);
		 glTexCoord2f(5,0);
		 glVertex3f(-200+points[k-1][1]-plot[points[k-1][0]][points[k-1][1]],
					0,
					-200+points[k-1][0]+plot[points[k-1][0]][points[k-1][1]]);
		 glTexCoord2f(0,5);
		 glVertex3f(-200+points[k-1][1]-plot[points[k-1][0]][points[k-1][1]],
					0,
					-200+points[k-1][0]-plot[points[k-1][0]][points[k-1][1]]);
		glEnd();

		glBegin(GL_POLYGON);
		 glNormal3f(0,0,0);
		 glTexCoord2f(0,0);
		 glNormal3f(0,1,1);
		 glVertex3f(-200+points[k-1][1],plot[points[k-1][0]][points[k-1][1]],-200+points[k-1][0]);
		 glTexCoord2f(5,0);
		 glVertex3f(-200+points[k-1][1]+plot[points[k-1][0]][points[k-1][1]],
					0,
					-200+points[k-1][0]+plot[points[k-1][0]][points[k-1][1]]);
		 glTexCoord2f(0,5);
		 glVertex3f(-200+points[k-1][1]-plot[points[k-1][0]][points[k-1][1]],
					0,
					-200+points[k-1][0]+plot[points[k-1][0]][points[k-1][1]]);
		glEnd();

		glBegin(GL_POLYGON);
		 glNormal3f(0,1,-1);
		 glTexCoord2f(0,0);
		 glVertex3f(-200+points[k-1][1],plot[points[k-1][0]][points[k-1][1]],-200+points[k-1][0]);
		 glTexCoord2f(5,0);
		 glVertex3f(-200+points[k-1][1]+plot[points[k-1][0]][points[k-1][1]],
					0,
					-200+points[k-1][0]-plot[points[k-1][0]][points[k-1][1]]);
		 glTexCoord2f(0,5);
		 glVertex3f(-200+points[k-1][1]-plot[points[k-1][0]][points[k-1][1]],
					0,
					-200+points[k-1][0]-plot[points[k-1][0]][points[k-1][1]]);
		glEnd();*/
	
}   


