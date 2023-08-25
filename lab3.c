#include <stdio.h>
#include <stdlib.h>

int inputNum, original, reverse=0, addedDigits=0, sumOfBoth;

void main(int argc, char *argv[]) 
{
	
	//convert command line argument to an int then assign it to inputNum
	inputNum = atoi(argv[1]);

	//verify input is greater than 9
	if(inputNum < 10)
    {
		printf("Sorry, I only accept numbers 10 and greater\n");
	}
    else
    {
		//reverse input and assign it to reverse
		//add digits of original number together
		original = inputNum;
		while(original > 0) 
		{
			int remainder = original%10;
			addedDigits += remainder;

			reverse = reverse*10+remainder;
			original = original/10;
		}
		printf("Original: %d   Reverse: %d\nDigits of original number added: %d\n", inputNum, reverse, addedDigits);
		
		//add reversed and original input together
		sumOfBoth = inputNum + reverse;
		printf("Sum of original and reverse numbers: %d\n", sumOfBoth);
	}
}
