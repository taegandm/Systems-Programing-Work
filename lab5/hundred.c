#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

//declare struct format
struct countries 
{
	char *country;
	char *runnerFirst;
	char *runnerLast;
	int bib;
};

//fork process
void forkProcess(int random, char country[], char last[]) {
	//store arguments
	char *theargs[4];
	char loop[1];
	
	//assign arguments to the array
	sprintf(loop, "%d", random);
	theargs[0] = "./runner";
	theargs[1] = loop;
	theargs[2] = last;
	theargs[3] = country;
	//fork processes
	int kidPid = fork();

	//if failed, exit
	if(kidPid < 0) {
		printf("Sorry, failed to fork");
		exit(1);
	}

	//if child, run runner
	if(kidPid == 0) {
		execvp("./runner", theargs);
	}
}

void main(int argc, char *argv[]) {	
	int hundredPID = getpid();
	char asciiHundredPID[100];
	char *command;
	int randNum, wstatus;
	time_t t;
	srand((unsigned) time(&t));

	//declare struct variables
	struct countries US;
	US.country = "United States";
	US.runnerFirst = "Grant"; 
	US.runnerLast = "Holloway";
	US.bib = 2609;
	struct countries RU;
	RU.country = "Russia";
	RU.runnerFirst = "Vladimir"; 
	RU.runnerLast = "Kanaykin";
	RU.bib = 1282;
	struct countries UK;
	UK.country = "United Kingdom";
	UK.runnerFirst = "Mo";
	UK.runnerLast = "Farah";
	UK.bib = 6090;

	//stire countries in an array, used for iteration
	struct countries countries[3];
	countries[0] = US;
	countries[1] = RU;
	countries[2] = UK;

	//check if user inputted correct number of arguments
	if(argc < 4) {
		printf("Sorry, please enter three countries on the command line\n");
		exit(2);	
	}

	//store inputed arguments into inCount array
	char country1[100]="", country2[100]="", country3[100]="";
	strcat(country1, argv[1]);
	strcat(country2, argv[2]);
	strcat(country3, argv[3]);
	char *inCount[3];
	inCount[0] = country1;
	inCount[1] = country2;
	inCount[2] = country3;

	//check if each input matches the countries
	for(int i=0; i < 3; i++) {
		if((strcmp(inCount[i], countries[0].country) != 0) && (strcmp(inCount[i], countries[1].country) != 0) && (strcmp(inCount[i], countries[2].country) != 0)) {
			i++;
			printf("Sorry, input #%d does not match any of the countries racing\n", i);
			exit(2);
		//printf("%s, %s, %s\n", country1, country2, country3);
		}
	}

	//display start of race
	system("clear");
	system("echo On your Marks");
	system("echo Get Set");
	system("echo Go!!!!");
	
	//create grep command
	sprintf(asciiHundredPID, "%d", hundredPID);
	strcpy(command, "ps -ef | grep ");
	strcat(command, asciiHundredPID);
	strcat(command, " | grep -v grep");
	system(command);
	
	//generate random number and fork each race process
	randNum = ((rand() % 4) + 4);
	forkProcess(randNum, "United States", "Holloway");
	randNum = ((rand() % 4) + 4);
	forkProcess(randNum, "Russia", "Kanaykin");
	randNum = ((rand() % 4) + 4);
	forkProcess(randNum, "United Kingdom", "Farah");

	//grep to show child processes are running
	system(command);
	//wait for all 3 processes to finish
	wait(&wstatus);
	wait(&wstatus);
	wait(&wstatus);
	//grep to show only parent
	system(command);
	//display end of race
	system("echo What a great race!!!");
}
	


