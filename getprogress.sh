#!/bin/bash

function ProgressBar {
# Process data
    let _progress=(${1}*100/${2}*100)/100
    let _done=(${_progress}*4)/10
    let _left=40-$_done
# Build progressbar string lengths
    _fill=$(printf "%${_done}s")
    _empty=$(printf "%${_left}s")

# 1.2 Build progressbar strings and print the ProgressBar line
# 1.2.1 Output example:                           
# 1.2.1.1 Progress : [########################################] 100%
    printf "[${_fill// /#}${_empty// /-}] ${_progress}%%"

}

NEVENT=$(grep "Number of Events" "$1.log" | awk '{print $6}')
SUBNEVENT=$(( $NEVENT / ($3 - $2 + 1) ))
echo "Number of Events       : $NEVENT"
echo "Number of Events (bin) : $SUBNEVENT"
TOTAL=0
for i in $(seq $2 $3)
do
    CEVENT=$(grep "EVENT" bin/ampt_${i}/${1}_$i.log | tail -1 | awk '{print $2}')
    STRING="$(ProgressBar $CEVENT $SUBNEVENT)"
    NUM=$(printf "%03d" $i)
    NUM2=$(printf "%5d" $CEVENT)
    echo "  $NUM : $NUM2 : $STRING"
    # printf "%03d : %s\n" $i $STRING
    TOTAL=$(($TOTAL+$CEVENT))
    
done


date_string=$(grep "Starting Time " $1.log | awk '{print $5,$6,$7,$8,$9,$10}')

day=$(echo "$date_string" | awk '{print $2}')
month=$(echo "$date_string" | awk '{print $3}')
year=$(echo "$date_string" | awk '{print $4}')
time=$(echo "$date_string" | awk '{print $5}')
# echo $day-$month-$year $time
case $month in
    jan) month_num=01;;
    feb) month_num=02;;
    mrt) month_num=03;;
    apr) month_num=04;;
    mei) month_num=05;;
    jun) month_num=06;;
    jul) month_num=07;;
    aug) month_num=08;;
    sep) month_num=09;;
    okt) month_num=10;;
    nov) month_num=11;;
    dec) month_num=12;;
    *) echo "Unknown month abbreviation"; exit 1;;
esac

formatted_date="$year-$month_num-$day $time"
# Rearrange components into a format accepted by date command
date_variable=$(date -d "$formatted_date" +"%s%N")

date_now=$(date +"%s%N")

diff=$(( ($date_now-$date_variable) ))
# echo $diff
slope=$(( $diff / $TOTAL ))
# echo $slope
eventleft=$(($NEVENT - $TOTAL))
# echo $eventleft
timeleft=$(($slope * $eventleft / 1000000))

STRING="$(ProgressBar $TOTAL $NEVENT)"
NUM="TOTAL"
NUM2=$(printf "%5d" $TOTAL)
echo "$NUM : $NUM2 : $STRING"

DURATION=$timeleft
HOURS=$(( $DURATION/3600000 ))
PHOURS=$(( $HOURS * 3600000 ))
MINUTES=$(( ($DURATION-$PHOURS)/60000 ))
PMINUTES=$(( $MINUTES*60000 ))
SECONDS=$(( ($DURATION-$PHOURS-$PMINUTES)/1000 ))
PSECONDS=$(( ($SECONDS*1000)))
MILLISECONDS=$((($DURATION-$PHOURS-$PMINUTES-$PSECONDS)))
STR=$(printf "Time left: %04d:%02d:%02d.%03d" $HOURS $MINUTES $SECONDS $MILLISECONDS)
echo $STR


