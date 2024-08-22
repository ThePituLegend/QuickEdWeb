#include "include/quicked.h" // Include the QuickEdit header file
#include <emscripten.h>
#include <stdio.h>
#include <string.h>

EMSCRIPTEN_KEEPALIVE
int quicked_aligner(char* pattern, char* text, int* score, char* cigar) {
    quicked_aligner_t aligner;                          // Aligner object
    quicked_status_t status;                            // Return code from QuickEdit functions
    quicked_params_t params = quicked_default_params(); // Get a set of sensible default parameters.

    // Without any extra configuration, the aligner will use the Quicked algorithm

    status = quicked_new(&aligner, &params);            // Initialize the aligner with the given parameters
    if (quicked_check_error(status)) {
        fprintf(stderr, "%s", quicked_status_msg(status));
        return 1;
    }

    // Align the sequences!
    status = quicked_align(&aligner, pattern, strlen(pattern), text, strlen(text));
    if (quicked_check_error(status)) {
        fprintf(stderr, "%s", quicked_status_msg(status));
        return 1;
    }

    *score = aligner.score;
    strcpy(cigar, aligner.cigar);

    status = quicked_free(&aligner);        // Free whatever memory the aligner allocated
    if (quicked_check_error(status)) {
        fprintf(stderr, "%s", quicked_status_msg(status));
        return 1;
    }

    return 0;
}