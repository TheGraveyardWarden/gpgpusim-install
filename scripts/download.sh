#!/bin/bash

# download $1 if $2 doesnt exist

wget $1 -O $2 -c

exit $?
