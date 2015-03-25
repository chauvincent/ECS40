#!/bin/bash

# Usage:
# 
# sh ./grade.sh ~/project
#
# where 'project' is the directory containing your source (mscp.cpp etc.)

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 directory" >&2
	echo "       (directory should contain your mscp.cpp etc.)" >& 2
    exit 1
fi

TIMEOUT=60s

rm -f *.o mscp mscp.reference ref.out

gcc -w -c time.c -o time.o
if g++ -Wall -Werror -ansi -Xlinker --wrap=time -I$1 $1/*.cpp time.o -o mscp;
then
	echo "Compile succeeded without warnings"
elif g++ -ansi -Xlinker --wrap=time -I$1 $1/*.cpp time.o -o mscp;
then
	echo "Compile succeeded with warnings"
else
	echo "Compile failed"
    exit 1
fi

gcc -w -c reference.c -o reference.o
gcc -Xlinker --wrap=time reference.o time.o -o mscp.reference
./mscp.reference < input > ref.out

timeout -k $TIMEOUT $TIMEOUT ./mscp < input > out
if cmp -s ref.out out;
then
	echo "Output matches reference (cmp byte-by-byte comparison)"
elif diff -q ref.out out > /dev/null;
then
	echo "Output matches reference (diff comparison)"
elif diff -q -w -i -E -B -t ref.out out > /dev/null;
then
	echo 'Output matches reference ignoring whitespace (diff comparison)'
else
	echo 'Output does NOT match'
	echo "Look at 'out' and 'ref.out' for more information"
fi
