#ifndef LC4_MEMORY_H
#define LC4_MEMORY_H

/*
 * definition of linked list node 
 */ 

struct row_of_memory {
	short unsigned int address ;
	char * label ;
	short unsigned int contents ;
	char * assembly ;
	struct row_of_memory *next ;
} ;


/*
 * declaration of linked list helper functions 
 */

struct row_of_memory* add_to_list    (struct row_of_memory* head, 
				      short unsigned int address, 
				      short unsigned int contents) ;

struct row_of_memory* search_address (struct row_of_memory* head, 
				      short unsigned int address ) ;

struct row_of_memory* search_opcode  (struct row_of_memory* head, 
				      short unsigned int opcode  ) ;

void print_list 		     (struct row_of_memory* head ) ;

struct row_of_memory* delete_list    (struct row_of_memory* head ) ;

#endif
