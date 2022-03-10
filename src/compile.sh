#!/bin/bash

make clean

phpize

./configure --enable-bouncestudio

make CFLAGS="-lBounceStudio64 $CFLAGS"

make install
