#!/bin/bash

#get start time in seconds and nanoseconds
let startTime=$(date +%s%N)

#define epoch time and ask if the user knows their birthday in epoch time
echo Epoch time is the current amount of seconds elapsed since January 1st, 1970, at 00:00:00 UTC. It is a consistant measurement used by computers to keep track of and calculate time.
echo
echo Do you know your birthday in epoch time?

#loop case until user responds with an accepted string
let finished=0;
while [ "$finished" = 0 ]; do
    read ans
    case $ans in
	
	y | Y | yes | Yes )
	    #prompt user for birthday in epoch time
	    echo
	    echo Great! Enter your birthday in epoch time: 
	    read birthEpoch
	    #convert epoch time to date and exit case loop
	    birthDate=$( date -d "@$birthEpoch" +"%m/%d/%Y" -u )
	    finished=1;;

	n | N | no | No )
	    #prompt user for birth date
	    echo
	    echo That\'s alright, enter your birthday in mm/dd/yyyy format: 
	    read birthDate
	    #convert birthdate to epoch time and exit case loop
	    birthEpoch=$( date -d "$birthDate" +"%s" -u )
	    finished=1;;

	* )
	    #ask user to input an acceptable response, then repeat case loop
	    echo Please enter y, n, Y, N, yes, no, Yes, or No;;
    esac
done

#get each necessary variable individually in UTC
year=$( date -d "$birthDate" +"%Y" -u )
month=$( date -d "$birthDate" +"%B" -u )
day=$( date -d "$birthDate" +"%d" -u )
dayOfWeek=$( date -d "$birthDate" +"%A" -u )
dayOfYear=$( date -d "$birthDate" +"%j" -u )
birthEpochStart=$( date -d "$birthDate 00:00:00" +"%s" -u )
birthEpochEnd=$( date -d "$birthDate 23:59:59" +"%s" -u )

#print results in desired format
echo
printf "The date you entered, %s %d, %d, was a %s and was the %dth day of the year...depending on the time, the epoch date was between %d and %d\n\n" "$month" "$day" "$year" "$dayOfWeek" "$dayOfYear" "$birthEpochStart" "$birthEpochEnd"

#get end time in seconds and nanoseconds
let endTime=$(date +%s%N)

#get total time and convert to seconds and nanoseconds individually
let totalTime=$endTime-$startTime
let totalSec=$((totalTime / 1000000000))
let totalNano=$((totalTime % 1000000000))

#display total process time
echo This application took $totalSec.$totalNano seconds
