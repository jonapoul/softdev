#!/bin/bash
./BUILDME.sh && valgrind --leak-check=full --track-origins=yes bin/softdev
