//Stanley Chu schu17, Jerry Chen jchen268

//TOP OF LINE LIBRARIES AND CLEARANCE HEADERS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "imageManip.h"
#include "ppm_io.h"
#include "menu.h"
//#include "imageManip.c"
//#include "ppm_io.c"

int main(int argc, char *argv[]) {
    //READ THAT FILE IN BABY
    if (argc < 3) {
        fprintf(stderr, "Missing input or output file names\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if (input == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return 2;
    }

    Image *yeet = read_ppm(input);
    if (yeet == NULL) {
        fprintf(stderr, "Failed to read in file\n");
        return 3;
    }
    //ARRAY OF ARGS
    int args[4];
    for (int i = 0; i < argc - 4; i++) {
        args[i] = atoi(argv[i + 4]);
        if (!args[i]) {
            fprintf(stderr, "Incorrect input type.\n");
            return 5;
        }
    }

    //REV UP THOSE STRINGS FOR INPUT COMPARISON
    char swap[] = "swap";
    char bright[] = "bright";
    char invert_[] = "invert";
    char gray[] = "gray";
    char crop_[] = "crop";
    char blur[] = "blur";
    char edges[] = "edges";

    //AND THE FUNCTION IS...
    if (strcmp(argv[3], swap) == 0) {
        if (argc != 4) {
            fprintf(stderr, "Incorrect number of args\n");
            return 5;
        }
        color_swap(yeet->data, yeet);
    } else if (strcmp(argv[3], bright) == 0) {
        if (argc != 5) {
            fprintf(stderr, "Incorrect number of args\n");
            return 5;
        }
        change_bright(yeet->data, yeet, args[0]);
    } else if (strcmp(argv[3], invert_) == 0) {
        if (argc != 4) {
            fprintf(stderr, "Incorrect number of args\n");
            return 5;
        }
        invert(yeet->data, yeet);
    } else if (strcmp(argv[3], gray) == 0) {
        if (argc != 4) {
            fprintf(stderr, "Incorrect number of args\n");
            return 5;
        }
        grayscale(yeet->data, yeet);
    } else if (strcmp(argv[3], crop_) == 0) {
        if (argc != 8) {
            fprintf(stderr, "Incorrect number of args\n");
            return 5;
        }

        if (crop(yeet->data, yeet, args[0], args[1], args[2], args[3]) == 6) {
            return 6;
        }
    } else if (strcmp(argv[3], blur) == 0) {
        if (argc != 5) {
            fprintf(stderr, "Incorrect number of args\n");
            return 5;
        }
        actually_blur(yeet->data, yeet, args[0]);
    } else if (strcmp(argv[3], edges) == 0) {
        if (argc != 6) {
            fprintf(stderr, "Incorrect number of args\n");
            return 5;
        }
        grayscale(yeet->data, yeet);
        actually_blur(yeet->data, yeet, args[0]);
        edge(yeet->data, yeet, args[1]);
    } else {
        fprintf(stderr, "Invalid operation name or no operation was specified\n");
        return 4;
    }
    //ARE YOU READY TO WRRRIIIIIIIIIITE?
    FILE *sweg = fopen(argv[2], "wb");
    if (sweg == NULL) {
        fprintf(stderr, "output file could not be opened\n");
        return 7;
    }

    int num_written = write_ppm(sweg, yeet);
    if (num_written != yeet->cols * yeet->rows) {
        //fprintf already present in write function
        return 7;
    }

    free(yeet->data);
    free(yeet);

    return 0;
}
