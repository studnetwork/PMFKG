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

sorted=$(find "$1" -maxdepth 1 -type f -name "*.$ext" | sort -d )

echo "$sorted" | head -2 | while read file; do
	awk '!/^-?[0-9]+\.[0-9]+.*[0-9]+\.[0-9]+$/' "$file" >> "$2"
done

echo "$sorted" | tail -2 | while read file; do
	awk '!/^-?[0-9]+\.[0-9]+.*[0-9]+\.[0-9]+$/' "$file" >> "$2"
done
