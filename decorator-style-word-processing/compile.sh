#!/bin/bash
# Use this script to compile your .cc files in dependency order, with ./compile < order.txt exec

# Arguments:
#   $1 = name of file containing list of .cc files
#   $2 = name of the output file

cxx="g++-14.2.0"
cxxflags="-std=c++20 -fmodules-ts -Wall -g"

if [ $# -lt 1 ]; then
  echo "Usage:  $0 list-filename [output-name]" 1>&2
  exit 1
fi

if [ $# -eq 2 ]; then
  name="-o $2"
fi

for x in $(cat $1); do
  $cxx $cxxflags -c $x
done

$cxx *.o $name

