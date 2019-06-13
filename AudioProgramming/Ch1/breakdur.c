#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define BUFFERSIZE 1024
#define SAMPLE float
#define SAMPLELEN 1048576

///////////////////////////////////
///////////////////////////////////

typedef unsigned short WORD;
typedef unsigned long  DWORD;

typedef struct breakpoint {
    double time;
    double value;
} BREAKPOINT;

typedef struct soundfile_info {
    DWORD n_samples;
} SFLIN;

///////////////////////////////////
///////////////////////////////////

BREAKPOINT maxpoint(const BREAKPOINT* points, long npoints) {
    BREAKPOINT point;
    
    point.time = points[0].time;
    point.value = points[0].value;

    int i;
    for(i=0; i < npoints; i++) {
        if(point.value < points[i].value) {
            point.value = points[i].value;
            point.time = points[i].time;
        }
    }
    return point;
}

BREAKPOINT* get_breakpoints(FILE* fp, long* psize) {
    int got;
    long npoints = 0;
    long size = 64;
    double lasttime = 0.0;
    BREAKPOINT* points = NULL;
    char line[80];

    if (fp == NULL) {
        return NULL;
    }

    points = (BREAKPOINT*) malloc(sizeof(BREAKPOINT) * size);

    if (points == NULL) {
        return NULL;
    }

    while(fgets(line, 80, fp)) {
        got = sscanf(line, "%lf%lf", &points[npoints].time, &points[npoints].value);

        if (got < 0) {
            // Empty line case
            continue;
        }
        if (got == 0) {
            printf("ERROR: line %ld contains non-numeric data\n", (npoints+1));
            break;
        }
        if (got == 1) {
            printf("ERROR: Incomplete breakpoint found at line %ld\n", (npoints+1));
            break;
        }

        if (points[npoints].time < lasttime) {
            printf("ERROR: Data error at line %ld: time not increasing", (npoints+1));
            break;
        }

        lasttime = points[npoints].time;

        if (++npoints == size) {
            BREAKPOINT* tmp;
            size += npoints;
            tmp = (BREAKPOINT*) realloc(points, sizeof(BREAKPOINT) *size);

            if (tmp == NULL) {
                // Not enough memory to continue
                // Memory needs to be realeased, return NULL
                npoints = 0;
                free(points);
                points = NULL;
                break;
            }
            points = tmp;
        }
    }

    if (npoints) {
        *psize = npoints;
    }

    return points;
}


int main(int argc, char* argv[]) {

    long    size;
    double  dur;
    BREAKPOINT point, *points;
    FILE *fp;

    printf("breakdur: find duration of breakpoint file\n");

    if (argc < 2) {
        printf("usage: breakdur infile.txt \n");
        return 0;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        return 0;
    }

    size = 0;
    points = get_breakpoints(fp, &size);

    if (points == NULL) {
        printf("ERROR: No breakpoints read.\n");
        fclose(fp);
        return 1;
    }

    if (size < 2) {
        printf("ERROR: At least two breakpoints required\n");
        fclose(fp);
        return 1;
    }

    // Breakpoints must start from 0
    if (points[0].time != 0.0) {
        printf("Error in breakpoint data: first time must be 0.0\n");
        free(points);
        fclose(fp);
        return 1;
    }

    printf("Read %ld breakpoints\n", size);

    dur = points[size-1].time;
    printf("Duration: %f seconds\n", dur);

    point = maxpoint(points, size);
    printf("Maximum value: %f at %f secs\n", point.value, point.time);

    free(points);
    fclose(fp);
    
    return 0;
}
