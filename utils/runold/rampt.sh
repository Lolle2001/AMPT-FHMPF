#!/bin/bash
source $(dirname $0)/utils/directories.sh

bash utils/amptjob.sh $1 $2 $3 $4 1> "$2.log" 2> "$2.err"
mv *.log "$DATAFOLDER/$2/"
mv *.err "$DATAFOLDER/$2/"