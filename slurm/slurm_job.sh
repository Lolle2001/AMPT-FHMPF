#!/bin/bash
INPUT=$1 # Name of input file
RUNNUMBER=$2 # Number given to job
BINMIN=$3 # Minimum bin number in which job is ran
BINMAX=$4 # Maximum bin number in which job is ran

# This file defines the directories in which
# the executables are located, where the inputs are stored
# and where the data is stored.
source $(dirname $0)/directories.sh
# This file has some user functions to give some 
# information on the duration of a job. Jobs are ran
# on a linus laptop and mac server, which have 
# different ways of measuring time.
source $(dirname $0)/timer.sh

STARTDATE_S=$(cdate +%s%N)
STARTDATE_L=$(cdate)

SEVENT=$(sed '9q;d' $INPUTFOLDER/$INPUT | awk '{print $1}') # Number of events in a single bin
NEVENT=$(($SEVENT * ($BINMAX-$BINMIN+1))) # Total number of events

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


# If there is a data folder with the same name as the runnumber,
# it will be deleted and recreated. This is done to make sure
# that there is no error in the data.
rm -rf $DATAFOLDER/$RUNNUMBER
mkdir -p $DATAFOLDER/$RUNNUMBER

# In this for loop the jobs are ran. The jobs are ran in parallel,
# so that the time needed for the jobs is minimized. It first removes
# any old data in the bin directories and creates subfolders in the 
# data directory. It copies the input file to the bin directories and
# then runs the job. The jobs are ran in the background, so that
# the script can continue.
for BINID in $(seq $BINMIN $BINMAX)
do
    I=$(($BINID - $BINMIN + 1))
    rm -rf "$BINFOLDER/ampt_$BINID/ana"
    rm -rf "$BINFOLDER/ampt_$BINID/ana1"
    mkdir -p "$DATAFOLDER/$RUNNUMBER/$RUNNUMBER""_""$I"
    # cp "$INPUTFOLDER/$INPUT" "$DATAFOLDER/$RUNNUMBER/$RUNNUMBER""_""$I/input.par"
    cp "$INPUTFOLDER/$INPUT" "$BINFOLDER/ampt_$BINID/input.ampt"
    # The amptsinglejob.sh runs one single bin. It allows for timing a single bin,
    # and makes sure a random seed is used for the ZPC. It also takes into account
    # that shell script works a bit different on a mac server.
    bash "$UTILSFOLDER/amptsinglejob.sh" $I $BINID $RUNNUMBER | batch
    # The sleep command makes sure that the jobs are starting with different HIJING seeds.
    sleep 1
done
# Before any copying is done, all jobs must be finished. Otherwise there will be clogging
# and the multiprocessing will not work properly.
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
