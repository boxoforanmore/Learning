// sf2float.c : convert soundfile to floats

#include <stdlib.h>
#include <stdio.h>
#include <portsf.h>


enum {ARG_PROGNAME, ARG_INFILE, ARG_OUTFILE, ARG_AMPFAC, ARG_NARGS};


int main(int argc, char* argv[]) {
    PSF_PROPS props;
    long framesread, totalread;
    
    // Initialize all resource variables to default states
    int ifd = -1;
    int ofd = -1;
    int error = 0;
    int i;
    float ampfac;

    psf_format outformat = PSF_FMT_UNKNOWN;
    PSF_CHPEAK* peaks = NULL;

    float* frame = NULL;

    printf("SFGAIN: change level of soundfile\n");

    if (argc < ARG_NARGS) {
        printf("ERROR: insufficient arguments.\nusage:\n\tsf2float infile outfile ampfac\n\twhere ampfac > 0\n");
        return 1;
    }

    ampfac = (float) atof(argv[ARG_AMPFAC]);
    if (ampfac <= 0.0) {
        printf("ERROR: ampfac must be positive\n");
        return 1;
    }

    // Be good, and startup pportsf
    if (psf_init()) {
        printf("ERROR: unable to start portsf\n");
        return 1;
    }

    ifd = psf_sndOpen(argv[ARG_INFILE], &props, 0);
    if (ifd < 0) {
        printf("ERROR: unable to open infile %s\n", argv[ARG_INFILE]);
        return 1;
    }

    // We now have a soundfile resource
    // therefore: use goto now for any errors

    // Make sure we can ouput to outfile extension
    outformat = psf_getFormatExt(argv[ARG_OUTFILE]);
    if (outformat == PSF_FMT_UNKNOWN) {
        printf("ERROR: outfile with name %s has unknown format\nUse any of: '.wav' '.aiff' '.aif' '.aif'\n", argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }

    props.format = outformat;
     
    ofd = psf_sndCreate(argv[2], &props, 0, 0, PSF_CREATE_RDWR);
    if (ofd < 0) {
        printf("ERROR: unable to create outfile %s\n", argv[ARG_OUTFILE]);
        error++;
        goto exit;
    }

    // Allocate space for sample frame
    frame = (float*) malloc(props.chans * sizeof(float));
    if (frame == NULL) {
        puts("ERROR: No memory!\n");
        error++;
        goto exit;
    }

    // Allocate space for PEAK info
    peaks = (PSF_CHPEAK*) malloc(props.chans * sizeof(PSF_CHPEAK));
    if(peaks == NULL) {
        puts("ERROR: No memory!\n");
        error++;
        goto exit;
    }

    printf("INFO: copying...");

    // Single frame loop to do copy, report any errors
    framesread = psf_sndReadFloatFrames(ifd, frame, 1);
    totalread  = 0; // Total count of sample frames read

    while(framesread == 1) {
        totalread++;

        for(i=0; i < props.chans; i++) {
            frame[i] *= ampfac;
        }

        if(psf_sndWriteFloatFrames(ofd, frame, 1) != 1) {
            printf("ERROR: error writing to outfile\n");
            error++;
            break;
        }
        // Do processing here!
        framesread = psf_sndReadFloatFrames(ifd, frame, 1);
    }

    if (framesread < 0) {
        printf("Error reading infile. Outfile is incomplete.\n");
        error++;
    }
    else {
        printf("DONE: %ld sample frames copied to %s\n", totalread, argv[ARG_OUTFILE]);
    }

    // Report PEAK values to user
    if (psf_sndReadPeaks(ofd, peaks, NULL) > 0) {
        long i;
        double peaktime;

        printf("Peak Information:\n");
        for(i=0; i < props.chans; i++) {
            peaktime = (double) peaks[i].pos / props.srate;

            printf("CH %ld:\t%.4f at %.4f secs\n", i+1, peaks[i].val, peaktime);
        }
    }

    /////////////
    // Cleanup //
    /////////////

    exit:
    if (ifd >= 0)
        psf_sndClose(ifd);
    if (ofd >= 0)
        psf_sndClose(ofd);
    if (frame)
        free(frame);
    if (peaks)
        free(peaks);
    psf_finish();

    return error;
}
