#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]) {
	//declare variables
	int inputNum, original, reverse=0, addedDigits=0, sumOfBoth, remainderNum;

	//declare pointer variables
	int *inputNum_pointer, *original_pointer, *reverse_pointer, *addedDigits_pointer, *sumOfBoth_pointer, *remainder_pointer;

	//declare pointer-to-pointer variables
	int **inputNum_print, **reverse_print, **addedDigits_print, **sumOfBoth_print;

	//assign memory addresses to pointer variables
	inputNum_pointer = &inputNum;
	original_pointer = &original;
	reverse_pointer = &reverse;
	addedDigits_pointer = &addedDigits;
	sumOfBoth_pointer = &sumOfBoth;
	remainder_pointer = &remainderNum;

	//assign pointer memory addresses to pointer-to-pointer variables
	inputNum_print = &inputNum_pointer;
	reverse_print = &reverse_pointer;
	addedDigits_print = &addedDigits_pointer;
	sumOfBoth_print = &sumOfBoth_pointer;

	//convert command line argument to an int then assign it to inputNum
	inputNum = atoi(argv[1]);

	//verify input is greater than 9
	if(*inputNum_pointer < 10)
       	{
		printf("Sorry, I only accept numbers 10 and greater\nNum: %d", *inputNum_pointer);
	}
       	else
       	{
		//reverse input and assign it to reverse using pointers
		//add digits of original number together using pointers
		original = *inputNum_pointer;
		while(*original_pointer > 0) 
		{
			remainderNum = 0;	
			*remainder_pointer = *original_pointer%10;
			*addedDigits_pointer += *remainder_pointer;

			*reverse_pointer = *reverse_pointer*10+*remainder_pointer;
			*original_pointer = *original_pointer/10;
		}
		//print original, reverse, and digits added using pointer-to-pointer variables
		printf("Original: %d   Reverse: %d\nDigits of original number added: %d\n", **inputNum_print, **reverse_print, **addedDigits_print);
		
		//add reversed and original input together using pointer-to-pointer variables
		sumOfBoth = *inputNum_pointer + *reverse_pointer;
		printf("Sum of original and reverse numbers: %d\n\n", **sumOfBoth_print);

		//print all memory variables memory addresses
		printf("Memory Addresses:\ninputNum: %d\noriginal: %d\nreverse: %d\naddedDigits: %d\nsumOfBoth: %d\nremainder: %d\ninputNum_pointer: %d\noriginal_pointer: %d\nreverse_pointer: %d\naddedDigits_pointer: %d\nsumOfBoth_pointer: %d\nremainder_pointer %d\ninputNum_print: %d\nreverse_print: %d\naddedDigits_print: %d\nsumOfBoth_print: %d\n", &inputNum, &original, &reverse, &addedDigits, &sumOfBoth, &remainderNum, &inputNum_pointer, &original_pointer, &reverse_pointer, &addedDigits_pointer, &sumOfBoth_pointer, &remainder_pointer, &inputNum_print, &reverse_print, &addedDigits_print, &sumOfBoth_print);
	}
}
