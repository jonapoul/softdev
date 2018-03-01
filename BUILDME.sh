#!/bin/bash
if [ ! -d "lib" ]; then
   mkdir -p lib
   cd lib
   if [ ! -d "libpf" ]; then
      git clone https://jonapoul@bitbucket.org:eric_tittley/libpf.git
      cd libpf
      rm -rf test
      rm -f Makefile
      cd ..
   fi
   if [ ! -d "matplotlib-cpp" ]; then
      git clone https://github.com/lava/matplotlib-cpp.git
      cd matplotlib-cpp
      rm -rf examples
      rm -f Makefile
      cd ..
   fi
   cd ..
fi
qmake
make