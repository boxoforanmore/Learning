// tforkraw.c : generate raw sfile with native endianness
//              * based on tfork2.c

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#ifndef M_PI
#define M_PI (3.141592654)
#endif


enum {ARG_NAME, ARG_OUTFILE, ARG_DUR, ARG_HZ, ARG_SR, ARG_AMP, ARG_TYPE, ARG_NARGS};
enum samptype {RAWSAMP_SHORT, RAWSAMP_FLOAT};

// Comment below directly from book
/* Thanks to the SNDAN programmers for this
 *
 * Return 0 for big-endian machine, 1 for little-endian machine
 * so we can tell user what order the data is 
 */
int byte_order() {
    int one = 1;
    char* endptr = (char *) &one;
    return (*endptr);
}


const char* endianness[2] = {"big_endian", "little_endian"};


int main(int argc, char* argv[]) {
    unsigned int i, nsamps;
    unsigned int maxframe = 0;
    unsigned int samptype, endian, bitreverse;

    double samp, dur, freq, srate, amp, step;
    double start, end, fac, maxsamp;
    double twopi = 2.0 * M_PI;
    double angleincr;

    FILE* fp = NULL;
    float fsamp;
    short ssamp;

    if (argc != ARG_NARGS) {
        fprintf(stderr, "usage: tforkraw outsfile.raw dur freq srate amp isfloat\n");
        return 1;
    }

    dur       = atof(argv[ARG_DUR]);
    freq      = atof(argv[ARG_HZ]);
    srate     = atof(argv[ARG_SR]);
    amp       = atof(argv[ARG_AMP]);
    samptype  = (unsigned int) atoi(argv[ARG_TYPE]);
    nsamps    = (int) (dur * srate);
    angleincr = twopi * freq / nsamps;
    step      = dur/nsamps;

    if (samptype > 1) {
        fprintf(stderr, "ERROR: sample type can only be 0 or 1 (short or float, respectively)\n");
        return 1;
    }

    // Create binary file; 'b' flag isn't required for all operating systems
    fp = fopen(argv[ARG_OUTFILE], "wb");

    if (fp == NULL) {
        fprintf(stderr, "ERROR: error creating output file %s\n", argv[ARG_OUTFILE]);
        return 1;
    }

    // Use normalized range and scale to amperage
    start = 1.0;
    end   = 1.0e-4;
    maxsamp = 0.0;
    fac = pow(end/start, 1.0/nsamps);
    endian = byte_order();
    
    fprintf(stderr, "Writing %d, %s samples\n", nsamps, endianness[endian]);
    
    // Check samptype and run appropriate loop
    if (samptype == RAWSAMP_SHORT) {
        for(i=0; i < nsamps; i++) {
            samp = amp * sin(angleincr*i);
            samp *= start;
            start *= fac;

            // Use 32767 to avoid overflow problem
            ssamp = (short) (samp * 32767.0);

            if (fwrite(&ssamp, sizeof(short), 1,  fp) != 1) {
                fprintf(stderr, "ERROR: error writing data to file\n");
                return 1;
            }
            
            if (fabs(samp) > maxsamp) {
                maxsamp = fabs(samp);
                maxframe = i;
            }
        }
    }
    else {
        for(i=0; i < nsamps; i++) {
            samp = amp * sin(angleincr*i);
            samp *= start;
            start *= fac;

            fsamp = (float) samp;

            if (fwrite(&fsamp, sizeof(float), 1, fp) != 1) {
                fprintf(stderr, "ERROR: error writing data  to file\n");
                return 1;
            }

            if (fabs(samp) > maxsamp) {
                maxsamp = fabs(samp);
                maxframe = i;
            }
        }
    }

    fclose(fp);
    fprintf(stderr, "Done.  Maximum sample value = %.8lf at frame %d\n", maxsamp, maxframe);
    return 0;
}
