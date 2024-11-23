#!/bin/bash

DEBPATH=$1

. ./scripts/run_wheezy.sh

/bin/cp ./gpgpusim $DEBPATH/root -rfv
run_wheezy "apt-get install -f"
run_wheezy "apt-get install -y --force-yes build-essential xutils-dev bison zlib1g-dev flex libglu1-mesa-dev doxygen graphviz libxi-dev libxmu-dev git vim"
run_wheezy "cd /root/gpgpusim; . ./setup_environment; make -j$(nproc)"
/bin/cat ./assets/gpgpusim_bashrc.dat >> $DEBPATH/root/.bashrc
