// Scorched Earth 3D
// File: SE3D_Text.cpp
// Description: Text functions

void dispstring(char string[50],double xr,double yr)
{
	int i;

	for (i=0;string[i]!='\0';i++,xr+=8) {
		glRasterPos2f(xr,yr);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,string[i]);
	}
}

void dispstring(int angle,double xr,double yr)
{
	char num = '0', num2 = '0', num3 = '0';
	if (angle>=100 || angle<=-100) {
		switch (angle/100) {
		case 0:
			num='0';
			break;
		case 1:
			num='1';
			break;
		case 2:
			num='2';
			break;
		case 3:
			num='3';
			break;
		case 4:
			num='4';
			break;
		case 5:
			num='5';
			break;
		case 6:
			num='6';
			break;
		case 7:
			num='7';
			break;
		case 8:
			num='8';
			break;
		case 9:
			num='9';
			break;
		};
		switch ((angle/10)%10) {
		case 0:
			num2='0';
			break;
		case 1:
			num2='1';
			break;
		case 2:
			num2='2';
			break;
		case 3:
			num2='3';
			break;
		case 4:
			num2='4';
			break;
		case 5:
			num2='5';
			break;
		case 6:
			num2='6';
			break;
		case 7:
			num2='7';
			break;
		case 8:
			num2='8';
			break;
		case 9:
			num2='9';
			break;
		};
	}
	if (angle<100 && angle>=10) {
		switch (angle/10) {
		case 0:
			num='0';
			break;
		case 1:
			num='1';
			break;
		case 2:
			num='2';
			break;
		case 3:
			num='3';
			break;
		case 4:
			num='4';
			break;
		case 5:
			num='5';
			break;
		case 6:
			num='6';
			break;
		case 7:
			num='7';
			break;
		case 8:
			num='8';
			break;
		case 9:
			num='9';
			break;
		};
		switch (angle%10) {
		case 0:
			num2='0';
			break;
		case 1:
			num2='1';
			break;
		case 2:
			num2='2';
			break;
		case 3:
			num2='3';
			break;
		case 4:
			num2='4';
			break;
		case 5:
			num2='5';
			break;
		case 6:
			num2='6';
			break;
		case 7:
			num2='7';
			break;
		case 8:
			num2='8';
			break;
		case 9:
			num2='9';
			break;
	};	
	}
	if (angle<10) {
		switch (angle) {
		case 0:
			num='0';
			break;
		case 1:
			num='1';
			break;
		case 2:
			num='2';
			break;
		case 3:
			num='3';
			break;
		case 4:
			num='4';
			break;
		case 5:
			num='5';
			break;
		case 6:
			num='6';
			break;
		case 7:
			num='7';
			break;
		case 8:
			num='8';
			break;
		case 9:
			num='9';
			break;
		};
	}
	switch ((angle%100)%10) {
	case 0:
		num3='0';
		break;
	case 1:
		num3='1';
		break;
	case 2:
		num3='2';
		break;
	case 3:
		num3='3';
		break;
	case 4:
		num3='4';
		break;
	case 5:
		num3='5';
		break;
	case 6:
		num3='6';
		break;
	case 7:
		num3='7';
		break;
	case 8:
		num3='8';
		break;
	case 9:
		num3='9';
		break;
	};

	if (angle<10 && angle>-10) {
		glRasterPos2f(xr,yr);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,num);
	}
	if (angle<100 && angle>-100) {
		glRasterPos2f(xr,yr);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,num);
		glRasterPos2f(xr+7,yr);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,num2);
	}
	if (angle>=100 || angle<=-100) {
		glRasterPos2f(xr,yr);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,num);
		glRasterPos2f(xr+7,yr);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,num2);
		glRasterPos2f(xr+14,yr);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,num3);
	}
}

void se_interface()
{
	if (win==1) {
		dispstring("Player One Wins!!!",350,450);
		win=0;
	}
	if (win==2) {
		dispstring("Player Two Wins!!!",350,450);
		win=0;
	}

	if (turn==1)
		dispstring("Player One's Turn",650,550);
	if (turn==2)
		dispstring("Player Two's Turn",650,550);

	glColor3f(0,1,0);
	dispstring("< and > rotate the board",2,4);
	dispstring("[ and ] rotate your tank",2,18);
	dispstring("z fires",2,33);
	dispstring("q and a adjust angle of tank muzzle",2,48);
	dispstring("w and s adjust speed of projectile",2,63);
	dispstring("p switches between tank and landscape mode",2,78);

	glColor3f(1,0,0);
	dispstring("Muzzle angle:",630,4);
	if (turn==1)
		dispstring(t1a,775,3);
	if (turn==2)
		dispstring(t2a,775,3);
	dispstring("Projectile speed:",630,19);
	if (turn==1)
		dispstring(s1,775,18);
	if (turn==2)
		dispstring(s2,775,18);

	if (turn==1) {
		if (p1mode==1)
			dispstring("Landscape Mode",10,500);
		if (p1mode==2)
			dispstring("Tank Mode",10,500);
	}
	if (turn==2) {
		if (p2mode==1)
			dispstring("Landscape Mode",10,500);
		if (p2mode==2)
			dispstring("Tank Mode",10,500);
	}
}