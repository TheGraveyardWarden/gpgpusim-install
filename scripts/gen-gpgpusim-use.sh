#!/bin/bash

DEBPATH=$1

echo "\
gpgpusim-rbind; \
chroot $DEBPATH; \
" > ./bin/gpgpusim-use

/bin/chmod +x ./bin/gpgpusim-use
