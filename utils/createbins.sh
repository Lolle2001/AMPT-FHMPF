MIN=$1
MAX=$2
SRC_DIR=$3
echo "[AMPT] Creating Bins"
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
echo "[AMPT] All bins created and compiled"
