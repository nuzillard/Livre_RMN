#define LW1 0.25
#define LW2 1.0
#define LW3 2.0
#define CORPS1 12
#define CORPS2 14
#define CORPS3 18
#define ARROWANGLE M_PI/12
#define DEFAULT_THETA 70
#define DEFAULT_PHI 20
#define INFTY 1000000.0

typedef void (*trajfunc)(double t, double *x, double *y, double *z) ;

extern void setgeom(double radius, double x, double y, double distance) ;
extern void setfontsizes(int small, int medium, int big) ;
extern void setgfplinewidth(double thin, double thick) ;
extern void setmingrey(double ming) ;
extern void setview(double th, double ph) ;
extern void setxlabel(char *c, double x, double y, double z) ;
extern void setylabel(char *c, double x, double y, double z) ;
extern void setzlabel(char *c, double x, double y, double z) ;
extern void setaxisfont(char *c) ;
extern void setsegment(double segment) ;
extern void coor2(double x, double y, double *xp, double *yp) ;
extern void newline() ;
extern void newline_bw() ;
extern void endline() ;
extern void endline_bw() ;
extern void papermove(double xp, double yp) ;
extern void draw2(double x, double y) ;
extern void coor3_bw(double x, double y, double z, double *xp, double *yp) ;
extern void coor3(double x, double y, double z, double *xp, double *yp) ;
extern double grey() ;
extern void draw3_bw(double x, double y, double z) ;
extern void draw3(double x, double y, double z) ;
extern void segment_bw(double x1, double y1, double z1, double x2, double y2, double z2) ;
extern void segment(double x1, double y1, double z1, double x2, double y2, double z2) ;
extern void curve_bw(trajfunc f, double from, double to, int n) ;
extern void curve(trajfunc f, double from, double to, int n) ;
extern void text3_bw(char *c, double x, double y, double z) ;
extern void text3(char *c, double x, double y, double z) ;
extern void arrowhead2_bw(double xp, double yp, double xp1, double yp1, double xp2, double yp2, double l, double th) ;
extern void arrowhead2(double xp, double yp, double xp1, double yp1, double xp2, double yp2, double l, double th) ;
extern void text3vec_bw(char *c, double x, double y, double z, double dxp, double dyp, double l, double th) ;
extern void text3vec(char *c, double x, double y, double z, double dxp, double dyp, double l, double th) ;
extern void arrowhead3_bw(double x, double y, double z, double x1, double y1, double z1, double x2, double y2, double z2, double l, double th) ;
extern void arrowhead3(double x, double y, double z, double x1, double y1, double z1, double x2, double y2, double z2, double l, double th) ;
extern void trajarrow_bw(double t, double dt1, double dt2, trajfunc f, double l, double th) ;
extern void trajarrow(double t, double dt1, double dt2, trajfunc f, double l, double th) ;
extern void centerarrow_bw(double t, trajfunc f, double l, double th) ;
extern void centerarrow(double t, trajfunc f, double l, double th) ;
extern void setlinewidth(double lw) ;
extern void setfont(char *font) ;
extern void header() ;
extern void gfp() ;
extern void gfp_init() ;
