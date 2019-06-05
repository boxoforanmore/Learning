// Converts frequency to appropriate MIDI note
#include <stdio.h>
#include <math.h>

int main() {

    double semitone_ratio;
    double c0;
    double c5;
    double frequency;
    int midinote;
    double fracmidi;
    int midi_frequency;
    double bend;
    int pitchbend;

    semitone_ratio = pow(2, 1.0/12.0);
    c5 = 220.0 * pow(semitone_ratio, 3);
    c0 = c5 * pow(0.5, 5);

    // Given frequency to convert
    frequency = 400.;
    fracmidi = log(frequency/c0) / log(semitone_ratio);

    // Round to nearest whole number to find note
    midinote = (int) (fracmidi + 0.5);

    midi_frequency = c0 * pow(semitone_ratio, midinote);

    if (frequency >= midi_frequency) {
        bend = (frequency-midi_frequency) / ((c0 * pow(semitone_ratio, (midinote+1))) - midi_frequency);
    }
    else {
        bend = - (midi_frequency-frequency) / (midi_frequency - (c0 * pow(semitone_ratio, (midinote-1))));
    }

    pitchbend = (int) (bend * 100);

    printf("The nearest MIDI note to the frequency %f is %d\n", frequency, midinote);
    printf("The pitchbend is ~%d%%\n", pitchbend);

}
