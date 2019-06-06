#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {

    double c0, c5, semitone_ratio, frequency;
    int midinote;

    semitone_ratio = pow(2.0, 1.0/12.0);
    c5 = 220.0 * pow(semitone_ratio, 3);
    c0 = c5 * pow(0.5, 5);

    if (argc != 2) {
        printf("%s : converts MIDI note to frequency. \n", argv[0]);
        printf("\tusage : %s <MIDI_note>\n", argv[0]);
        printf("\trange : 0 <= MIDI_note <= 127\n");
        return 0;
    }

    midinote = atoi(argv[1]);

    if (midinote < 0)  {
        printf("Bad MIDI note value: %s\n", argv[1]);
        return 1;
    }

    if (midinote >  127) {
        printf("%s is beyond the valid MIDI range\n", argv[1]);
        return 1;
    }

    frequency = c0 * pow(semitone_ratio, midinote);
    printf("Frequency of MIDI note %d = %f\n", midinote, frequency);
    return 0;
}
