#!/bin/bash

file=`echo $1 | awk 'BEGIN{FS="."; OFS=""} {print $NF}'`
path=${1//\./\/}
jpath=$1
echo $path

cd src
javac -d ../bin $path.java

cd ../bin
java $jpath
