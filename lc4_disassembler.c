#include <stdio.h>
#include <stdlib.h>
#include "lc4_memory.h"

int reverse_assemble (struct row_of_memory* memory) 
{

	struct row_of_memory* this_row = NULL;

	while(1) {	

		this_row = search_opcode(memory, 0001);

		if (this_row == NULL) {
			break;
		} else {
			char* temp = (char*)malloc(13);
			//printf("\nmalloc'ing for an assembly instruction");
			int rt = (this_row->contents & 0b0000000000000111);
			int rs = (this_row->contents & 0b0000000000111000)/(8);
			int rd = (this_row->contents & 0b0001110000000000)/(1024);
			if ((this_row->contents & 0b0000000000111000) == 0b0000000000000000) {
				sprintf(temp, "ADD R%x R%x R%x", rd, rs, rt);
			} else if ((this_row->contents & 0b0000000000111000) == 0b0000000000001000) {
				sprintf(temp, "MUL R%x R%x R%x", rd, rs, rt);
			} else if ((this_row->contents & 0b0000000000111000) == 0b0000000000010000) {
				sprintf(temp, "SUB R%x R%x R%x", rd, rs, rt);
			} else if ((this_row->contents & 0b0000000000111000) == 0b0000000000011000) {
				sprintf(temp, "DIV R%x R%x R%x", rd, rs, rt);
			} else if ((this_row->contents & 0b0000000000100000) == 0b0000000000100000) {
				int imm5 = (this_row->contents & 0b0000000000011111);
				if (imm5 > 15) {
					imm5 = -32 + imm5;
				}
				sprintf(temp, "ADD R%x R%x %d", rd, rs, imm5);
			}
			this_row->assembly = temp;
		}
	}
	return 0;
}