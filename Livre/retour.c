#include "libgfp.h"
#include <math.h>

#define OM 20.0 * 2 * M_PI
#define RT1 0.3
#define RT2 0.15
#define DT 0.002

void trajec(double t, double *x, double *y, double *z)
{
	double om = OM ;
	double rt1 = RT1 ;
	double rt2 = RT2 ;
	double xy ;
	
	xy = exp(-t / rt2) ;
	*x = xy * cos(om * t) ;
	*y = xy * sin(om * t) ;
	*z = 1 - exp(-t / rt1) ;
}


int main()
{
	int i ;
	double x, y, z ;
	gfp_init() ;
	
	setlinewidth(LW3) ;
	curve(trajec, 0*DT, 512*DT, 512) ;
	centerarrow(3*DT, trajec, 0.05, ARROWANGLE) ;
	trajarrow(4*DT, 0.5*DT, 0.0*DT, trajec, 0.08, ARROWANGLE) ;

	setfont("bigfont") ;
	setlinewidth(LW1) ;
	trajec(3*DT, &x, &y, &z) ;
	text3vec("M", x, y, z+0.05, 16.0, 16.0, 0.02, ARROWANGLE) ;

	return 0 ;
}

