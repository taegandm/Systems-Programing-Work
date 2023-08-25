#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <ctype.h>
#include <time.h>

//file variables
int fd1; 
FILE *transcript;

//strings to accept input, file name, and permission change command
char str1[100], str2[100], fname[50]="", permission[50]; 

//create fifo address
char *myfifo="/tmp/fifo";

//responses for sleep function
char *replies[3] = {"Yup\n", "uh-huh...\n", "Absolutely, I totally agree!!\n"};
int replycount = 0, leave = 0, cont = 0, endSleep = 0;

//current time for file
time_t now;
struct tm tstart;
struct tm tend;

//auto answers with set replies
void sleepMode ()
{
	while(1) {
		//read response
        	fd1 = open(myfifo, O_RDONLY); 
        	read(fd1, str1, 80); 
		 
        	// Print the read string and close 
        	printf("Coworker: %s\n", str1); 
        	close(fd1); 

		//if user just wrote, end sleepMode loop
		if(endSleep) {
			endSleep = 0;
			break;
		}
		
		//if other user exits, exit by comparing te
		char *end = "exit\n";
		for(int i = 0; i < 5; i++) {
			if(tolower(str1[i]) !=  end[i]) 
			{
				break;
			}
			if(i == 4) 
			{
				//get current time
				now = time(NULL);
				tend = *localtime(&now);

				//write end time into file
				transcript = fopen(fname, "a");
				fprintf(transcript, "%d/%d/%d %02d:%02d:%02d\n",tend.tm_mon+1, tend.tm_mday, tend.tm_year + 1900, tend.tm_hour, tend.tm_min, tend.tm_sec);
				fclose(transcript);

				//change file permission
				system(permission);	
				exit(1);
			}
		}

		//check if user inputs some form of "hello"
		//compare input to hello
		end = "hello";
		for(int i = 0; i < 5; i++) {
			if(tolower(str1[i]) !=  end[i]) 
			{
				break;
			}
			if(i == 4) 
			{
				//if 'hello', leave sleepMode loop and play bell tone 5 times
				leave = 1;
				
				//this loop won't play the bell unless the text is included, I am not sure why
				for(int count=0;count<5;count++)
  				{
  					printf("\a");
					printf("ALERT: COWORKER SUSPICIOUS\n");
					sleep(1);
				}
			}
		}
		//if 'hello', leave loop
		if(leave) {
			leave = 0;
			break;
		}
 		
		//check if other user is in sleepMode
		for(int i = 0; i < 3; i++) {
			//if the responses match, continue to avoid infinite looop
			if(strcmp(str1, replies[i]) == 0) {
				cont = 1;
			}
		}
		
		//continue to avoid infinite loop
		if(cont) {
			cont = 0;
			continue;
		}
			
		//send out response
		transcript = fopen(fname, "a");
		fd1 = open(myfifo,O_WRONLY);
        write(fd1, replies[replycount], strlen(replies[replycount])+1); 
		fprintf(transcript, "Coworker: %s\n", replies[replycount]);
		fclose(transcript);
        close(fd1);

		//increment response to send
		replycount++;
		if(replycount == 3) {
		replycount = 0;
		}
	}
}

//allow user to send a message
void writeMode () 
{
	//open file
	transcript = fopen(fname, "a");

	//open fifo for writing
    fd1 = open(myfifo,O_WRONLY);

	//accept and write string	
    fgets(str2, 80, stdin);
    write(fd1, str2, strlen(str2)+1);

	//write input to file and close file	
	fprintf(transcript, "Coworker: %s\n", str2);
	fclose(transcript);
    close(fd1);

	//check if exit string
	char *end = "exit\n";
	for(int i = 0; i < 5; i++) {
		if(tolower(str2[i]) !=  end[i]) 
		{
			break;
		}
		if(i == 4) 
		{	
			exit(1);
		}
		
	//store that this user just wrote
	endSleep = 1;
	}
}


//consistantly read reponses until user enters write or sleep mode
int main(int argc, char *argv[]) 
{
	//check to see if user entered a file name
	if(argc < 2) {
		printf("Please add a file on the command line\n");
		exit(1);
	}

	//open file, write current time, close file
	now = time(NULL);
	tstart = *localtime(&now);
	
	strcat(fname, argv[1]);
	transcript = fopen(fname, "w");
	fprintf(transcript, "%d/%d/%d %02d:%02d:%02d\n", tstart.tm_mon + 1, tstart.tm_mday, tstart.tm_year + 1900, tstart.tm_hour, tstart.tm_min, tstart.tm_sec);
	fclose(transcript);

	//create permission command
	strcat(permission, "chmod 400 ");
	strcat(permission, fname);

	//make fifo and redirect signals
	mkfifo(myfifo, 0666); 
	signal(SIGINT, writeMode );
    signal(SIGTSTP, sleepMode );
	
	//read answers until user enters write or sleep mode
    	while (1) 
    	{
		//store that user just read
		endSleep = 0;

		//access fifo and wait for input
        	fd1 = open(myfifo, O_RDONLY); 
        	read(fd1, str1, 80);

		//if reading exit string, exit
		char *end = "exit";
		for(int i = 0; i < 4; i++) {
			if(tolower(str1[i]) != end[i]) 
			{
				break;
			}
			if(i == 3) 
			{
				//write end time in file
				now = time(NULL);
				tend = *localtime(&now);
				transcript = fopen(fname, "a");
				fprintf(transcript, "%d/%d/%d %02d:%02d:%02d\n",tend.tm_mon+1, tend.tm_mday, tend.tm_year + 1900, tend.tm_hour, tend.tm_min, tend.tm_sec);
				fclose(transcript);

				//change file permission
				system(permission);	
				exit(1);
			}
		}
  
        	// Print the read string and close 
        	printf("Coworker: %s\n", str1); 
        	close(fd1); 
    	}
    	return 0; 
} 
