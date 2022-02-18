#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define UP 0
#define DOWN 1
#define CM (72.0/2.54)
#define DEG (M_PI/180.0)
#define INFTY (1000000.0)
#define SEGMENT 10.0
#define RES 100
#define R 8
#define X0 10.5
#define Y0 14
#define CORPS1 12
#define CORPS2 14
#define CORPS3 18
#define DEFAULT_THETA 70
#define DEFAULT_PHI 20
#define LW1 0.25
#define LW2 1.0
#define F INFTY
#define MINGREY 0.1
#define MAXGREY 1.0
#define WHITE 0.01

typedef void (*trajfunc)(double t, double *x, double *y, double *z) ;

void setgeom(double radius, double x, double y, double distance) ;
void setfontsizes(int small, int medium, int big) ;
void setgfplinewidth(double thin, double thick) ;
void setmingrey(double ming) ;
static void compview() ;
void setview(double th, double ph) ;
void setxlabel(char *c, double x, double y, double z) ;
void setylabel(char *c, double x, double y, double z) ;
void setzlabel(char *c, double x, double y, double z) ;
void setaxisfont(char *c) ;
void setsegment(double segment) ;
void coor2(double x, double y, double *xp, double *yp) ;
void newline() ;
void newline_bw() ;
void endline() ;
void endline_bw() ;
static char move() ;
void papermove(double xp, double yp) ;
void draw2(double x, double y) ;
void coor3_bw(double x, double y, double z, double *xp, double *yp) ;
void coor3(double x, double y, double z, double *xp, double *yp) ;
double grey() ;
void draw3_bw(double x, double y, double z) ;
void draw3(double x, double y, double z) ;
void segment_bw(double x1, double y1, double z1, double x2, double y2, double z2) ;
void segment(double x1, double y1, double z1, double x2, double y2, double z2) ;
void curve_bw(trajfunc f, double from, double to, int n) ;
void curve(trajfunc f, double from, double to, int n) ;
void text3_bw(char *c, double x, double y, double z) ;
void text3(char *c, double x, double y, double z) ;
void arrowhead2_bw(double xp, double yp, double xp1, double yp1, double xp2, double yp2, double l, double th) ;
void arrowhead2(double xp, double yp, double xp1, double yp1, double xp2, double yp2, double l, double th) ;
void text3vec_bw(char *c, double x, double y, double z, double dxp, double dyp, double l, double th) ;
void text3vec(char *c, double x, double y, double z, double dxp, double dyp, double l, double th) ;
void arrowhead3_bw(double x, double y, double z, double x1, double y1, double z1, double x2, double y2, double z2, double l, double th) ;
void arrowhead3(double x, double y, double z, double x1, double y1, double z1, double x2, double y2, double z2, double l, double th) ;
void trajarrow_bw(double t, double dt1, double dt2, trajfunc f, double l, double th) ;
void trajarrow(double t, double dt1, double dt2, trajfunc f, double l, double th) ;
void centerarrow_bw(double t, trajfunc f, double l, double th) ;
void centerarrow(double t, trajfunc f, double l, double th) ;
void setlinewidth(double lw) ;
void setfont(char *font) ;
void header() ;
void gfp() ;
void gfp_init() ;

static int pen = UP ;
static double mingrey = MINGREY ;
static double maxgrey = MAXGREY ;
static double oldgrey = 0.0 ;
static double newgrey = 0.0 ;
static double theta = DEFAULT_THETA * DEG ;
static double phi = DEFAULT_PHI * DEG ;
static double xc = X0 * CM ;
static double yc = Y0 * CM ;
static double r = R * CM ;
static double seg = SEGMENT ;
static double xx, xy, yx, yy, yz, zx, zy, zz ;
static double dist = F ;
static double oldxp, oldyp ;
static double axispos[3][3] = {1.2, 0.0, 0.0, 0.0, 1.1, 0.0, 0.0, 0.0, 1.1} ;
static char *axislabel[3] = {"X", "Y", "Z"} ;
static char *axisfont = "mediumfont" ;
static int sz1 = CORPS1 ;
static int sz2 = CORPS2 ;
static int sz3 = CORPS3 ;
static double lw1 = LW1 ;
static double lw2 = LW2 ;

void setgeom(double radius, double x, double y, double distance)
{
	r = radius * CM ;
	xc = x * CM ;
	yc = y * CM ;
	dist = distance ;
}

void setfontsizes(int small, int medium, int big)
{
	sz1 = small ;
	sz2 = medium ;
	sz3 = big ;
}


void setgfplinewidth(double thin, double thick)
{
	lw1 = thin ;
	lw2 = thick ;
}

void setmingrey(double ming)
{
	mingrey = ming ;
}

static void compview()
{
	xx = -sin(phi) ;
	xy = cos(phi) ;
	zz = cos(theta) ;
	yx = -xy * zz ;
	yy = xx * zz ;
	yz = sin(theta) ;
	zx = yz * xy ;
	zy = -yz * xx ;
}

void setview(double th, double ph)
{
	theta = th * DEG ;
	phi = ph * DEG ;
	compview();
}

void setxlabel(char *c, double x, double y, double z)
{
	axislabel[0] = c ;
	axispos[0][0] = x ; axispos[0][1] = y ; axispos[0][2] = z ; 
}

void setylabel(char *c, double x, double y, double z)
{
	axislabel[1] = c ;
	axispos[1][0] = x ; axispos[1][1] = y ; axispos[1][2] = z ; 
}

void setzlabel(char *c, double x, double y, double z)
{
	axislabel[2] = c ;
	axispos[2][0] = x ; axispos[2][1] = y ; axispos[2][2] = z ; 
}

void setaxisfont(char *c)
{
	axisfont = c ;
}

void setsegment(double segment)
{
	seg = segment ;
}

void coor2(double x, double y, double *xp, double *yp)
{
	*xp = x * r + xc ;
	*yp = y * r + yc ;
}

void newline()
{
	if(pen != UP) {
		printf("gfp: newline: previous line in progress...\n") ;
		exit(1) ;
	}
}

void newline_bw()
{
	newline() ;
	printf("n\n") ;
}

void endline()
{
	pen = UP ;
	newgrey = 0.0 ;
	printf("0 g\n") ;
}

void endline_bw()
{
	pen = UP ;
	printf("s\n") ;
}

static char move()
{
	char m ;

	m = (pen==UP) ? 'm' : 'l' ;
	pen = DOWN ;
	return m ;
}

void papermove(double xp, double yp)
{
	printf("%5.1f %5.1f %1c\n", xp, yp, move()) ;
}

void draw2(double x, double y)
{
	double xp, yp ;

	coor2(x, y, &xp, &yp) ;
	papermove(xp, yp) ;
}	

void coor3_bw(double x, double y, double z, double *xp, double *yp)
{
	double f, zl, grl ;
	zl = x * zx + y * zy + z * zz ;
	f = dist / ( dist - zl) ;
	coor2(f*(x * xx + y * xy), f*(x * yx + y * yy + z * yz), xp, yp) ;
}

void coor3(double x, double y, double z, double *xp, double *yp)
{
	double f, zl, grl ;
	zl = x * zx + y * zy + z * zz ;
	f = dist / ( dist - zl) ;
	coor2(f*(x * xx + y * xy), f*(x * yx + y * yy + z * yz), xp, yp) ;
	grl = mingrey + (zl + 1.0)/2.0 * (maxgrey - mingrey) ;
	if(grl > maxgrey) grl = maxgrey ;
	if(grl < mingrey) grl = mingrey ;
	oldgrey = newgrey ;
	newgrey = grl ;
}

double grey()
{
	return (oldgrey < WHITE) ? 1.0-newgrey : 1.0-(oldgrey + newgrey)/2.0 ;
}
	
void draw3_bw(double x, double y, double z)
{
	double xp, yp ;

	coor3_bw(x, y, z, &xp, &yp) ;
	papermove(xp, yp) ;
}	

void draw3(double x, double y, double z)
{
	double xp, yp ;
	char m ;

	coor3(x, y, z, &xp, &yp) ;
	m = move() ;
	if(m == 'l') printf("n %5.1f %5.1f m %5.1f %5.1f l %5.3f g s \n", 
		oldxp, oldyp, xp, yp, grey()) ;
	oldxp = xp ; oldyp = yp ;
}

void segment_bw(double x1, double y1, double z1, double x2, double y2, double z2)
{
	newline_bw() ;
	draw3_bw(x1, y1, z1) ;
	draw3_bw(x2, y2, z2) ;
	endline_bw() ;
}

void segment(double x1, double y1, double z1, double x2, double y2, double z2)
{
	double d ;
	double xp1, yp1, xp2, yp2 ;
	double x, y, z ;
	int nseg, iseg, jseg ;
	
	coor3(x1, y1, z1, &xp1, &yp1) ;
	coor3(x2, y2, z2, &xp2, &yp2) ;
	d = hypot(xp1 - xp2, yp1 - yp2) ;
	nseg = floor(d / seg) + 1 ;
	newline() ;
	for(iseg = 0, jseg = nseg ; iseg <= nseg ; iseg++, jseg--) {
		x = (x1 * iseg + x2 * jseg) / nseg ;
		y = (y1 * iseg + y2 * jseg) / nseg ;
		z = (z1 * iseg + z2 * jseg) / nseg ;
		draw3(x, y, z) ;
	}
	endline() ;
}

void curve_bw(trajfunc f, double from, double to, int n)
{
	double t, dt ;
	double x, y, z ;
	int i ;
	
	dt = (to - from) / n ;
	newline_bw() ;
	for(i=0, t=from ; i<=n ; i++,t+=dt) {
		(*f)(t, &x, &y, &z) ;
		draw3_bw(x, y, z) ;
	}
	endline_bw() ;
}

void curve(trajfunc f, double from, double to, int n)
{
	double t, dt ;
	double x, y, z ;
	int i ;
	
	dt = (to - from) / n ;
	newline() ;
	for(i=0, t=from ; i<=n ; i++,t+=dt) {
		(*f)(t, &x, &y, &z) ;
		draw3(x, y, z) ;
	}
	endline() ;
}

void text3_bw(char *c, double x, double y, double z)
{
	double xp, yp ;

	coor3(x, y, z, &xp, &yp) ;
	printf("%5.1f %5.1f m\n", xp, yp) ;
/* labels in black */
	newgrey = oldgrey = 1.0 ;
	printf("(%s) %5.3f g show\n", c, grey()) ;
/* the next time coor3() is called, oldgrey will be 0
and then the call to grey() will only use the newgrey for the grey level
 see the grey() function*/
	newgrey = 0.0 ; 
}	

void text3(char *c, double x, double y, double z)
{
	double xp, yp ;

	coor3(x, y, z, &xp, &yp) ;
	printf("%5.1f %5.1f m\n", xp, yp) ;
	printf("(%s) %5.3f g show\n", c, grey()) ;
/* the next time coor3() is called, oldgrey will be 0
and then the call to grey() will only use the newgrey for the grey level
 see the grey() function*/
	newgrey = 0.0 ; 
}	

void arrowhead2_bw(double xp, double yp, double xp1, double yp1, double xp2, double yp2, double l, double th)
/* xp, yp ;  pointe */
/* xp1, yp1 ; pt1 de la flèche */
/* xp2, yp2 ; pt2 de la flèche */
/* l, th ; longueur et écartement des traits de pointe */
{
	double xn, yn, norme, xf, yf ;
	double ct, st ;
	
	ct = cos(th) ;
	st = sin(th) ;
	xn = xp1 - xp2 ;
	yn = yp1 - yp2 ;
	norme = hypot(xn, yn) ;
	norme = (norme < 1e-6) ? 0.0 : 1.0/norme ;
	norme *= r * l ;
	xn *= norme ;
	yn *= norme ;
	
	newline_bw() ;
	papermove(xp+(xn*ct-yn*st), yp+(xn*st+yn*ct)) ;
	papermove(xp, yp) ;
	endline_bw() ;	
	newline_bw() ;
	papermove(xp, yp) ;
	papermove(xp+(xn*ct+yn*st), yp+(-xn*st+yn*ct)) ;
	endline_bw() ;	
}

void arrowhead2(double xp, double yp, double xp1, double yp1, double xp2, double yp2, double l, double th)
/* xp, yp ;  pointe */
/* xp1, yp1 ; pt1 de la flèche */
/* xp2, yp2 ; pt2 de la flèche */
/* l, th ; longueur et écartement des traits de pointe */
{
	double xn, yn, norme, xf, yf ;
	double ct, st ;
	
	ct = cos(th) ;
	st = sin(th) ;
	xn = xp1 - xp2 ;
	yn = yp1 - yp2 ;
	norme = hypot(xn, yn) ;
	norme = (norme < 1e-6) ? 0.0 : 1.0/norme ;
	norme *= r * l ;
	xn *= norme ;
	yn *= norme ;
	
	printf("%5.3f g\n", grey()) ;
	newline_bw() ;
	papermove(xp+(xn*ct-yn*st), yp+(xn*st+yn*ct)) ;
	papermove(xp, yp) ;
	endline_bw() ;	
	newline_bw() ;
	papermove(xp, yp) ;
	papermove(xp+(xn*ct+yn*st), yp+(-xn*st+yn*ct)) ;
	endline_bw() ;
	newgrey = 0.0 ;
}

void text3vec_bw(char *c, double x, double y, double z, double dxp, double dyp, double l, double th)
{
	double xp, yp ;

	coor3_bw(x, y, z, &xp, &yp) ;
	newline_bw() ;
	papermove(xp, yp+dyp) ;
	papermove(xp+dxp, yp+dyp) ;
	endline_bw() ;
	arrowhead2_bw(xp+dxp, yp+dyp, xp, yp+dyp, xp+dxp, yp+dyp, l, th) ; 
	text3_bw(c, x, y, z) ;
}

void text3vec(char *c, double x, double y, double z, double dxp, double dyp, double l, double th)
{
	double xp, yp ;

	coor3(x, y, z, &xp, &yp) ;
	printf("%5.3f g\n", grey()) ;
	newline_bw() ;
	papermove(xp, yp+dyp) ;
	papermove(xp+dxp, yp+dyp) ;
	endline_bw() ;
	arrowhead2(xp+dxp, yp+dyp, xp, yp+dyp, xp+dxp, yp+dyp, l, th) ; 
	text3(c, x, y, z) ;
}

void arrowhead3_bw(double x, double y, double z, double x1, double y1, double z1, double x2, double y2, double z2, double l, double th)
/* x, y, z ;  pointe */
/* x1, y1, z1 ; pt1 de la flèche */
/* x2, y2, z2 ; pt2 de la flèche */
/* l, th ; longueur et écartement des traits de pointe */
{
	double xp, yp, xp1, yp1, xp2, yp2 ;
	
	coor3_bw(x, y, z, &xp, &yp) ;
	coor3_bw(x1, y1, z1, &xp1, &yp1) ;
	coor3_bw(x2, y2, z2, &xp2, &yp2) ;
	arrowhead2_bw(xp, yp, xp1, yp1, xp2, yp2, l, th) ;
}
void arrowhead3(double x, double y, double z, double x1, double y1, double z1, double x2, double y2, double z2, double l, double th)
/* x, y, z ;  pointe */
/* x1, y1, z1 ; pt1 de la flèche */
/* x2, y2, z2 ; pt2 de la flèche */
/* l, th ; longueur et écartement des traits de pointe */
{
	double xp, yp, xp1, yp1, xp2, yp2 ;
	
	coor3(x, y, z, &xp, &yp) ;
	coor3_bw(x1, y1, z1, &xp1, &yp1) ;
	coor3_bw(x2, y2, z2, &xp2, &yp2) ;
	arrowhead2(xp, yp, xp1, yp1, xp2, yp2, l, th) ;
}

void trajarrow_bw(double t, double dt1, double dt2, trajfunc f, double l, double th)
{
	double x, y, z, x1, y1, z1, x2, y2, z2 ;
	
	(*f)(t, &x, &y, &z) ;
	(*f)(t-dt1, &x1, &y1, &z1) ;
	(*f)(t+dt2, &x2, &y2, &z2) ;
	arrowhead3_bw(x, y, z, x1, y1, z1, x2, y2, z2, l, th) ;
}

void trajarrow(double t, double dt1, double dt2, trajfunc f, double l, double th)
{
	double x, y, z, x1, y1, z1, x2, y2, z2 ;
	
	(*f)(t, &x, &y, &z) ;
	(*f)(t-dt1, &x1, &y1, &z1) ;
	(*f)(t+dt2, &x2, &y2, &z2) ;
	arrowhead3(x, y, z, x1, y1, z1, x2, y2, z2, l, th) ;
}

void centerarrow_bw(double t, trajfunc f, double l, double th)
{
	double x, y, z ;
	
	(*f)(t, &x, &y, &z) ;
	segment_bw(0.0, 0.0, 0.0, x, y, z) ;
	arrowhead3_bw(x, y, z, 0.0, 0.0, 0.0, x, y, z, l, th) ;
}

void centerarrow(double t, trajfunc f, double l, double th)
{
	double x, y, z ;
	int i ;
	int n = 10 ;
	
	(*f)(t, &x, &y, &z) ;
	newline() ;
	for(i=0 ; i<=n ; i++) {
		draw3(x*i/n, y*i/n, z*i/n) ;
	}
	endline() ;
	arrowhead3(x, y, z, 0.0, 0.0, 0.0, x, y, z, l, th) ;
}

void setlinewidth(double lw)
{
	printf("%4.2f setlinewidth\n", lw) ;
}

void setfont(char *font)
{
	printf("%s setfont\n", font) ;
}

void header()
{
	printf("%%!GFP V1.0\n") ;
	printf("%% ***********************************\n") ;
	printf("%% * gfp PostScript file             *\n") ;
	printf("%% * Creator:  gfp Version: 1.0      *\n") ;
	printf("%% ***********************************\n") ;
	printf("/l /lineto load def\n") ;
	printf("/m /moveto load def\n") ;
	printf("/s /stroke load def\n") ;
	printf("/n /newpath load def\n") ;
	printf("/g /setgray load def\n") ;
	printf("/smallfont /Times-Bold findfont %d scalefont def\n", sz1);
	printf("/mediumfont /Times-Bold findfont %d scalefont def\n", sz2) ;
	printf("/bigfont /Times-Bold findfont %d scalefont def\n", sz3) ;
	printf("/bigsymbolfont /Symbol findfont %d scalefont def\n", sz3) ;
}

void gfp()
{
	double rsph ;
	double inc ;
	int i ;
	int res = RES ;
	
	rsph = dist / sqrt( dist * dist - 1.0) ;
	inc = 2 * M_PI / res ;
	
	setlinewidth(lw1) ;
	newline_bw() ;
	for(i=0 ; i<= res ; i++) draw2(rsph*cos(i*inc), rsph*sin(i*inc)) ;
	endline_bw() ;
	newline() ;
	for(i=0 ; i<= res ; i++) draw3(cos(i*inc), sin(i*inc), 0.0) ;
	endline() ;
	newline() ;
	for(i=0 ; i<= res ; i++) draw3(cos(i*inc), 0.0, sin(i*inc)) ;
	endline() ;
	newline() ;
	for(i=0 ; i<= res ; i++) draw3(0.0, cos(i*inc), sin(i*inc)) ;
	endline() ;

	segment(0.0, 0.0, 0.0, -1.0, 0.0, 0.0) ;
	segment(0.0, 0.0, 0.0, 0.0, -1.0, 0.0) ;
	segment(0.0, 0.0, 0.0, 0.0, 0.0, -1.0) ;
	setlinewidth(lw2) ;
	segment(0.0, 0.0, 0.0, 1.0, 0.0, 0.0) ;
	segment(0.0, 0.0, 0.0, 0.0, 1.0, 0.0) ;
	segment(0.0, 0.0, 0.0, 0.0, 0.0, 1.0) ;
	
	setfont(axisfont) ;
	for(i=0 ; i<3 ; i++) {
		text3_bw(axislabel[i], axispos[i][0], axispos[i][1], axispos[i][2]) ;
	}
}

void gfp_init()
{
	header() ;
	compview() ;
	gfp() ;
}
