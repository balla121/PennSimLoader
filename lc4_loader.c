#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"

/* declarations of functions that must defined in lc4_loader.c */

FILE* get_file() 
{
	char userInputFileName [40];
	FILE* filePtr = NULL;

	printf("Please enter the file name: ");
	scanf("%s", userInputFileName);

	filePtr = fopen(userInputFileName, "r");
	
	return filePtr;
}

int parse_file (FILE* my_obj_file, struct row_of_memory** memory) 
{
	int first_byte;
	int second_byte;
	int first_word;
	char sect_type = 'c';
	int address;
	int len_of_contents = 0;
	int contents;
	struct row_of_memory* this_row = NULL;
	int counter;
	char temp_char;

	while (1) {

		first_byte = fgetc(my_obj_file);
		if (first_byte == EOF) {
			return 0;
		}

		second_byte = fgetc(my_obj_file);
		first_word = (first_byte<<8) + second_byte;
	
		if (first_word == 0xCADE) {
			sect_type = 'c';
		} else if (first_word == 0xDADA) {
			sect_type = 'd';
		} else if (first_word == 0xC3B7) {
			sect_type = 's';
		}

		first_byte = fgetc(my_obj_file);
		second_byte = fgetc(my_obj_file);
		address = (first_byte<<8) + second_byte;

		first_byte = fgetc(my_obj_file);
		second_byte = fgetc(my_obj_file);
		len_of_contents = (first_byte<<8) + second_byte;

		if (sect_type == 'c' || sect_type == 'd') {			

			while (len_of_contents > 0) {
				first_byte = fgetc(my_obj_file);
				second_byte = fgetc(my_obj_file);
				contents = (first_byte<<8) + second_byte;
				
				*memory = add_to_list(*memory, address, contents);

				len_of_contents--;
				address++;
			}
		} else if (sect_type == 's') {
			this_row = search_address(*memory, address);
			/*if ((this_row == NULL) || (this_row->label != NULL)) {
				continue;
			}*/

			if (this_row == NULL) {
				continue;
			}
			if (this_row->label != NULL) {
				//printf("\ndouble label encountered!\n");
				free(this_row->label);
				//printf("\nfreeing a label\n");
			}

			char* test = (char*)malloc(len_of_contents + 1);
			//printf("\nmalloc'ing for a label");
			fread(test, 1, len_of_contents, my_obj_file);
			test[len_of_contents] = '\0';
			
			this_row->label = test;
		}
	}

	return 0 ;
}