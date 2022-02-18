/* gcc invcomp.c -o invcomp -L. -lgfp -lsimu1 -lm */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "libgfp.h"
#include "libsimu1.h"

#define THETA 60.0
#define PHI -70.0
#define MINGREY 0.3

#define ANGLE 85

Vec3 v0, v1, v2 ;
Vec3 ax, ay ;

double deg = M_PI / 180 ;
int n1 = ANGLE ;
int n2 = 2 * ANGLE ;

void pr_usage(char *c)
{
	fprintf(stderr, "usage: %s 0|1\n", c) ;
	exit(0) ;
}

void initVec3(Vec3 v, double x, double y, double z)
{
	v[0] = x ;
	v[1] = y ;
	v[2] = z ;
}

void traj0(double t, double *x, double *y, double *z)
{
	Mat33 r ;
	Vec3 v ;
	
	matrot(r, ax, t) ;
	matmult(r, v0, v) ;
	*x =v[0] ; *y = v[1] ; *z = v[2] ;
}

void traj1(double t, double *x, double *y, double *z)
{
	Mat33 r ;
	Vec3 v ;
	
	matrot(r, ay, t) ;
	matmult(r, v1, v) ;
	*x =v[0] ; *y = v[1] ; *z = v[2] ;
}

void traj2(double t, double *x, double *y, double *z)
{
	Mat33 r ;
	Vec3 v ;
	
	matrot(r, ax, t) ;
	matmult(r, v2, v) ;
	*x =v[0] ; *y = v[1] ; *z = v[2] ;
}

void mycurve(trajfunc f, int n)
{
	curve(f, 0.0, n*deg, n) ;
}

void draw0()
{
	mycurve(traj0, n2) ;
	trajarrow(n2/2.0*deg, 0.01, 0.01, traj0, 0.08, ARROWANGLE) ;

	setlinewidth(3.0) ;
	centerarrow(0.0, traj0, 0.05, ARROWANGLE) ;
	centerarrow(n2*deg, traj0, 0.05, ARROWANGLE) ;
}

void draw1()
{
	Mat33 r ;
	
	matrot(r, ax, n1*deg) ;
	matmult(r, v0, v1) ;
	matrot(r, ay, n2*deg) ;
	matmult(r, v1, v2) ;
	
	mycurve(traj0, n1) ;
	trajarrow(n1/2.0*deg, 0.01, 0.01, traj0, 0.08, ARROWANGLE) ;
	
	mycurve(traj1, n2) ;
/*	trajarrow(n2/2.0*deg, 0.01, 0.01, traj1, 0.08, ARROWANGLE) ; */
	
	mycurve(traj2, n1) ;
	trajarrow(n1/3.0*deg, 0.01, 0.01, traj2, 0.08, ARROWANGLE) ;
	
	setlinewidth(3.0) ;
	centerarrow(0.0, traj0, 0.05, ARROWANGLE) ;
	centerarrow(n1*deg, traj2, 0.05, ARROWANGLE) ;
}

int main(int argc, char **argv)
{
	int cas = 0 ;
	int i ;
	
	if(argc != 2) {
		pr_usage(argv[0]) ;
	}
	cas = atoi(argv[1]) ;
	if((cas != 0) && (cas != 1)){
		pr_usage(argv[0]) ;
	}
	
	initVec3(ax, 1.0, 0.0, 0.0) ;
	initVec3(ay, 0.0, 1.0, 0.0) ;	
	initVec3(v0, 0.0, 0.0, 1.0) ;
	
	setmingrey(MINGREY) ;
	setview(THETA, PHI) ;
	setxlabel("X", 1.1, 0.0, 0.0) ;
	setzlabel("Z", 0.0, -0.05, 1.1) ;
	gfp_init() ;
	setlinewidth(LW3) ;
	
	if(cas == 0) {
		draw0() ;
	} else {
		draw1() ;
	}
	return 0 ;
}
