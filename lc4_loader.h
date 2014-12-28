#include <stdio.h>
#include "lc4_memory.h"

/* declarations of functions that must defined in lc4_loader.c */



/**
 * prompts the user for the name of a .OBJ input file, and
 * opens it for reading.
 *
 * returns the FILE pointer upon success, else NULL.
 */ 
FILE * get_file() ;



/**
 * parses the given input file into an ordered (by memory address) 
 * linked list with the passed in row_of_memory as the head.
 *
 * returns 0 upon successs, non-zero if an error occurs.
 */
int parse_file (FILE* my_obj_file, struct row_of_memory** memory) ;
