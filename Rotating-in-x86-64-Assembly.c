//
// I was challenged in Ubuntu.ir Telegram channel to write a program to rotate n members of an array of numbners for k times
// This program is my 1st piece of mixed C Language + Assembly within two decades. It was necessary to learn GNU Assembler syntax
// as well as 64 bit and new modern x86 instructions.
//
// Copyright by Ali Mirjamali - 2016 under GPLv3 terms
//

#include <stdio.h>
#include <stdint.h>				// It is much better to use new header to define INT values

void rotate(uint64_t[],uint64_t,uint64_t);	// Defining function prototype

int main()
{
	uint64_t a[]={1,2,3,4,5,6,7,8,9,0};	// Example array. It is possible to define your array (or user input)
	uint16_t i;
	printf ("This is the array before rotating:\n");
	for (i=0;i<10;i++)
		printf("Array %llu = %llu\n",(long long int)i,(long long int)a[i]);
	rotate(a,10,3);				// We rotate all 1st 10 members 3 times
	printf ("This is the array after rotating:\n");
	for (i=0;i<10;i++)
		printf("Array %llu = %llu\n",(long long int)i,(long long int)a[i]);
	return 0;
}

void rotate(uint64_t array[],uint64_t n,uint64_t k)
{
	asm
	(
		".myLableStart:		\n\t"	// We start from here. We require a lable for jumping
		"cmp $0,%2		\n\t"	// Is k == 0 ???
		"je .myLableDone	\n\t"	// If it is 0 (or less), we are done. Currently we do not support negative numbers
		"dec %2			\n\t"	// k--
		".myLableRotate:	\n\t"	// We start rotating from this point
		"push %0		\n\t"	// We want to keep the number of array members to rotate
		"push %1		\n\t"	// Let's store the pointer to the array for next rotating
		".myLableSwap:		\n\t"	// We start swaping two items here
		"push (%1)		\n\t"	// Pushing value at pointer to stack
		"push 8(%1)		\n\t"	// Pushing the next item to stack
		"pop (%1)		\n\t"	// Poping the 1st item from stack
		"pop 8(%1)		\n\t"	// Poping the 2nd item from stack. we have changed two array members
		"dec %0			\n\t"	// One done
		"cmp $1,%0		\n\t"	// Is it finished? we need at least two remaining
		"je .myLableFinished	\n\t"	// If finished, exit
		"add $8,%1		\n\t"	// Else increase the pointer
		"jmp .myLableSwap	\n\t"	// Do next swap
		".myLableFinished:	\n\t"	// We finished rotating the array
		"pop %1			\n\t"	// Restoring the pointer to array from stack
		"pop %0			\n\t"	// Restoring the number of array members to be rotated
		"jmp .myLableStart	\n\t"
		".myLableDone:		\n\t"	// We have finished the task
		:
		"+r" (n),
		"+r" (array),
		"+r" (k)
	);
}
