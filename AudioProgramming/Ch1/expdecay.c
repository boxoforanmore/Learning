// Implementation of formula:
// x[t] = a * exp(-k/T)
// s.t.  a and k are constants
//       T is the decay rate

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

enum {ARG_NARGS};

int main(int argc, char* argv[])  {

    int      i, nsteps;
    double   step, x, a, T, k;
    double   dur;

    if (argc != ARG_NARGS) {
        printf("expdecay.c: for exponential decay\n");
        printf("usage: expdecay dur T steps\n");
        printf("args:\tdur\t=> duration of decrease\n");
        printf("\tT\t=> the decay rate\n");
        printf("\tsteps\t=> the number of steps to decrease\n");
        return 1;
    }

    dur = atof(argv[1]);
    T = atof(argv[2]);
    nsteps = atoi(argv[3]);

    k = dur/nsteps;    // Constant time increment
    a = exp(-k/T);     // Constant ratio value
    x = 1.0;           // Starting value

    step = 0.0;

    for(i=0; i < nsteps; i++) {
        printf("%.4lf\t%.8lf\n",step,x);
        x = a * x;
        step += k;
    }

    return 0;
}
