#include <math.h>
#include "libsimu1.h"

void matmult(Mat33 m, Vec3 v1, Vec3 v2)
{
	Vec3 tmp ;
	int i, j ;

	for(i=0 ; i<3 ; i++) {
		tmp[i] = 0 ;
		for(j=0 ; j<3 ; j++)
			tmp[i] += m[i][j] * v1[j] ;
	}
	for(i=0 ; i<3 ; i++) v2[i] = tmp[i] ;
}

void matrot(Mat33 m, Vec3 v, double angle)
{
	double ca, ca1, sa, f ;
	int i, j ;

	ca = cos(angle) ;
	sa = sin(angle) ;
	ca1 = 1-ca ;
	for(i=0 ; i<3 ; i++) 
		m[i][i] = ca + ca1 * v[i] * v[i] ; 
	for(i=1 ; i<3 ; i++) for(j=0 ; j<i ; j++)
			m[i][j] = m[j][i] = ca1 * v[i] * v[j] ;
	for(i=1 ; i<3 ; i++) for(j=0 ; j<i ; j++) {
		f = v[3-i-j] * ((i-j-1) ? (-1) : 1) * sa ;
		m[i][j] += f ;
		m[j][i] -= f ;
	}
}

