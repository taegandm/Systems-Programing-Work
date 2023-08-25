#include <stdio.h>

// Taegan Maishman

/*
 * vi is a bit confusing (mainly remebering commands), but I'm sure I'll get the hang of it
 * I also want to mention that if time would allow, I would love to be inperson for your class, I really enjoy your teaching style and would prefer to be in person. Due to my other responsibilites, I am not sure I can make the time :(
*/

// PI is the ratio of diameter to the circumfrence of a circle
#define PI 3.14159

/*
I'm now going to declare my variables
calculated variables on one line input viariables on another
this is not required, but any rule-of-thumb is good in variable names
*/

double weight, volume, batchWeight, innerA, outerA, area;
double innerD, outerD, density, thickness;
int quantity;

void main()
{
  printf("Please enter the Inner Diameter of the Washer in cm: ");
  scanf("%lf", &innerD);
  printf("Please enter the Outer Diameter of the Washer in cm: ");
  scanf("%lf", &outerD);
  printf("Please enter the density of the material of the Washer in g/cm2: ");
  scanf("%lf", &density);
  printf("Please enter the thickness of the washer in cm: ");
  scanf("%lf", &thickness);
  printf("Please enter the number of washers ordered: ");
  scanf("%d", &quantity);

  innerA = PI*innerD/2*innerD/2;
  outerA = PI*outerD/2*outerD/2;
  area = outerA - innerA;
  volume = area * thickness;
  weight = volume * density;
  batchWeight = quantity*weight; 

  printf("The Rim Area of the washer is %10.5lf\n", area);
  printf("The weight of one washer is %10.5lf\n", weight);
  printf("The weight of the batch of washers is %10.5lf\n", batchWeight);
}
