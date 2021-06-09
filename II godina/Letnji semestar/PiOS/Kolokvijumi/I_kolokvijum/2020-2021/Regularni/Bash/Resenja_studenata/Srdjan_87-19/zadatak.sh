#!/bin/bash

if [ $# -lt 2 ]; then
	echo "Potrebno je proslediti ekstenziju i barem jedan direktorijum"
	exit 1
fi

ext=$1

shift

if [ -d "./kopije" ]; then
	rm -r "./kopije"
fi

mkdir kopije

for dir in "$@"
do
	if ! [ -d "$dir" ]; then
		echo "Neispravna putanja do direktorijuma: $dir"
		exit 2
	fi	

	find "$dir" -type f | while read file
	do
        basename=$(basename "$file")
		if [[ $file == *."$ext" ]]; then
			grep -E "^[A-Z].*\.$" "$file" >> "./$basename"
			rm "$file"
		else
			ime=${basename%.*}
			path="${file%/*}"
			mkdir -p "./kopije/$path"
			cp "$file" "./kopije/${file}"
			
			cd "./kopije/${path}"
			cp -s "$basename" "${ime}.ln"
			cd - > /dev/null
		fi
	done
done


