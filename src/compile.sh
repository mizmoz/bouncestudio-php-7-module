#!/bin/bash

make clean

phpize7.1

./configure --enable-bouncestudio

make CFLAGS="-lBounceStudio64 $CFLAGS"

make install
