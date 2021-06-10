#!/bin/bash

if [ $# -ne 3 ]; then
	echo 'Potrebno je uneti tacno tri parametra'
	exit 1
fi

if ! [ -d "$1" ]; then
	echo 'Neispravna putanja do direktorijuma'
	exit 2
fi

prvi=$(echo "$2" | grep -E "^[0-7]{3,4}$" | wc -l)
drugi=$(echo "$3" | grep -E "^[0-7]{3,4}$" | wc -l)

if [ $prvi -eq 0 ]; then
	echo 'Dozvola 1 nije trocifren/cetvorocifren broj sacinjen od cifara [0-7]'
	exit 3
fi

if [ $drugi -eq 0 ]; then
	echo 'Dozvola 2 nije trocifren/cetvorocifren broj sacinjen od cifara [0-7]'
	exit 4
fi

find "$1" -type f -exec chmod $2 '{}' \;
find "$1" -type d -exec chmod $3 '{}' \;
