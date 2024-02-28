MIN=$1
MAX=$2
SRC_DIR=$3

source $(dirname $0)/timer.sh

printf "│ Creating Bins at : %-51s │\n" "$(cdate)"
for i in $(seq $1 $2)
do
    rm -rf bin/ampt_$i
    mkdir -p bin/ampt_$i
    cp -a src/$SRC_DIR/. bin/ampt_$i
    cd bin/ampt_$i
    make 1> make.log 2> make.err &
    cd ../..
done
wait
printf "│ All bins created and compiled at : %-35s │\n" "$(cdate)"

