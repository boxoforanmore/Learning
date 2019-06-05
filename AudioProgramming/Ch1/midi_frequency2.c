#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    double c5, c0, semitone_ratio, frequency;
    int midinote;
    char message[256];
    char* result;

    semitone_ratio = pow(2, 1.0/12.0);
    c5 = 220.0 * pow(semitone_ratio, 3);
    c0 = c5 * pow(0.5, 5);

    printf("Enter MIDI note (0 - 127): ");
    result = fgets(message, 128, stdin);
    midinote = atoi(message);

    while ((result == NULL) || (message[0] == '\0') || (midinote < 0) || (midinote >  127)) {
        if (result == NULL) {
            printf("There was an error reading the input\n");
        }
        else if (message[0] == '\0') {
            printf("Please enter a numeric (integer) MIDI value");
        }
        else if (midinote < 0) {
            printf("%s is a bad MIDI note number", message);
        }
        else if (midinote > 127)
        {
            printf("%s is beyond the range of a valid MIDI note number", message);
        }

        result = fgets(message, 128, stdin);
        midinote = atoi(message);
    }

    frequency = c0 * pow(semitone_ratio, midinote);
    printf("frequency of MIDI note %d = %f\n", midinote, frequency);
    
    return 0;
}
