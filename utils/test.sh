#!/bin/bash

BINMIN=$3
BINMAX=$4
INPUT=$1
RUNNUMBER=$2


source $(dirname $0)/directories.sh

STARTDATE_S=$(date +%s%N)
STARTDATE_L=$(date)


SEVENT=$(sed '9q;d' $INPUTFOLDER/$INPUT | awk '{print $1}')
NEVENT=$(($SEVENT * ($BINMAX-$BINMIN+1)))

printf "╭────────────────────────────────────────────────────────────────────────╮\n"
printf "│ %-70s │\n" "AMPT Multiprocesser"                                        
printf "│ %-70s │\n" "Version 3.0"           
printf "│ %-70s │\n" "Made by Lieuwe Huisman"
printf "├────────────────────────────────────────────────────────────────────────┤\n"
printf "│ Bin Directory    : %-51s │\n" $BINFOLDER
printf "│ Input Directory  : %-51s │\n" $INPUTFOLDER
printf "│ Output Directory : %-51s │\n" $DATAFOLDER
printf "│ Used Bins        : %03d to %03d %-40s │\n" $BINMIN $BINMAX " "
printf "│ Used CPU Count   : %03d %-48s│\n" $(($BINMAX-$BINMIN+1)) " "
printf "│ Number of Events : %-51s │\n" "$NEVENT"
printf "│ Starting Time    : %-51s │\n" "$STARTDATE_L"
printf "╰────────────────────────────────────────────────────────────────────────╯\n"



ENDDATE_S=$(date +%s%N)

ENDDATE_L=$(date)

DURATION=$((($ENDDATE_S-$STARTDATE_S)/1000000))
DURATION_EVENT=$(($DURATION/$NEVENT))

source $(dirname $0)/timer.sh
DURATION_STR=$(printduration $DURATION)
DURATION_STR_EVENT=$(printduration $DURATION_EVENT)

tput bel
printf "╭────────────────────────────────────────────────────────────────────────╮\n"
printf "│ Ending Time      : %-51s │\n" "$ENDDATE_L"
printf "│ Elapsed Time     : %-51s │\n" "$DURATION_STR"     
printf "│ Time per event   : %-51s │\n" "$DURATION_STR_EVENT"     
printf "╰────────────────────────────────────────────────────────────────────────╯\n"