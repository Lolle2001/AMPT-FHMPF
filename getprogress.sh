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

STRING="$(ProgressBar $TOTAL $NEVENT)"
NUM="TOTAL"
NUM2=$(printf "%5d" $TOTAL)
echo "$NUM : $NUM2 : $STRING"



