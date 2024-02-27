MIN=$1
MAX=$2
SRC_DIR=$3

for i in $(seq $1 $2)
do
    rm -f bin/ampt_$i/*.f
    rm -f bin/ampt_$i/*.o
    rm -f bin/ampt_$i/ampt
    cp -a src/$SRC_DIR/. bin/ampt_$i
    cd bin/ampt_$i
    make > /dev/null 2>&1 &
    cd ../..

done
wait
echo "Compiling done"
