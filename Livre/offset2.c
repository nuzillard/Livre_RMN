#include "libgfp.h"
#include <math.h>

#define RES 100

double x0 = 7.0/25.0 ;
double z0 = 24.0/25.0 ;

void trajec(double angle, double *x, double *y, double *z)
{
	double ca = cos(angle) ;
	
	*x = x0 * z0 * (1 - ca) ;
	*y = -x0 * sin(angle) ;
	*z = 1 - x0 * x0 * (1 - ca) ;
}

void flechexz(double x, double z)
{
	double norme, xn, zn, th, ct, st ;

	norme = hypot(x, z) ;

	xn = -x/norme * 0.05 ;
	zn = -z/norme * 0.05 ;

	th = ARROWANGLE ;
	ct = cos(th) ;
	st = sin(th) ;

	segment(0.0, 0.0, 0.0, x, 0.0, z) ;
	segment(x, 0.0, z, x+(xn*ct-zn*st), 0.0, z+(xn*st+zn*ct)) ;
	segment(x, 0.0, z, x+(xn*ct+zn*st), 0.0, z+(-xn*st+zn*ct)) ;
}

int main()
{
	int i ;
	double x, y, z ;
	double inc = 2 * M_PI / RES ;
	double eps = 0.02 ;
	
	setview(70.0, -70.0) ;
	setmingrey(0.3) ;
	setxlabel("X", 1.1, 0.0, 0.0) ;
	gfp_init() ;
	
	setlinewidth(LW3) ;
	curve(trajec, 0, 2*M_PI, RES) ;
		
	segment(x0*z0*(1-eps), 0.0, z0*z0 + eps*(x0*x0), 
		x0*z0*(1+eps), 0.0, z0*z0 - eps*(x0*x0)) ;
	
	flechexz(x0/2, z0/2) ;
	flechexz(x0/2, 0.0) ;
	flechexz(0.0, z0/2) ;

	centerarrow(M_PI/180 * (70), trajec, 0.05, ARROWANGLE) ;
	trajarrow(M_PI/180 * (110), M_PI/180 * (15), 0.0, trajec, 0.08, ARROWANGLE) ;

	setlinewidth(LW1) ;
	setfont("bigfont") ;
	trajec(M_PI/180 * (70), &x, &y, &z) ;
	text3vec("M", x+0.02, y, z+0.02, 18.0, 16.0, 0.02, ARROWANGLE) ;

	setfont("bigsymbolfont") ;
	text3vec("W", x0/2*1.1, 0.0, z0/2*1.05, 18.0, 16.0, 0.02, ARROWANGLE) ;
	text3vec("W", -0.1, 0.0, z0/2*1.05, 18.0, 16.0, 0.02, ARROWANGLE) ;
	text3vec("W", x0/2*1.1, 0.0, 0.05, 18.0, 16.0, 0.02, ARROWANGLE) ;

	setfont("smallfont\n") ;
	text3("eff", x0/2*1.1+0.06, 0.0, z0/2*1.05-0.02) ;
	text3("0", -0.1+0.065, 0.0, z0/2*1.05-0.02) ;
	text3("1", x0/2*1.1+0.065, 0.0, 0.05-0.02) ;

	return 0 ;
}

