#!/bin/bash
#./BUILDME.sh && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes bin/softdev
./BUILDME.sh && valgrind --leak-check=full --track-origins=yes bin/softdev
