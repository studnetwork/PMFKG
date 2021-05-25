#!/bin/bash

if [[ $# < 2 ]]
then
    echo Potrebno je proslediti minimalno 2 argumenta
    exit 1
fi

direktorijumi=$(find "$1" -mindepth 1 -maxdepth 1 -type d )
args=("${@}")

# indeksi od 1 do $#-1
sekvenca=$(seq 1 $(expr $# - 1) )

#prvi deo
for direktorijum in $direktorijumi
do
    for i in $sekvenca
    do
        cp "${args[$i]}" "$direktorijum"
        echo "Prekopiran ${args[$i]} u $direktorijum"
    done
done

direktorijumi=$(find "$1" -mindepth 1 -type d )

#drugi deo
for direktorijum in $direktorijumi
do
    for i in $sekvenca
    do
        cp "${args[$i]}" "$direktorijum"
        echo "Prekopiran ${args[$i]} u $direktorijum"
    done
done

# dodatno
for direktorijum in $direktorijumi
do
    cd "$direktorijum"
    fajlovi=$(find . -mindepth 1 -maxdepth 1  -type f)
    text=""
    for fajl in $fajlovi
    do
        cat $fajl | grep -E "^[a-zA-Z0-9]{5,15}@[a-z]{3,10}$" > _tempfile
        rm "$fajl"
        mv _tempfile "$fajl"
    done
    
    if [[ "$text" != "" ]]
    then
        echo -e $text
    fi
    
    cd "$OLDPWD"
done
