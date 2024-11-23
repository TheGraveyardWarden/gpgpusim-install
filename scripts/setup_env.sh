#!/usr/bin/bash

DEBPATH=$1

/bin/ln -s $DEBPATH/bin/bash $DEBPATH/usr/bin/bash
/bin/cat ./assets/bashrc.dat >> $DEBPATH/root/.bashrc
