#!/usr/bin/bash

DEBPATH=$1

/bin/ln -s /bin/bash $DEBPATH/usr/bin/bash
/bin/cat ./assets/bashrc.dat >> $DEBPATH/root/.bashrc
