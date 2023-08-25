#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

void main() {
	//store epoch time of birthday start and end
	time_t epochbirth;
	time_t bdaystart, bdayend;

	//store start and end of program in seconds and nanosecond
	struct timespec start;
	struct timespec end;

	//store tm structs to assign inputted date
	struct tm inputbday;
	struct tm *bday;
	struct tm pbday;

	//variables to store input, and secons / nanoseconds elapsed in the program
	int month, day, year, secs, nanosecs, einput; 

	//used to print final results
	char buf[200];

	//used to verify user input is some form of yes or no
	char input[20];
	char switchcase;

	//store current time
	timespec_get(&start, TIME_UTC);
	
	//explain what epoch time is
	printf("Epoch time is the current amount of seconds elapsed since January 1st, 1970, at 00:00:00. It is a consistant measurement used by computers to keep track of and calculate time.\n");

	//prompt user input
	printf("Do you know your birthday in epoch time?\n");
	scanf("%s", &input);

	//verify user input is some form of yes or no, otherwise ask again
	switchcase = tolower(input[0]);
	while(switchcase != 'y' && switchcase != 'n') {	
		printf("Please enter some form of \"yes\" or \"no\"\n");
		scanf("%s", &input);
		switchcase = tolower(input[0]);
	}

	//depending on answer, prompt user for date or epoch time and convert
	switch(switchcase)
	{
		case 'y':
			//accept epoch input
			printf("Great! Enter your birthday in epoch time: ");
			scanf("%i", &einput);

			//store epoch time
			epochbirth = einput;
			break;
		case 'n':
			//accept birth date
			printf("That's alright, enter your birthday in mm/dd/yyyy format: ");
			scanf("%i/%i/%i", &month, &day, &year);

			//store in time struct
  			inputbday.tm_mon=month - 1;
  			inputbday.tm_mday=day;
  			inputbday.tm_year=year-1900;
  			inputbday.tm_hour=0;
  			inputbday.tm_min=0;
  			inputbday.tm_sec=0;
			inputbday.tm_isdst = -1;

			//convert to epoch time
  			epochbirth = mktime(&inputbday);
			break;
		default:
			//error in selection
			//should never reach this code
			printf("Something went wrong, sorry!\n");
			exit(1);
	}
	
	//convert to UTC time
	bday = gmtime(&epochbirth);
	pbday = *gmtime(&epochbirth);

	//get epoch value range
	bday->tm_hour = 0;
	bday->tm_min = 0;
	bday->tm_sec = 0;	
	bdaystart = mktime(bday)-18000;
	
	bday->tm_hour = 23;
	bday->tm_min = 59;
	bday->tm_sec = 59;	
	bdayend = mktime(bday)-18000;
	
	//create amd print birthday info string
	strftime(buf, sizeof buf, "\nThe date you entered, %B %d, %Y, was a %A, and was the %jth day of the year.", &pbday);
	printf("%s Depending on the time, the epoch date was between %i and %i\n", buf, bdaystart, bdayend);
	
	//store end of process and calculate / display how long the code took
	timespec_get(&end, TIME_UTC);
	secs = end.tv_sec - start.tv_sec;
	nanosecs = end.tv_nsec - start.tv_nsec;
	printf("This process took %i.%09ld seconds\n", secs, nanosecs);
}
