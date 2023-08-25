#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//race for a random number of laps
void main(int argc, char *argv[]) {
	//store number of laps
	int loop = atoi(argv[1]);
	//store name and country
	char country[50] = "", lastName[50] = "";
	strcat(country, argv[2]);
	strcat(lastName, argv[3]);

	//loop for given amount of laps in 1 second increments
	for(int i = 0; i < loop; i++) {
		printf("There GOES %s from %s\n", country, lastName);
		sleep(1);
	}
	//print end of race
	printf("%s from %s FINISHES!!!!\n", country, lastName);
}
