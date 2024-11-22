#!/bin/bash

run_wheezy() {
	/bin/chroot $DEBPATH /bin/sh -c ". /root/.bashrc; $1"
	CODE=$?
	if [ $CODE -ne 0 ]; then
		exit $CODE
	fi
}
