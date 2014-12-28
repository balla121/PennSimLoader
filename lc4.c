#include <stdio.h>
#include "lc4_memory.h"
#include <stdio.h>
#include "lc4_loader.h"
#include "lc4_disassembler.h"

/* program to mimic LC4's program & data memory */

int main () {

	/**
	 * main() holds the linked list &
	 * only calls functions in other files 
	 */

	/* step 1: create head pointer to linked list: memory 	*/
	FILE* filePtr;
	struct row_of_memory* memory = NULL;
	struct row_of_memory** memoryPtr = &memory;
	
	/* step 2: call function: get_file() in lc4_loader.c 	*/
	filePtr = get_file();
	if (filePtr == NULL) {
		fprintf(stderr, "Error reading in the file\n");
		return 1;
	}
	
	/* step 3: call function: parse_file() in lc4_loader.c 	*/
	if (parse_file(filePtr, memoryPtr) != 0) {
		fprintf(stderr, "Error parsing the file\n");
		return 2;
	}

	if (fclose(filePtr) != 0) {
		fprintf(stderr, "Error closing the file\n");
	}


	/* step 4: call function: reverse_assemble() in lc4_disassembler.c */
	if (reverse_assemble(memory) != 0) {
		fprintf(stderr, "Error reverse-assembling the file\n");
		return 3;
	}


	/* step 5: call function: print_list() in lc4_memory.c 	*/
	print_list(memory);	


	/* step 6: call function: delete_list() in lc4_memory.c */
	delete_list(memory);


	/* only return 0 if everything works properly */
	return 0 ;
}
