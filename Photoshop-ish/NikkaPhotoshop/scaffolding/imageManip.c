// Stanley Chu schu17, Jerry Chen jchen268

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "imageManip.h"

/** Function to swap color levels for each pixel. g->r, r->b, b->g.
 * @param img Pointer to image input
 * @param pixels Pointer to the pixels of the input
 * @returns Pointer to swapped image
 * */
Image *color_swap(Pixel *pixels, Image *img) {

    //initialize each color
    unsigned char temp;
    //size of image & what new image size should be
    int size = img->rows * img->cols;
    //Go through array and cycle switching values
    for (int i = 0; i < size; i++) {
        temp = pixels[i].r;
        pixels[i].r = pixels[i].g;
        pixels[i].g = pixels[i].b;
        pixels[i].b = temp;

    }

    return img;
}

/** Make the brightness more or less based on user input.
 *  @param img Pointer to input image
 *  @param factor user input to tell how much brightness to change
 *  @param pixels pixels given
 *  @returns array of changed pixels
 * */
Pixel *change_bright(Pixel *pixels, Image *img, int factor) {
    int change_R;
    int change_G;
    int change_B;
    //size of image & what new image size should be
    int size = img->rows * img->cols;

    //iterate through each  pixel in array and change colors
    for (int i = 0; i < size; i++) {
        change_R = (int) pixels[i].r + factor;
        change_B = (int) pixels[i].b + factor;
        change_G = (int) pixels[i].g + factor;
        //Turns out there can be over or underflow, so should modify
        //number appropriately
        if (change_B > 255) {
            change_B = 255;
        }
        if (change_G > 255) {
            change_G = 255;
        }
        if (change_R > 255) {
            change_R = 255;
        }
        if (change_B < 0) {
            change_B = 0;
        }
        if (change_R < 0) {
            change_R = 0;
        }
        if (change_G < 0) {
            change_G = 0;
        }
        //Actual assignment of new values
        pixels[i].b = (unsigned char) change_B;
        pixels[i].r = (unsigned char) change_R;
        pixels[i].g = (unsigned char) change_G;
    }
    //return changed array of pixels
    return pixels;
}

/** Inverts image color.
 * @param pixels pixels being given to be inverted.
 * @param img   image being modified.
 */
Pixel *invert(Pixel *pixels, Image *img) {
    //size of image & what new image size should be
    int size = img->rows * img->cols;
    for (int i = 0; i < size; ++i) {
        pixels[i].g = 255 - pixels[i].g;
        pixels[i].r = 255 - pixels[i].r;
        pixels[i].b = 255 - pixels[i].b;
    }
    return pixels;
}

/** Puts the image into grayscale.
* @param pixels pixels being given to be inverted.
* @param img   image being modified.
*/
Pixel *grayscale(Pixel *pixels, Image *img) {
    double intensity;
    //size of image & what new image size should be
    int size = img->rows * img->cols;
    for (int i = 0; i < size; ++i) {
        intensity = (0.30 * pixels[i].r) + (0.59 * pixels[i].g) + (0.11 * pixels[i].b);
        //rounds to integer of floating point format
        double rounded = rint(intensity);
        pixels[i].g = (int) rounded;
        pixels[i].r = (int) rounded;
        pixels[i].b = (int) rounded;
    }
    return pixels;
}

/** Crops image by taking initial and final x and y positions
* @param pixels pixels being given to be inverted.
* @param img   image being modified.
 * @returns pointer to cropped image.
*/
int crop(Pixel *pixels, Image *img, int c1, int r1, int c2, int r2) {
    if (c1 == -1 || r1 == -1 || c2 == -1 || r2 == -1) {
        printf("Failed to collect crop parameters.\n");
        return 6;
    }

    int changeRows = r2 - r1 + 1;
    int changeCols = c2 - c1 + 1;
    if (changeRows < 0 || changeCols < 0 || c1 < 0 || c2 < 0 || r1 < 0 || r2 < 0 || c1 >= img->cols ||
        c2 >= img->cols || r1 >= img->rows || r2 >= img->rows) {
        printf("Invalid parameters\n");
        return 6;
    }
    printf("Cropping\n");
    //Create a new array to store what will be cropped
    Pixel *new_pixels = malloc(sizeof(Pixel) * changeRows * changeCols);
    int place = 0;
    for (int i = r1; i < r2 + 1; ++i) {
        for (int j = c1; j < c2 + 1; ++j) {
            new_pixels[place].g = pixels[i * img->cols + j].g;
            new_pixels[place].r = pixels[i * img->cols + j].r;
            new_pixels[place].b = pixels[i * img->cols + j].b;
            place++;
        }
    }
    img->rows = changeRows;
    img->cols = changeCols;
    free(pixels);
    img->data = new_pixels;
    return 0;
}

/** Function to process the given pixel array by creating the Gaussian filter matrix.
 * @param sig value of sigma
 * @returns
 */
Filter *generate_filter(double sig) {
    //initialize some int values and allocate space for filter.
    Filter *filter = malloc(sizeof(Filter));
    int bounds = 0;
    int dimensions = 0;
    //size of filter from sig (span 5* sig in either direction)
    double size = sig * 10;
    double round_size = rint(size);

    //N must always be odd
    if ((int) round_size % 2 == 0) {
        round_size += 1;
    }
    dimensions = (int) round_size;
    bounds = (dimensions - 1) / 2;
    //allocate space for array for the filter
    double *values_filter = malloc(pow(2 * bounds + 1, 2) * sizeof(double));


    int count = 0;
    //this should iterate through each pixel while generating the filter of the appropriate size
    for (int i = -1 * bounds; i < bounds + 1; ++i) {
        for (int j = -1 * bounds; j < bounds + 1; ++j) {
            //given formula
            values_filter[count] = (1.0 / (2.0 * 3.1415926 * pow(sig, 2)))
                                   * exp(-(pow(i, 2) + pow(j, 2)) / (2 * pow(sig, 2)));
            count++;
        }
    }
    //Put our values in the struct fields for the filter
    //Filter struct is in imageManip.h
    filter->ptr_filter = values_filter;
    filter->sigma = sig;
    filter->bound = bounds;
    filter->dimensions = dimensions;
    return filter;
}

/** Function to put the pixel array through our created filter matrix.
 *  This should blur...Separate function for sharpen??
 *  @param two_D pointer to array of arrays to represent image in rows/cols
 *  @param img Image struct for given image
 *  @param filter pointer to given filter
 *  @returns array of blurred pixels
 */
Pixel *blur(Pixel *pixels, Image *img, Filter *filter) {
    Pixel *blurred_pixel_array = malloc(img->rows * img->cols * sizeof(Pixel));

    double sum_r;
    double sum_g;
    double sum_b;

    //Step through filter array in order to get average pixel values for image...
    //First two for loops to get every pixel in the two d array...
    for (int i = 0; i < img->rows * img->cols; ++i) {
        sum_b = 0;
        sum_r = 0;
        sum_g = 0;
        //So these ones will actually get average values for pixels in the image...
        double sum_filter = 0;
        int count = 0;
        for (int r = -1 * filter->bound; r <= filter->bound; ++r) {
            for (int c = -1 * filter->bound; c <= filter->bound; ++c) {
                //if statement to deal with boundaries.
                int curr_idx = i + r * img->cols + c;
                if (curr_idx >= 0 && curr_idx < img->rows * img->cols) {
                    sum_b += ((pixels[curr_idx]).b
                              * filter->ptr_filter[count]);
                    sum_r += ((pixels[curr_idx]).r
                              * filter->ptr_filter[count]);
                    sum_g += ((pixels[curr_idx]).g
                              * filter->ptr_filter[count]);
                    sum_filter += filter->ptr_filter[count];

                }
                count++;
            }
        }
        //Actually assign the appropriate pixels in blurred_pixel_array based on averages above.
        blurred_pixel_array[i].g = sum_g / sum_filter;
        blurred_pixel_array[i].r = sum_r / sum_filter;
        blurred_pixel_array[i].b = sum_b / sum_filter;
    }


    //return the actual blurred image as 1-D
    free(filter->ptr_filter);
    return blurred_pixel_array;
}

/** A function that menu will actually use to blur an image.
 * @param pixels pixels given in the image given
 * @param img image struct for image
 * @param sig sigma value from user
 * @returns blurred_array the array of blurred pixels
 */
Pixel *actually_blur(Pixel *pixels, Image *img, double sig) {
    if (sig <= 0) {
        printf("Invalid sigma.\n");
        return pixels;
    }
    Filter *filter;
    filter = generate_filter(sig);
    Pixel *blurred_array = blur(pixels, img, filter);
    img->data = blurred_array;

    free(filter);
    return pixels;
}


Pixel *edge(Pixel *pixels, Image *img, double threshold) {

    Pixel *new_pixels = malloc(sizeof(Pixel) * img->rows * img->cols);

    for (int i = 0; i < (img->rows * img->cols); i++) {

        if (i >= img->cols && i < (img->rows - 1) * img->cols && (i % img->cols != 0) && ((i + 1) % img->cols != 0)) {

            double x = (pixels[i + 1].g - pixels[i - 1].g) / 2.0;

            double y = (pixels[i + img->cols].g - pixels[i - img->cols].g) / 2.0;

            double intensity = (sqrt(pow(x, 2) + pow(y, 2)));

            if (intensity < 0) {
                intensity *= -1;
            }

            if (intensity > threshold) {
                new_pixels[i].b = 0;
                new_pixels[i].g = 0;
                new_pixels[i].r = 0;
            } else {
                new_pixels[i].b = 255;
                new_pixels[i].g = 255;
                new_pixels[i].r = 255;
            }
        }
    }

    img->data = new_pixels;
    return pixels;
}
