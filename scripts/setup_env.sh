#!/usr/bin/bash

DEBPATH=$1

if [ -f /tmp/gpgpusim_rbind ]; then
	echo "already rbind!"
else
	/bin/mount --rbind /sys $DEBPATH/sys
	/bin/mount --rbind /proc $DEBPATH/proc
	/bin/mount --rbind /dev $DEBPATH/dev
	/bin/mount --rbind /run $DEBPATH/run
	/bin/echo "do not rm me" > /tmp/gpgpusim_rbind
fi

/bin/ln -s $DEBPATH/bin/bash $DEBPATH/usr/bin/bash
/bin/cat ./assets/bashrc.dat >> $DEBPATH/root/.bashrc