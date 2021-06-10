#!/bin/bash

if [ $# -ne 2 ]; then
	echo 'Skripta prima tacno 2 argumenta'
	exit 1
fi

if ! [ -d "$1" ]; then
	echo 'Prvi argument nije ispravna putanja do direktorijuma'
	exit 2
fi

if ! [ -d "$2" ]; then
	mkdir "$2"
else
	if [ -d $2/mali ]; then
		rm -r "$2"/mali
	fi

	if [ -d "$2"/srednji ]; then
		rm -r "$2"/srednji
	fi
	
	if [ -d "$2"/veliki ]; then
		rm -r "$2"/veliki
	fi
fi

mkdir "$2"/{mali,srednji,veliki}

#find "$1" -maxdepth 2 -type f -size -100kB -exec cp '{}' "$2"/mali  \;

find "$1" -maxdepth 2 -type f | while read file; do
	size=$(ls -l "$file" | awk '{ print $5 }')
	
	if [ "$size" -lt 100000 ]; then
		cp "$file" "$2"/mali
	elif [ "$size" -lt 1000000 ]; then
		cp "$file" "$2"/srednji
	else
		cp "$file" "$2"/veliki
	fi
done
