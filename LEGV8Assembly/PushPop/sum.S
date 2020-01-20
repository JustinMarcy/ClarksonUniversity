.globl sum

sum:

SUBS XZR, X0, #1 	// compare n and 1
B.EQ nIsOne		 	// if n>=1, skip to n=1 case and return value
SUB SP, SP, #16     // adjust stack for 2 items
STUR X30, [SP,#8]  	// save the return address
STUR X0, [SP,#0]  	// save the argument n
SUB X0, X0, #1		// De-increment n
BL sum				// Jump to sum
MOV X12, X0			// Move Result
LDR X30, [SP,#8]    // restore the return address
LDR X0, [SP,#0]     // return from BL: restore argument n
ADD SP, SP, #16     // adjust stack pointer to pop 2 items
ADD X0, X0, X12		// add result to n
BR X30              // return to the caller

nIsOne:
mov X0, #1			// move 1 to n
BR X30				// return to the caller
