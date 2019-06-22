#ifndef FRANNOR_H_
#define FRANNOR_H_

#include <math.h>
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define AA 12.37586
#define Bsu 0.4878992
#define Csu 12.67706
#define C1 0.9689279
#define C2 1.301198
#define PC 0.01958303
#define XN 2.776994
#define OXN 0.3601016
#define NBITS 24

/* macro to generate a random number uni uniform on [0,1) */
#define UNI(uni) \
	uni = u[i]-u[j]; if (uni<0.0) uni += 1.0; u[i] = uni; \
	if (--i<0) i = 16;  if (--j<0) j = 16

float frannor(void);
void srannor (int seed);

#endif /* FRANNOR_H_ */