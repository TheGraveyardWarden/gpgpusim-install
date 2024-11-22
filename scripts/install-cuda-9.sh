#!/bin/bash

DEBPATH=$1
CUDAPATH=$2
WD=/root/install-cuda

. ./scripts/run_wheezy.sh

/bin/mkdir $DEBPATH/$WD
/bin/cp $CUDAPATH $DEBPATH/$WD/cuda.run
run_wheezy "apt-get install -y --force-yes cpanminus make"
run_wheezy "cpanm Tie::File"
run_wheezy "/bin/chmod +x $WD/cuda.run"
run_wheezy "$WD/cuda.run"
/bin/cat ./assets/cuda_9_bashrc.dat >> $DEBPATH/root/.bashrc
