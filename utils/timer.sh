#!/bin/bash
printduration(){
    # IN MILLISECONDS
    DURATION=$1
    HOURS=$(( $DURATION/3600000 ))
    PHOURS=$(( $HOURS * 3600000 ))
    MINUTES=$(( ($DURATION-$PHOURS)/60000 ))
    PMINUTES=$(( $MINUTES*60000 ))
    SECONDS=$(( ($DURATION-$PHOURS-$PMINUTES)/1000 ))
    PSECONDS=$(( ($SECONDS*1000)))
    MILLISECONDS=$((($DURATION-$PHOURS-$PMINUTES-$PSECONDS)))
    STR=$(printf "%04d:%02d:%02d.%03d" $HOURS $MINUTES $SECONDS $MILLISECONDS)
    echo $STR
}

cdate(){
    if [ "$(uname)" = "Darwin" ]; then
        gdate $1
    else
        date $1
    fi
}



# DURATION_STR=$(date -d @${DURATION} +"%d-%m-%Y %H:%M:%S.%3N")
# DURATION_STR_EVENT=$(date -d @${DURATION_EVENT} +"%d-%m-%Y %H:%M:%S.%3N")