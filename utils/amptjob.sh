#!/bin/bash

INPUT=$1
RUNNUMBER=$2
BINMIN=$3
BINMAX=$4

source $(dirname $0)/directories.sh
source $(dirname $0)/timer.sh

STARTDATE_S=$(cdate +%s%N)
STARTDATE_L=$(cdate)

SEVENT=$(sed '9q;d' $INPUTFOLDER/$INPUT | awk '{print $1}')
NEVENT=$(($SEVENT * ($BINMAX-$BINMIN+1)))

printf "╭────────────────────────────────────────────────────────────────────────╮\n"
printf "│ %-70s │\n" "AMPT Multiprocesser"                                        
printf "│ %-70s │\n" "Version 3.0.0"           
printf "│ %-70s │\n" "Made by Lieuwe Huisman"
printf "├────────────────────────────────────────────────────────────────────────┤\n"
printf "│ Bin Directory    : %-51s │\n" $BINFOLDER
printf "│ Input Directory  : %-51s │\n" $INPUTFOLDER
printf "│ Output Directory : %-51s │\n" $DATAFOLDER
printf "│ Used Bins        : %03d to %03d %-40s │\n" $BINMIN $BINMAX " "
printf "│ Used CPU Count   : %03d %-48s│\n" $(($BINMAX-$BINMIN+1)) " "
printf "│ Number of Events : %-51s │\n" "$NEVENT"
printf "│ Starting Time    : %-51s │\n" "$STARTDATE_L"
printf "├────────────────────────────────────────────────────────────────────────┤\n"


rm -rf $DATAFOLDER/$RUNNUMBER
mkdir -p $DATAFOLDER/$RUNNUMBER


for BINID in $(seq $BINMIN $BINMAX)
do
    I=$(($BINID - $BINMIN + 1))
    rm -rf "$BINFOLDER/ampt_$BINID/ana"
    rm -rf "$BINFOLDER/ampt_$BINID/ana1"
    mkdir -p "$DATAFOLDER/$RUNNUMBER/$RUNNUMBER""_""$I"
    cp "$INPUTFOLDER/$INPUT" "$DATAFOLDER/$RUNNUMBER/$RUNNUMBER""_""$I/input.par"
    cp "$INPUTFOLDER/$INPUT" "$BINFOLDER/ampt_$BINID/input.ampt"
    bash "$UTILSFOLDER/amptsinglejob.sh" $I $BINID $MAINFOLDER $BINFOLDER $RUNNUMBER &
done
wait
for BINID in $(seq $BINMIN $BINMAX)
do
    I=$(($BINID - $BINMIN + 1))
    mv "$BINFOLDER/ampt_$BINID/ana" "$DATAFOLDER/$RUNNUMBER/$RUNNUMBER""_""$I/"
    mv "$BINFOLDER/ampt_$BINID/ana1" "$DATAFOLDER/$RUNNUMBER/$RUNNUMBER""_""$I/"
    mv $BINFOLDER/ampt_$BINID/*.time "$DATAFOLDER/$RUNNUMBER/$RUNNUMBER""_""$I/"
    mv $BINFOLDER/ampt_$BINID/*.log "$DATAFOLDER/$RUNNUMBER/$RUNNUMBER""_""$I/"
    mv $BINFOLDER/ampt_$BINID/*.err "$DATAFOLDER/$RUNNUMBER/$RUNNUMBER""_""$I/"
done

ENDDATE_S=$(cdate +%s%N)
ENDDATE_L=$(cdate)

DURATION=$(( ($ENDDATE_S-$STARTDATE_S)/1000000))
DURATION_EVENT=$(($DURATION/$NEVENT))


DURATION_STR=$(printduration $DURATION)
DURATION_STR_EVENT=$(printduration $DURATION_EVENT)
printf "%s | %s | %s | %s" "$STARTDATE_L" "$ENDDATE_L" "$DURATION_STR" "$DURATION_STR_EVENT" > "$DATAFOLDER/$RUNNUMBER/$RUNNUMBER.time"

printf "├────────────────────────────────────────────────────────────────────────┤\n"
printf "│ Ending Time      : %-51s │\n" "$ENDDATE_L"
printf "│ Elapsed Time     : %-51s │\n" "$DURATION_STR"     
printf "│ Time per event   : %-51s │\n" "$DURATION_STR_EVENT"     
printf "╰────────────────────────────────────────────────────────────────────────╯\n"

# tput bel