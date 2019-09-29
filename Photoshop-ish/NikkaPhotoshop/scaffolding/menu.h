// Stanley Chu schu17, Jerry Chen jchen268


/** IM NOT COMPLETELY SURE IF THIS IS THE RIGHT THING :( . */
#ifndef MENU_H
#define MENU_H

#include "ppm_io.h"
#include "imageManip.h"

/** Print out the menu options. */
void generate_menu();

/** Actually collect the selected option. 'Detail' Input to be put in after option selected.
 *
 */
char * collectInput();

/** Collect extra info if read or write.
 *  @returns pointer to array input has been placed.
 */
char * collect_file_info();

/** Collect number information.
 * @returns value scanned
 */
double collect_number();

/** Collect image boundaries for crop. */
int * collect_boundaries();

/** Interpret valid input, do what is asked for.
 * @param
 */
Pixel * interpret(char * input, Image * img, Pixel * pixels);

/** Allocates memory and calls functions to actually do project things.
 *
 * @return 0 if done.
 */
int project();

#endif