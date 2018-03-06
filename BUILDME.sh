#!/bin/bash
if [ ! -d "lib" ]; then
   mkdir -p lib
   cd lib
   if [ ! -d "libpf" ]; then
      echo "Cloning libPF ..."
      git clone https://jonapoul@bitbucket.org:eric_tittley/libpf.git
      cd libpf
      rm -rf test
      rm -f Makefile
      cd ..
      echo "done!"
   fi
   cd ..
fi

echo "Updating libPF ..."
cd lib/libpf
git pull
cd ../..
echo "done!"

qmake
make