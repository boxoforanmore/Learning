// sinetext2.c : write sinewave as text

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Conditional constant definition
#ifndef M_PI
#define M_PI (3.141592654)
#endif


enum {ARG_NAME, ARG_NSAMPS, ARG_FREQ, ARG_SR, ARG_NARGS};

int main(int argc, char* argv[]) {

    int      i, nsamps;
    double   samp, freq, srate;
    double   twopi = 2 * M_PI;
    double   angleincr;

    if (argc != ARG_NARGS) {
        fprintf(stderr, "usage: sinetext2 nsamps freq srate\n");
        return 1;
    }

    nsamps    = atoi(argv[ARG_NSAMPS]);
    freq      = atof(argv[ARG_FREQ]);
    srate     = atof(argv[ARG_SR]);
    angleincr = twopi * freq / srate;

    for(i=0; i < nsamps; i++) {
        samp = sin(angleincr * i);
        fprintf(stdout, "%.8lf\t%.8lf\n", samp, samp * samp);
    }

    fprintf(stderr, "Done\n");
    return 0;
}
