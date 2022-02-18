/* gcc cpmgcalib.c -o cpmgcalib -L. -lgfp -lsimu1 -lm */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "libgfp.h"
#include "libsimu1.h"

#define THETA 60.0
#define PHI 20.0

#define MINGREY 0.3

Vec3 v0, v1, v2, v3, v4, v5, v6 ;
Vec3 a1, a2 ;
Mat33 r1, r2 ;

double deg = M_PI / 180 ;
int prec = 44 ;
int refoc = 160 ;

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
	
	matrot(r, a1, t) ;
	matmult(r, v0, v) ;
	*x =v[0] ; *y = v[1] ; *z = v[2] ;
}

void traj1(double t, double *x, double *y, double *z)
{
	Mat33 r ;
	Vec3 v ;
	
	matrot(r, a2, t) ;
	matmult(r, v1, v) ;
	*x =v[0] ; *y = v[1] ; *z = v[2] ;
}

void traj2(double t, double *x, double *y, double *z)
{
	Mat33 r ;
	Vec3 v ;
	
	matrot(r, a1, t) ;
	matmult(r, v2, v) ;
	*x =v[0] ; *y = v[1] ; *z = v[2] ;
}

void traj3(double t, double *x, double *y, double *z)
{
	Mat33 r ;
	Vec3 v ;
	
	matrot(r, a1, t) ;
	matmult(r, v3, v) ;
	*x =v[0] ; *y = v[1] ; *z = v[2] ;
}

void traj4(double t, double *x, double *y, double *z)
{
	Mat33 r ;
	Vec3 v ;
	
	matrot(r, a2, t) ;
	matmult(r, v4, v) ;
	*x =v[0] ; *y = v[1] ; *z = v[2] ;
}

void traj5(double t, double *x, double *y, double *z)
{
	Mat33 r ;
	Vec3 v ;
	
	matrot(r, a1, t) ;
	matmult(r, v5, v) ;
	*x =v[0] ; *y = v[1] ; *z = v[2] ;
}

void text3v(char *c, Vec3 v, double dx, double dy, double dz)
{
	text3(c, v[0] + dx, v[1] + dy, v[2] + dz) ;
}

void mycurve(trajfunc f, int n)
{
	curve(f, 0.0, n*deg, n) ;
}

void draw0()
{
	text3v("A", v0, 0.0, 0.05, 0.03) ;
	mycurve(traj0, prec) ;
	trajarrow(prec/2.0*deg, 0.01, 0.01, traj0, 0.08, ARROWANGLE) ;
	
	text3v("B", v1, 0.0, 0.03, 0.03) ;
	mycurve(traj1, refoc) ;
	trajarrow(refoc/2.0*deg, 0.01, 0.01, traj1, 0.08, ARROWANGLE) ;
	
	text3v("C", v2, 0.0, 0.05, 0.03) ;
	mycurve(traj2, prec) ;
	trajarrow(prec/2.0*deg, 0.01, 0.01, traj2, 0.08, ARROWANGLE) ;
	
	segment(v3[0], v3[1], v3[2]+0.02, v3[0], v3[1], v3[2]-0.02) ;
	
	text3v("D", v3, 0.0, 0.0, 0.03) ;
	mycurve(traj3, prec) ;
	trajarrow(prec/2.0*deg, 0.01, 0.01, traj3, 0.08, ARROWANGLE) ;
	
	text3v("E", v4, 0.0, 0.03, 0.03) ;
	mycurve(traj4, refoc) ;
	trajarrow(refoc/2.0*deg, 0.01, 0.01, traj4, 0.08, ARROWANGLE) ;
	
	text3v("F", v5, 0.0, 0.05, 0.03) ;
	mycurve(traj5, prec) ;
	trajarrow(prec/2.0*deg, 0.01, 0.01, traj5, 0.08, ARROWANGLE) ;
	
	text3v("G", v6, 0.0, -0.05, 0.03) ;

	setlinewidth(3.0) ;
	centerarrow(0.0, traj0, 0.05, ARROWANGLE) ;
	centerarrow(prec*deg, traj5, 0.05, ARROWANGLE) ;
}

void draw1()
{
	text3v("A", v0, 0.0, 0.05, 0.03) ;
	mycurve(traj0, prec) ;
	trajarrow(prec/2.0*deg, 0.01, 0.01, traj0, 0.08, ARROWANGLE) ;
	
	text3v("B", v1, 0.0, 0.03, 0.03) ;
	mycurve(traj1, refoc) ;
	trajarrow(2*refoc/3.0*deg, 0.01, 0.01, traj1, 0.08, ARROWANGLE) ;
	
	text3v("C", v2, 0.0, 0.05, 0.03) ;
	mycurve(traj2, prec) ;
	trajarrow(prec/2.0*deg, 0.01, 0.01, traj2, 0.08, ARROWANGLE) ;
	
	segment(v3[0], v3[1], v3[2]+0.02, v3[0], v3[1], v3[2]-0.02) ;

	text3v("D", v3, 0.0, 0.0, 0.03) ;
	mycurve(traj3, prec) ;
	trajarrow(prec/2.0*deg, 0.01, 0.01, traj3, 0.08, ARROWANGLE) ;
	
	text3v("E", v4, 0.0, 0.03, 0.03) ;
	mycurve(traj4, refoc) ;
	trajarrow(3*refoc/4.0*deg, 0.01, 0.01, traj4, 0.08, ARROWANGLE) ;
	
	text3v("F", v5, 0.0, 0.05, 0.03) ;
	mycurve(traj5, prec) ;
	trajarrow(prec/2.0*deg, 0.01, 0.01, traj5, 0.08, ARROWANGLE) ;
	
	text3v("G", v6, 0.0, -0.05, 0.03) ;
	
	setlinewidth(3.0) ;
	centerarrow(0.0, traj0, 0.05, ARROWANGLE) ;
	centerarrow(prec*deg, traj5, 0.05, ARROWANGLE) ;
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
	
	initVec3(a1, 0.0, 0.0, 1.0) ;
	if(cas == 0) {
		initVec3(a2, 1.0, 0.0, 0.0) ;
	} else {
		initVec3(a2, 0.0, 1.0, 0.0) ;
	}
	initVec3(v0, 1.0, 0.0, 0.0) ;
	matrot(r1, a1, prec*deg) ;
	matrot(r2, a2, refoc*deg) ;
	matmult(r1, v0, v1) ;
	matmult(r2, v1, v2) ;
	matmult(r1, v2, v3) ;
	matmult(r1, v3, v4) ;
	matmult(r2, v4, v5) ;
	matmult(r1, v5, v6) ;
	matrot(r1, a1, deg) ;
	matrot(r2, a2, deg) ;
	
	setmingrey(MINGREY) ;
	setview(THETA, PHI) ;
	setzlabel("Z", 0.0, -0.05, 1.05) ;
	gfp_init() ;
	setlinewidth(LW3) ;
	
	if(cas == 0) {
		draw0() ;
	} else {
		draw1() ;
	}
	return 0 ;
}
