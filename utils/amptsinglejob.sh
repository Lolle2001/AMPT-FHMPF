I=$1
BINID=$2
MAINFOLDER=$3
BINFOLDER=$4
RUNNUMBER=$5
source $(dirname $0)/timer.sh
cd "$BINFOLDER/ampt_$BINID"

mkdir -p "ana"
mkdir -p "ana1"

STARTDATE_S=$(cdate +%s%N)
STARTDATE_L=$(cdate)

printf "│ Job %02d started at  : %-49s │\n" $I "$STARTDATE_L"
cp input.ampt ana/
nrandom=$(date '+%d%H%M%S')



echo $nrandom > nseed

./ampt < nseed 1> "$RUNNUMBER""_""$I.log" 2> "$RUNNUMBER""_""$I.err"

ENDDATE_S=$(cdate +%s%N)
ENDDATE_L=$(cdate)

# tput bel
# sleep 1 
# tput bel

DURATION=$(( ($ENDDATE_S-$STARTDATE_S)/1000000))

DURATION_STR=$(printduration $DURATION)

printf "│ Job %02d finished at : %-49s │\n" $I "$ENDDATE_L"
printf "│ Job %02d finished in : %-49s │\n" $I "$DURATION_STR"

BIN_STR=$(printf "%03d" $BINNUMBER)

printf "%s | %s | %s | %s\n" "$BIN_STR" "$STARTDATE_L" "$ENDDATE_L" "$DURATION_STR" > "$RUNNUMBER""_""$I.time"
cd "$MAINFOLDER"
