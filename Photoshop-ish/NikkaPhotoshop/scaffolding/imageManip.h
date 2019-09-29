// Stanley Chu schu17, Jerry Chen jchen268


/** IM NOT COMPLETELY SURE IF THIS IS THE RIGHT THING :( . */
#ifndef IMAGEMANIP_H
#define IMAGEMANIP_H

#include "ppm_io.h"

/** Struct representing the filter being used in blur.
 * Has a pointer to the filter, sigma used in blur, bound
 * of length from the center to the edge,
 * dimensions of filter as len/wid.
 */
 typedef struct filter {
     double * ptr_filter;
     double sigma;
     int bound;
     int dimensions;
 }Filter;

/** Function to swap color levels for each pixel. g->r, r->b, b->g.
 * @param img Pointer to image input
 * @param pixels Pointer to the pixels of the input
 * @returns Pointer to swapped image
 * */
Image * color_swap(Pixel * pixels, Image * img);

/** Make the brightness more or less based on user input.
 *  @param img Pointer to input image
 *  @param factor user input to tell how much brightness to change
 *  @param pixels pixels given
 *  @returns array of changed pixels
 * */
Pixel * change_bright(Pixel * pixels, Image * img, int factor);

/** Inverts image color.
 * @param pixels pixels being given to be inverted.
 * @param img   image being modified.
 */
Pixel * invert(Pixel * pixels, Image * img);

/** Puts the image into grayscale.
* @param pixels pixels being given to be inverted.
* @param img   image being modified.
*/
Pixel * grayscale(Pixel * pixels, Image * img);

/** Crops image by taking initial and final x and y positions
* @param pixels pixels being given to be inverted.
* @param img   image being modified.
 * @returns pointer to cropped image.
*/
int crop(Pixel* pixels, Image * img, int x1, int y1, int x2, int y2);

/** Turns the read 1D array from read to a 2D array...
 *
 */

Filter *generate_filter(double sig);

/** A function that menu will actually use to blur an image.
 * @param pixels pixels given in the image given
 * @param img image struct for image
 * @param sig sigma value from user
 * @returns blurred_array the array of blurred pixels
 */
Pixel * actually_blur(Pixel * pixels, Image * img, double sig);

/** Function to put the pixel array through our created filter matrix.
 *  This should blur...Separate function for sharpen??
 */
Pixel * blur(Pixel * pixels, Image * img, Filter * filter);



Pixel * edge(Pixel * pixels, Image * img, double threshold);


#endif
