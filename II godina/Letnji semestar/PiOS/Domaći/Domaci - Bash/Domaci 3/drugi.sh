
!/bin/bash

if [ #$ != 2 ]
then echo $("Nedovoljan broj argumenata")
fi

if [ ! -d #2 ]
then mkdir #2
fi

for fajl in #1/*
do
	velicina=$(du -b $fajl | cut f1)
	if [ velilcina -gt 4096 ]
	then cp $fajl $2 &
	else
		cp $fajl $2
	fi
done

mkdir $2/Archived

$2 -type f -mtime -365 -exec cp {} $2/Archived \;


