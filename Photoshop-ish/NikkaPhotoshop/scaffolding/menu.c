//Stanley Chu schu17, Jerry Chen jchen268

/** I THINK WE NEED A MENU OR SMTH SO WE CAN ACTUALLY RUN STUFF. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "imageManip.h"
#include "ppm_io.h"
#include "ppm_io.c"
#include "imageManip.c"
/** Print out the menu options. */
void generate_menu() {
    printf("Main Menu:\n");
    printf("Enter the number corresponding to the option desired.\n");
    printf("\t 1 <file> - READ the image in <file>\n");
    printf("\t 2 <file> - WRITE image to <file>\n");
    printf("\t 3 - SWAP COLORS (red to blue, blue to green, green to red)\n");
    printf("\t 4 <amount> - change BRIGHTNESS of image by given amount\n");
    printf("\t 5 - INVERT the color intensity\n");
    printf("\t 6 - convert the image to GRAYSCALE\n");
    printf("\t 7 <x1> <y1> <x2> <y2> - CROP the image to something with given corners\n");
    printf("\t 8 <amt> - BLUR image by given amount\n");
    printf("\t 9 <amt> - detect EDGES with an intensity above given amount\n");
    printf("\t 0 - QUIT\n");
    printf("Enter Option: ");
}

/** Actually collect the selected option. 'Detail' Input to be put in after option selected.
 *
 */
 char * collectInput() {
     char * input = malloc(2 * sizeof(char));
     char c;

     //TODO: FIGURE OUT WHAT TO DO IF NO INPUT?>??
     scanf("%c", &c);
     input[0] = c;
    scanf("%c", &c);
    if (isspace(c)) {
        input[1] = '\0';
        //clears my input stream
        ungetc(c, stdin);
        return input;
    } else {
        printf("Invalid. Please choose a valid option\n");
        return input;
    }

 }

 /** Collect extra info if read or write.
  *  @returns pointer to array input has been placed.
  */
  char * collect_file_info() {
      char c;
      int i = 0;
      //kind of decided to determine arbitrary max size of a file name
      char * input = malloc(200 * sizeof(char));
      scanf("%c", &c);
      while(isspace(c)) {
          scanf("%c", &c);
      }
      input[i] = c;
      while (c != '\n' && i < 199) {
          scanf("%c", &c);
          input[++i] = c;
      }
//      input[++i] = '\0';
      return input;
  }

  /** Collect number information.
   * @returns value scanned
   */
  double collect_number() {
      double val;
      scanf("%lf", &val);
      return val;
  }

  /** Collect image boundaries for crop. */
  int * collect_boundaries(){
      int *boundaries = malloc(4 * sizeof(int));
      for(int i = 0; i < 4; ++i) {
          boundaries[i] = -1;
      }

      scanf("%d %d %d %d", &boundaries[0], &boundaries[1], &boundaries[2], &boundaries[3]);
      return boundaries;
  }

 /** Interpret valid input, do what is asked for.
  * @param
  */
 Pixel * interpret(char * input, Image * img, Pixel * pixels) {
     char * remainder = malloc(200 * sizeof(char));
     Image * image;
     double bright;
     int * boundaries;
     double sig;
     switch (input[0]) {
         case '0' :
             free(input);
             return pixels;
         case '1' :
             remainder = collect_file_info();
             //Opens the file thingy and closes if no exist.
             FILE *fp = fopen(remainder, "rb");
             if (!fp) {
                 printf("Image couldn't be loaded, please enter valid path.\n");
                 return pixels;
             }
             image = read_ppm(fp);
             pixels = image->data;
             fclose(fp);
             free(input);
             free(input);
             return pixels;
         case '2' :
             input = collect_file_info();
             FILE *rp = fopen(remainder, "wb");
             if (!rp) {
                 return pixels;
             }
             if (!pixels) {
                 printf("No image, please re-read.\n");
                 return pixels;
             }
             int written = write_ppm(rp, img);
             if (written == 7) {
                 printf("Failed to write.\n");
             }
             fclose(rp);
             free(input);
             free(input);
             return pixels;
         case '3' :
             printf("Shifting colors...\n");
             free(input);
             image = color_swap(pixels, img);
             return image->data;
         case '4' :
             bright = collect_number();
             printf("Adjusting brightness\n");
             free(input);
             return change_bright(pixels, img, (int) bright);
         case '5' :
             printf("Inverting colors.\n");
             free(input);
             return invert(pixels, img);
         case '6' :
             printf("Converting to grayscale.\n");
             free(input);
             return grayscale(pixels, img);
         case '7' :
             boundaries = collect_boundaries();
             pixels = crop(pixels, img, boundaries[0], boundaries[1], boundaries[2], boundaries[3]);
             free(boundaries);
             return pixels;
         case '8' :
	   
             sig = collect_number();
             printf("Blurring the image.\n");
             return actually_blur(pixels, img, sig);
//         case '9' :
//
//             break;
     }
     return pixels;
 }

 /** Allocates memory and calls functions to actually do project things.
  *
  * @return 0 if done.
  */
 int project() {
     Image * ptr_image = malloc(sizeof(Image));
     Pixel * arr_pixels = NULL;

     int quit = 0;
     char * valid = NULL;
     while(quit == 0) {
         generate_menu();
         valid = collectInput();
         if (valid) {
             if (valid[0] == '0') {
                 free(valid);
                 quit = 1;
                 printf("Ending Program.\n");
             }
             if (quit == 0 && valid) {
                 arr_pixels = interpret(valid, ptr_image, arr_pixels);
             }
         }
     }
     valid = NULL;
     free(ptr_image);
     free(arr_pixels);
     return 0;
 }
