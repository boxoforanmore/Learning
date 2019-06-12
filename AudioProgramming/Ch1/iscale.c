// Calculates ET frequencies for N-note octaves from a given midinote

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void print_info(char *argv[20]) {

    printf("\n%s : Calculates the even-tempered frequency for N-note octaves\n", argv[0]);
    printf("---------\n"); 
    printf("usage: %s [-m] [-i] N startval [outfile.txt]\n\n", argv[0]);
    printf("options:\n\t-m : interpret startval as a MIDI note\n");
    printf("\t(default: interpret as frequency in hertz)\n\n");
    printf("\t-i : print interval ratios as well as frequency values\n");
    printf("\t(default: print just freqeuncy values)\n\n");
    printf("\toutfile.txt : name of optional file to write to\n\n");
}




int main(int argc, char* argv[]) {

    int notes, midinote;
    double base_frequency, step_ratio, frequency;
    double c0, c5;
    double frequencies[24];

    int read_as_midi = 0;
    int write_intervals = 0;
    int open_file = 0;
    int interval = 0;
    double startval;
    int err = 0;

    char program_name[20];

    FILE *fp;

    if (argc < 3) {
        print_info(argv);
        return 0;
    }

    strncpy(program_name, argv[0], 18);

    int i;
    argv++;
    argc--;
    while (argc > 1) {
        if (argv[0][0] == '-') {
            char flag;
            flag = argv[0][1];
            if (flag == 'm') {
                read_as_midi = 1;
            }
            else if (flag == 'i') {
                write_intervals = 1;
            }
            else {
                printf("ERROR: %s is not a valid flag\n", argv[i]);
                return 1;
            }

        argv++;
        argc--;
        }
        else {
            break;
        }
    }
    
    if (argc < 2) {
        printf("ERROR: Insufficient arguments\n");
        print_info(program_name);
        return 1;
    }   

    
    // Parse rest of arguments
    notes = atoi(argv[0]);

    if ((notes < 1) || (notes > 24)) {
        printf("ERROR: Notes (N) parameter must be between 1 and 24\n");
        return 1;
    }

    startval = atof(argv[1]);


    if (read_as_midi) {
        midinote = startval;

        step_ratio = pow(2.0, 1.0/12.0);

        c5 = 220.0 * pow(step_ratio, 3);
        c0 = c5 * pow(0.5, 5);

        base_frequency = c0 * pow(step_ratio, midinote);
    }
    else {
        if (startval <= 0.0) {
            printf("ERROR: The frequency must be a positive number");
            return 1;
        }
        else {
            base_frequency = startval;
        }
    }

    step_ratio = pow(2.0, 1.0/notes);

    frequency = base_frequency;

    for(i = 0; i < notes; i++) {
        frequencies[i] = frequency;
        frequency *= step_ratio;
    }


    fp = NULL;
    if (argc == 3) {
        fp = fopen(argv[2], "w");
        if (fp == NULL) {
            printf("WARNING: Unable to create file: %s\n",argv[3]);
            perror("");
        }
    }

    for(i = 0; i < notes; i++) {
        if (write_intervals) {
            printf("%d:\t%f\t%f\n", i, pow(step_ratio, i), frequencies[i]);
        }
        else {
            printf("%d:\t%f\n", i, frequencies[i]);
        }

        if (fp) {
            if (write_intervals) {
                if (!fprintf(fp, "%d:\t%f\t%f\n", i, pow(step_ratio, i), frequencies[i])) {
                    err = -1;
                }
            }
            else {
                if (!fprintf(fp, "%d:\t%f\n", i, frequencies[i])) {
                    err = -1;
                }
            }

            if (err < 0) {
                break;
            }
        }        
    }


    if (err < 0) {
        perror("There was an error writing the file.\n");
    }

    if (fp) {
        fclose(fp);
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
