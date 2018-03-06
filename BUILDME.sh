#!/bin/bash
if [ ! -d "lib" ]; then
   mkdir -p lib
fi
if [ ! -d "lib/libPF" ]; then
   cd lib
   git clone git@bitbucket.org:eric_tittley/libpf.git
   mv libpf libPF
   cd libPF
   rm -rf test
   rm -f Makefile
   cd ../..
else
   echo "Updating libPF ..."
   cd lib/libPF
   git pull
   cd ../..
   echo "done!"
fi

qmake
make