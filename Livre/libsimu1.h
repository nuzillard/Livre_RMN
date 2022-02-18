#include <math.h>

typedef double Mat33[3][3] ;
typedef double Vec3[3] ;

void matmult(Mat33 m, Vec3 v1, Vec3 v2) ;
void matrot(Mat33 m, Vec3 v, double angle) ;
