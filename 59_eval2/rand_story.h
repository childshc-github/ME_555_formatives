#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use
void format_checker(char * fname);
catarray_t * create_catarray(void);
void free_catarry(catarray_t * stats);
void category_checker(char * fname);
catarray_t * readCW(char * fname);
void print_story(char * fname, catarray_t * carr);

#endif
