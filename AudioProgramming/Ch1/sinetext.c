// sinetext.c : write sinewave as text

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Conditional constant definition
#ifndef M_PI
#define M_PI (3.141592654)
#endif


int main(int argc, char* argv[]) {

    int      i, nsamps;
    double   samp;
    double   twopi = 2 * M_PI;
    double   angleincr;

    nsamps = 50;   // Number of points to create
    angleincr = twopi / nsamps;

    for(i=0; i < nsamps; i++) {
        samp = sin(angleincr * i);
        fprintf(stdout, "%.8lf\n", samp);
    }

    fprintf(stderr, "Done\n");
    return 0;
}
