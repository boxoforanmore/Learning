// Calculates ET frequencies for N-note octaves from a given midinote

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    int notes, midinote;
    double frequency, step_ratio;
    double c0, c5;
    double frequencies[24];


    if (argc != 3) {
        printf("%s : Calculates the even-tempered frequency for N-note octaves\n", argv[0]); 
        printf("\tusage: %s notes midinote\n", argv[0]);
        printf("\targs:\tnotes => number of notes in scale\n");
        printf("\t\tmidinote => midinote to start new scale\n");
        return 0;
    }

    notes = atoi(argv[1]);

    if (notes < 1) {
        printf("ERROR: Notes parameter must be positive\n");
        return 1;
    }

    if (notes > 24) {
        printf("ERROR: Maximum available notes in octave is 24\n");
        return 1;
    }


    midinote = atoi(argv[2]);

    if (midinote < 0) {
        printf("ERROR: %s is a bad midinote value\n", argv[2]);
        return 1;
    }

    if (midinote > 127) {
        printf("ERROR: the maximum midinote value is 127\n");
        return 1;
    }


    // Calculate starting frequency
    step_ratio = pow(2.0, 1.0/12.0);

    c5 = 220.0 * pow(step_ratio, 3);
    c0 = c5 * pow(0.5, 5);

    frequency = c0 * pow(step_ratio, midinote);


    // Calculate new frequencies
    step_ratio = pow(2.0, 1.0/notes);
    
    int i;
    for(i = 0; i < notes; i++) {
        frequencies[i] = frequency;
        frequency *= step_ratio;
    }

    for(i = 0; i < notes; i++) {
        printf("%d\t:\t%f\n", i, frequencies[i]);
    }

    return 0;
}
