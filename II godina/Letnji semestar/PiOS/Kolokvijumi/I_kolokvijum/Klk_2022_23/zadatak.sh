#!/bin/bash

if [ ! -d $1 ]
then
	echo "Prvi folder ne postoji."
	exit -1
fi

if [ ! -d $2 ]
then
	mkdir ./$2
else
	rm -r ./$2
	mkdir ./$2
fi

folder=$1
dest=$2

touch "sistem_errors.txt"

fajlovi=$( ls $folder | grep -E ".*(\.core_dump)$")

for fajl in $fajlovi
do
        if [[ $(basename $fajl) =~ ^[A-Z0-9][a-z\@\#\$\_]{4,19}\.core_dump ]]
        then
                mv $folder/$fajl $dest
        
	else
		ln -s $fajl $fajl-ln
	fi
done

fajlovi_error=$(find $dest -type f)

for fajl in $fajlovi_error
do
	cat $fajl | grep -E "^ERROR" >> "sistem_errors.txt"
done


