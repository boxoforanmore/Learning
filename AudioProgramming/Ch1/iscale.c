// Calculates ET frequencies for N-note octaves from a given midinote

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


char filename[40];

int print_info(double frequency, double step_ratio, int notes, int write_ratios) {
    double frequencies[24];

    printf(filename);

    if (write_ratios) {
    }

    int i;
    for(i = 0; i < notes; i++){
        frequencies[i] = frequency;
        frequency *= step_ratio;
    }

    if (write_ratios) {
        for(i = 0; i < notes; i++) {
            printf("%d\t:\t%f Hz\n, %f", i, frequencies[i], pow(step_ratio, i));
        }
    }
    else {
        for(i = 0; i < notes; i++) {
            printf("%d\t:\t%f\n", i, frequencies[i]);
        }
    }
    return 0;
}






int main(int argc, char* argv[]) {

    int notes, midinote;
    double base_frequency, step_ratio;
    double c0, c5;
    // double frequencies[24];

    int read_as_midi = 0;
    int write_ratios = 0;
    int open_file = 0;
    int interval = 0;
    double startval;
    int err = 0;

    FILE *fp;

    if (argc < 3) {
        printf("\n%s : Calculates the even-tempered frequency for N-note octaves\n", argv[0]);
        printf("---------\n"); 
        printf("usage: %s [-m] [-i] N startval [outfile.txt]\n\n", argv[0]);
        printf("options:\n\t-m : interpret startval as a MIDI note\n");
        printf("\t(default: interpret as frequency in hertz)\n\n");
        printf("\t-i : print interval ratios as well as frequency values\n");
        printf("\t(default: print just freqeuncy values)\n\n");
        printf("\toutfile.txt : name of optional file to write to\n\n");
        return 0;
    }

    int i;
    argv++;
    argc--;
    for(i = 0; i < argc; i++) {
        if (argv[0][0] == '-') {
            char flag;
            flag = argv[0][1];
            if (flag == 'm') {
                read_as_midi = 1;
            }
            else if (flag == 'i') {
                write_ratios = 1;
            }
            else {
                printf("ERROR: %s is not a valid flag\n", argv[i]);
                return 1;
            }
        }
        argv++;
        argc--
    }
        else {

            if(strstr(argv[0], ".txt")) {
                continue;
            }
            else {
                if (strstr(argv[0], ".")) {
                    printf("ERROR: %s is not a valid number or output file name");
                    return 1;
                }
                else if (!notes) {
                    notes = atoi(argv[0]);
                    if (notes < 1) {
                        printf("ERROR: Notes parameter must be positive\n");
                        return 1;
                    }
                    else if (notes > 24) {
                        printf("ERROR: Maximum available notes in octave is 24\n");
                        return 1;
                    }
                }
                else if (!startval) {
                    startval = atof(argv[0]);
                }
                else {
                    printf("ERROR: %s is not a valid number or output file name");
                }
            }
        }

        argv++;
    }



    if (read_as_midi) {
        midinote = startval;
        if (midinote < 0) {
            printf("ERROR: %s is a bad midinote value\n", midinote);
            return 1;
        }
        else if (midinote > 127) {
            printf("ERROR: the maximum midinote value is 127\n");
            return 1;
        }

        step_ratio = pow(2.0, 1.0/12.0);

        c5 = 220.0 * pow(step_ratio, 3);
        c0 = c5 * pow(0.5, 5);

        base_frequency = c0 * pow(step_ratio, midinote);
    }
    else {
        frequency = startval;
    }

    step_ratio = pow(2.0, 1.0/12.0);

    for(i = 0; i < notes; i++) {
        frequencies[i] = frequency;
        base_frequency *= step_ratio;
    }

    if (argv[0]) {
        
    }


   /**
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
    **/
    return 0;
}
