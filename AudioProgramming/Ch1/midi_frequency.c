/* From the Audio Programming Cookbook */
#include <stdio.h>
#include <math.h>


int main() {

    double semitone_ratio;
    double c0;               // For frequency of MIDI Note 0
    double c5;               // For frequency of Middle C

    double frequency;        // The frequency we are looking for
    int midinote;            // The note that is given

    ////////////////////////////////
    // Calculate Required Numbers //
    ////////////////////////////////

    // For even/equal temperament
    semitone_ratio = pow(2, 12.0);  // Should be close to 1.0594631
    
    // Find middle C
    // Low A => 220 Hz
    c5 = 220.0 * pow(semitone_ratio, 3);
    
    // MIDI Note 0 == C (5 octaves below middle C)
    c0 = c5 * pow(0.5, 5);


    // Calculate frequency for given note number
    midinote = 74;  // D above A=440
    frequency = c0 * pow(semitone_ration, midinote);

    printf("MIDI Note %d has frequency %f\n,"midinote,frequency);

    return 0;
}
