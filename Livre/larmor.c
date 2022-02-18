#include "libgfp.h"
#include <math.h>

#define RES 100
#define TH 55*M_PI/180
#define ARCPHI (-10)*M_PI/180

void trajec(double t, double *x, double *y, double *z)
{
	double xy ;
	
	xy = sin(TH) ;
	*x = xy * cos(t) ;
	*y = xy * sin(t) ;
	*z = cos(TH) ;
}

void arc(double t, double *x, double *y, double *z)
{
	double xy, r ;
	
	r = 0.15 ;
	xy = r * sin(t) ;
	*x = xy * cos(ARCPHI) ;
	*y = xy * sin(ARCPHI) ;
	*z = r * cos(t) ;
}

int main()
{
	int i ;
	double x, y, z ;
	
	setmingrey(0.3) ;
	gfp_init() ;
	
	setlinewidth(LW3) ;
	curve(trajec, 0.0, 2*M_PI, RES) ;
	
	curve(arc, 0.0, TH, 10) ;
	setfont("bigsymbolfont") ;
	text3("q", 0.0, -0.1, 0.1) ;
	
	centerarrow(ARCPHI, trajec, 0.05, ARROWANGLE) ;
	trajarrow((40)*M_PI/180, 0.01, 0.01, trajec, 0.08, ARROWANGLE) ;

	setfont("bigfont") ;
	setlinewidth(LW1) ;
	trajec(ARCPHI, &x, &y, &z) ;
	text3vec("M", x, y, z+0.05, 16.0, 16.0, 0.02, ARROWANGLE) ;

	return 0 ;
}

