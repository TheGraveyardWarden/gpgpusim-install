#!/bin/bash

DEBPATH=$1
GCCPATH=$2

. ./scripts/run_wheezy.sh

WD=/root/build-gcc

/bin/mkdir $DEBPATH/$WD
/bin/cp $GCCPATH $DEBPATH/$WD/gcc-5.debs.tar
run_wheezy "/bin/tar -C $WD -xvf $WD/gcc-5.debs.tar"
run_wheezy "/usr/bin/dpkg -P --force-all gcc-4.7-base"
run_wheezy "DEBIAN_FRONTEND=noninteractive /usr/bin/dpkg --force-confdef -i $WD/gcc-5.debs/*.deb"
run_wheezy "DEBIAN_FRONTEND=noninteractive /usr/bin/dpkg --force-confdef -i $WD/gcc-5.debs/g++-5.debs/*.deb"
run_wheezy "/bin/ln -s /usr/bin/gcc-5 /usr/bin/gcc"
run_wheezy "/bin/ln -s /usr/bin/g++-5 /usr/bin/g++"
run_wheezy "/bin/ln -s /usr/bin/gcc /bin/gcc"
run_wheezy "/bin/ln -s /usr/bin/g++ /bin/g++"
run_wheezy '/bin/echo "export LD_PRELOAD=/lib/x86_64-linux-gnu/libc-2.18.so" >> /root/.bashrc'
/bin/cp ./assets/cpp-dummy.deb ./assets/gcc-dummy.deb ./assets/g++-dummy.deb $DEBPATH/$WD
run_wheezy "DEBIAN_FRONTEND=noninteractive /usr/bin/dpkg --force-confdef -i $WD/cpp-dummy.deb $WD/gcc-dummy.deb $WD/g++-dummy.deb"
run_wheezy "/bin/rm -rfv $WD"
