#!/bin/bash

# ./zadatak.sh ext Dir1 Dir2 ... DirN

if [[ $# -lt 2 ]]
then
    echo "premali broj argumenata"
    exit -1
fi

dirs=$@
ext=$1

i=0
for dir in $dirs
do
    if [[ $i -gt 0 ]]
    then
        fs=$(find $dir | grep -E ".*\.$ext$")
        for f in $fs
        do
            t=$(echo $f | awk 'BEGIN{FS="/"} {print $NF}')
            cp $f ./$t
        done
    fi
    let i++
done

fs=$(ls -l ./ | grep -E ".*\.$ext$" | awk 'BEGIN{FS=" "} {print $NF}')
for f in $fs
do
    cp $f $f.clone
    cat $f.clone | grep -E "^[A-Z].*\.$" > $f
    rm ./*.clone
done

# drugi deo

mkdir kopije

i=0
for dir in $dirs
do
    if [[ $i -gt 0 ]]
    then
        cp -r $dir ./kopije/$dir
    fi
    let i++
done

fs=$(find ./kopije | grep -E "\.$ext$")
for f in $fs
do
    rm $f
done

fs=$(find ./kopije -type f)
for f in $fs
do
    ln -s $f $f.ln
done