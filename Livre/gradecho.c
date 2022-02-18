#include "libgfp.h"
#include <math.h>
#include <stdio.h>

#define RES 40
#define RANGLE 0.8
#define AANGLE (M_PI/24)

double kglob ;

void circle0(double t, double *x, double *y, double *z)
{
	*x = cos(t) ;
	*y = sin(t) ;
	*z = 0.0 ;
}

void circle(double z, double ph)
{
	double cph, sph, pha ;
	
	setlinewidth(LW2) ;
	curve(circle0, 0.0, 2*M_PI, RES) ;
	cph = cos(ph) ;
	sph = sin(ph) ;
	setlinewidth(LW3) ;
	segment(0.0, 0.0, 0.0, cph, sph, 0.0) ;
	pha = ph + AANGLE ;
	segment(cph, sph, 0.0, RANGLE*cos(pha), RANGLE*sin(pha), 0.0) ;
	pha = ph - AANGLE ;
	segment(cph, sph, 0.0, RANGLE*cos(pha), RANGLE*sin(pha), 0.0) ;
}

void helix(double t, double *x, double *y, double *z)
{
	double phi ;
	
	*z = t ;
	phi = kglob * t ;
	*x = cos(phi) ;
	*y = sin(phi) ;
}

void tube(double t, double *x, double *y, double *z)
{
	*x = 1.25 * cos(t) ;
	*y = 0.0 ;
	*z = -3.25 + 1.25 * sin(t) ;
}

void circles(double k, double xp, char *c)
{
	int i ;
	double z ;
	double phi ;
	
	kglob = k ;
	for(i=-6 ; i<=6 ; i++) {
		z = i * 0.5 ;
		phi = k * z ;
		setgeom(1.0, xp, 20.0+z, INFTY) ;
		circle(z, phi) ;
	}
	setlinewidth(LW2) ;
	setgeom(1.0, xp, 20.0, INFTY) ;
	printf("[2 2] 0 setdash\n") ;
	curve_bw(helix, -3.2, 3.2, RES) ;
	printf("[] 0 setdash\n") ; 
	setlinewidth(3.0) ;
	segment_bw(-1.25, 0, -3.25, -1.25, 0, 4.0) ;
	segment_bw(1.25, 0, -3.25, 1.25, 0, 4.0) ;
	curve_bw(tube, 0.0, -M_PI, RES) ;
	setfont("titlefont") ;
	text3_bw(c, -1.75, 0.0, 3.5) ;
}

void addfont(char *name, char *font, double size)
{
	printf("/%s /%s findfont %.1f scalefont def\n", name, font, size) ;
}

void arrow()
{
	setlinewidth(LW3) ;
	segment_bw(-0.5, 0.0, 0.0, 0.5, 0.0, 0.0) ;
	arrowhead3_bw(0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.4, ARROWANGLE) ;
}

void gradtext(char *g, double x)
{
	setgeom(1.0, x, 20.0, INFTY) ;
	arrow() ;
	setfont("mathfontbig") ;
	text3_bw("G", -0.2, 0.0, 0.3) ;
	setfont("smallfont") ;
	text3_bw(g, 0.2, 0.0, 0.3-0.15) ;
}

void invtext(double x)
{
	setgeom(1.0, x, 20.0, INFTY) ;
	arrow() ;
	setfont("bigsymbolfont") ;
	text3_bw("p", -0.2, 0.0, 0.3) ;
	setfont("mathfontsmall") ;
	text3_bw("x", 0.2, 0.0, 0.3-0.15) ;
}

int main()
{
	int i ;
	double x, y, z ;
	
	setview(70.0, -90.0) ;
	setmingrey(0.3) ;
	setsegment(4.0) ;
	header() ;
	addfont("titlefont", "Times-Italic", CORPS3) ;
	addfont("mathfontbig", "Times-Bold-Italic", CORPS3) ;
	addfont("mathfontsmall", "Times-Bold-Italic", CORPS1) ;
	
	circles(0.0, 4.0, "a") ;
	gradtext("1", 6.0) ;
	circles(2*M_PI/3, 8.0, "b") ;
	invtext(10.0) ;
	circles(-2*M_PI/3, 12.0, "c") ;
	gradtext("2", 14.0) ;
	circles(0.0, 16.0, "d") ;
	
	return 0 ;
}
