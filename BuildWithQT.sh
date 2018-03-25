#!/bin/bash
if [ ! -d "lib" ]; then
   mkdir -p lib
fi
if [ ! -d "lib/libpf" ]; then
   cd lib
   git clone git@bitbucket.org:eric_tittley/libpf.git
   cd libpf
   cd ../..
else
   echo "Updating libpf ..."
   cd lib/libpf
   git pull
   cd ../..
   echo "done!"
fi

qmake
make -f Qt_Makefile
rm Qt_Makefile