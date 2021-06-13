#!/bin/bash

if [[ $# < 2 ]]
then
    echo 'Potrebno je uneti najmanje 2 argumenta'
    exit 1
fi

if ![ -d "$1" ]
then
    echo "Putanja do direktorijuma $1 nije ispravna"
    exit 1
fi


if ![ -d "$2" ]  
then 
    mkdir "$2"
fi

granica=$(expr 4096 \* 1000)

#manji_fajlovi=$(find . -type f -size -4096KB -exec cp {} "$2/" \;)
#veci_fajlovi=$(find . -type f -size +4096KB -exec cp {} "$2/" \; &)

fajlovi=$(find . -type f)

echo "$fajlovi" | while read file
do
    size=$(ls -l "$file" | awk '{ print $5 }')
    if [ $size -gt $granica ]
    then
        cp "$file" "$2" &
    else
        cp "$file" "$2"
    fi
    
done

if ![ -d "$2"/Archived ]  
then
    mkdir "$2"/Archived
else
    rm -r "$2"/Archived/*
fi

find "$2" -mtime +365 -type f -exec mv '{}' "$2"/Archived

#godina=$(ls -l "$file" | awk 'NR != 1 && $8 !~ /[0-9]+:[0-9]+/ { print $8 }')
