#include <stdio.h>

//declare variables for temperatures / distances
double input, fahrenheit, celsius, kelvin, feet, miles, meters;

void main() 
{	
	//prompt user for input
	printf("Please enter a number to be converted> ");
	scanf("%lf", &input);
	

	//assign input to fahrenheit and calculate celsius and kelvin
	fahrenheit = input;
	celsius = (fahrenheit-32)*5/9;
	kelvin = (fahrenheit+459.67)*5/9;

	//if kelvin is below zero, display text instead
	if(kelvin < 0) {
		printf("%-.2fF is %-.2fC and the number entered cannot be converted to Kelvin because it is below Absolute 0\n", fahrenheit, celsius);
	}
	else {
		printf("%-.2fF is %-.2fC and %-.2fK\n", fahrenheit, celsius, kelvin);
	}


	//assign input to celsius and calculate fahrenheit and kelvin
	celsius = input;
	fahrenheit = celsius*9/5+32;
	kelvin = celsius+273.15;

	//if kelvin is below zero, display text instead
	if(kelvin < 0) {
		printf("%-.2fF is %-.2fC and the number entered cannot be converted to Kelvin because it is below Absolute 0\n", fahrenheit, celsius);
	}
	else {
		printf("%-.2fC is %-.2fF and %-.2fK\n", celsius, fahrenheit, kelvin);
	}


	//assign input to kelvin and calculate fahrenheit and celsius
	kelvin = input;
	fahrenheit = (kelvin*9/5)-459.67;
	celsius = kelvin-273.15;

	//if kelvin is less than zero, inform user computations cannot be performed
	if(kelvin < 0) {
		printf("The number entered cannot be converted because it is below Absolute 0\n");
	}
	else {
		printf("%-.2fK is %-.2fF and %-.2fC\n\n", kelvin, fahrenheit, celsius);
	}


	//if input is negative, convert it to a positive before distance calculations
	if(input < 0) {
		input = input*-1;
	}


	//assign input to feet and calculate miles and meters
	feet = input;
	miles = feet / 5280;
	meters = feet * 0.3048;
	printf("%-.2fft is %-.2f miles and %-.2fm\n", feet, miles, meters);


	//assign input to miles and calculate feet and meters
	miles = input;
	feet = miles * 5280;
	meters = miles * 1609.344;
	printf("%-.2f miles is %-.2fft and %-.2fm\n", miles, feet, meters);


	//assign input to meters and calculate feet and miles
	meters = input;
	feet = meters * 3.28084;
	miles = meters / 1609.344;
	printf("%-.2fm is %-.2fft and %-.2f miles\n\n", meters, feet, miles);
}
