#!/bin/bash

if [ $# -ne 2 ]; then
	echo 'Potrebno je uneti tacno 2 putanje'
	exit 1
fi

if ! [ -d "$1" ]; then
	echo 'Putanja do direktorijuma nije ispravna'
	exit 2
fi

if ! [ -f "$2" ]; then
	echo 'Putanja do fajla nije ispravna'
	exit 3
fi

ext='txt'

files=$(find "$1" -maxdepth 1 -type f -name "*.$ext" )

echo "$files" | head -2 | while read file; do
    file=$(sort -d "$file")
	awk '!/^-?[0-9]+\.[0-9]+.*[0-9]+\.[0-9]+$/' "$file" >> "$2"
done

echo "$files" | tail -2 | while read file; do
    file=$(sort -d "$file")
	awk '!/^-?[0-9]+\.[0-9]+.*[0-9]+\.[0-9]+$/' "$file" >> "$2"
done
