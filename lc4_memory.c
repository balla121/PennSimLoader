#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lc4_memory.h"

struct row_of_memory* add_to_list    (struct row_of_memory* head, 
				      short unsigned int address, 
				      short unsigned int contents) 
{
	/* takes in head pointer to a linked list: head
	   creates a new node with address & contents passed in
	   adds node to end of linked list pointed to by head
	   if list is empty, new node is now head
	   always returns head pointer */
	   
	/* add node to the end of linked list pointed to by "head"
	   if list doesn't exist, create 1st node */
	 
	/* allocate memory for a single node */

	struct row_of_memory* next_row = NULL;
	struct row_of_memory* new_row = malloc(sizeof(struct row_of_memory));
	//printf("\nmalloc'ing for a new row of memory");

	/* populate fields in newly allocated node w/ address&contents */

	new_row->address = address;
	new_row->contents = contents;

	new_row->label = NULL;
	new_row->assembly = NULL;
	new_row->next = NULL;

	/* if head==NULL, node created is the new head of the list! */
	/* otherwise, traverse linked list until we reach the end */

	if (head == NULL) {
		head = new_row;
	} else {
		next_row = head;

		while (next_row->next != NULL) {
			next_row = next_row->next;
		}

		/* add node to the end of list */
		next_row->next = new_row;
	}

	/* always return pointer to head of linked list */
	return head;
}

struct row_of_memory* search_address (struct row_of_memory* head, 
				      short unsigned int address ) 
{
	/* traverse linked list, searching each node for "address"  */
	
	struct row_of_memory* this_row = head;
	
	while (this_row != NULL && this_row->address != address) {
		this_row = this_row->next;
	}

	/* return pointer to node in list that matches */
	
	return this_row;
}

struct row_of_memory* search_opcode  (struct row_of_memory* head, 
				      short unsigned int opcode  ) 
{
	/* traverse linked list until node is found with matching opcode
	   AND "assembly" field of node is empty */

	struct row_of_memory* this_row = head;
	
	while (1) {


		if (this_row == NULL) {
			break;
		}

		if (((0b1111000000000000 & this_row->contents) == (opcode<<12)) && (this_row->assembly == NULL)) {
			break;
		}
		
		this_row = this_row->next;

	}

	/* return pointer to node in list that matches */
	/* return NULL if list is empty or if no matching nodes */
	 
	return this_row;
}

void print_list (struct row_of_memory* head ) 
{

	printf("\n<label>\t\t<address>\t<contents>\t<assembly>");

	struct row_of_memory* this_row = head;

	/* make sure head isn't NULL */
	if (this_row == NULL) {
		return;
	}
	
	while (this_row != NULL) {
		
		printf("\n");
		if (this_row->label == NULL) {
			printf("\t\t");
		} else {
			printf("%s", this_row->label);
			if (strlen(this_row->label) >= 8){
				printf("\t");
			} else {
				printf("\t\t");
			}
		}
		printf("%x\t\t%x\t\t", this_row->address, this_row->contents);

		if (this_row->assembly != NULL) {
			printf("%s", this_row->assembly);
		}
		
		this_row = this_row->next;
	}

	printf("\n\n");
	
	/* traverse linked list, print contents of each node */	

	return ;
}

struct row_of_memory* delete_list    (struct row_of_memory* head ) 
{
	/* delete entire list node by node */

	struct row_of_memory* this_row = head;
	struct row_of_memory* temp;

	while (this_row != NULL) {
		//printf("\n");
		temp = this_row->next;
		if (this_row->label != NULL) {
			//printf("freeing a label\n");
			free(this_row->label);
		}
		if (this_row->assembly != NULL) {
			//printf("freeing an assembly field\n");
			free(this_row->assembly);
		}
		free(this_row);
		//printf("freeing a row of memory\n");
		this_row = temp;
	}

	return NULL ;
}