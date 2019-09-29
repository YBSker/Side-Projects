// Stanley Chu schu17, Jerry Chen jchen268
// __Add your name and JHED above__
// ppm_io.c
// 601.220, Spring 2019
// Starter code for midterm project - feel free to edit/add to this file

#include <assert.h>
#include "ppm_io.h"
#include <stdlib.h>
#include <stdio.h>
/* Read a PPM-formatted image from a file (assumes fp != NULL).
 * Returns the address of the heap-allocated Image struct it
 * creates and populates with the Image data.
 */


Image * read_ppm(FILE *fp) {
  int rgb_scale = 255;
 
  // check that fp is not NULL
  if (fp == NULL) {
    fprintf(stderr, "File could not be opened");
    return NULL;
  }
  //used to hold values returned by fscanf so I can compare those values
  char c;
  int x;

  // check first line
  fscanf(fp, " %c", &c);
  if (c != 'P'){
    fprintf(stderr, "Bad file - char in first line not P");
    return NULL;
  }
  fscanf(fp, " %d", &x);
  if (x != 6){
    fprintf(stderr, "Bad file - int in first line not 6");
    return NULL;
  }
  // check for comment line
  c = fscanf(fp, " %c", &c);
   if (c == '\001'){
    char comment[1000];
    fgets(comment, 1000, fp);
  }

  //allocate space for image struct
  Image *ppm = (Image *) malloc (sizeof(Image));
  if(!ppm){
    fprintf(stderr, "Memory allocation for Image Struct Failed");
    return NULL;
  }

  //collect cols and rows and color
  if (fscanf(fp," %d  %d", &ppm->cols, &ppm->rows) != 2){
    fprintf(stderr,"Failed to collect cols and rows");
    return NULL;
  }
  if (fscanf(fp, " %d", &x) != 1){
    fprintf(stderr, "Failed to collect color num");
    return NULL;
  }
  if (x!=rgb_scale){
    fprintf(stderr, "Color scale is not 255");
    return NULL;
  }
  fgetc(fp);

  //collect pixels
  ppm->data = malloc(sizeof(Pixel) * ppm->cols * ppm->rows);
  if(!ppm->data){
    printf("image data array allocation failed");
    return NULL;
  }
  x = fread(ppm->data, sizeof(Pixel), ppm->cols * ppm->rows, fp);
  if (x!=ppm->cols * ppm->rows){
    printf("Read wrong number of pixels");
    return NULL;
  }
  return ppm;
  
}


/* Write a PPM-formatted image to a file (assumes fp != NULL),
 * and return the number of pixels successfully written.
 */
int write_ppm(FILE *fp, const Image *im) {

  // check that fp is not NULL
  assert(fp); 

  // write PPM file header, in the following format
  // P6
  // cols rows
  // 255
  fprintf(fp, "P6\n%d %d\n255\n", im->cols, im->rows);

  // now write the pixel array
  int num_pixels_written = fwrite(im->data, sizeof(Pixel), im->cols * im->rows, fp);

  if (num_pixels_written != im->cols * im->rows) {
    fprintf(stderr, "Uh oh. Pixel data failed to write properly!\n");
    return 7;
  }
  //fputc('\n', fp);

  return num_pixels_written;
}

