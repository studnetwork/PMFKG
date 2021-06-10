#!/bin/bash

if [ $# -le 2 ]; then
	echo 'Potrebno je proslediti minimalno 2 parametra'
	exit 1
fi

if ! [ -d "$1" ]; then
	echo 'Neispravna putanja do direktorijuma'
	exit 2
fi

main_dir="$1"

shift

# a)
# find "$main_dir" -maxdepth 1 -type d | while read dir
find "$main_dir" -type d | while read dir              # b)
do
	for file in "$@"
	do
		bname=$(basename "$file")
		grep -E "[a-zA-Z0-9]{5,15}@[a-z]{3,10}" "$file" >> "$dir"/"$bname"
	done	
done
