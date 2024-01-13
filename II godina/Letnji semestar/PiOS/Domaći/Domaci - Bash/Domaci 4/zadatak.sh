#!/bin/bash

if [ $# -lt 2 ]
then
	echo "Nedovoljno argumenata"
fi

if [ $2 = "-d" ]
then

	echo "Da li ste sigurni da zelite da obrisete instalaciju?"
	read odgovor
	if [ odgovor == "yes" ]
	then
		if [ -d $1 ]
		then
			echo "Instalacija ne postoji"

		else
			rm -r $1
		fi
	fi
fi

if [ $2 = "-i" ]
then
	for fajl in $1/*;
	do
		if [[ $fajl == *.c ]]
		then
			naziv="$(basename $fajl .c).exe"
			gcc -o $naziv $fajl
		fi
	done
fi

if [ ! -d $1 ]
then 
	mkdir $1
else
	rm -r $1
	mkdir $1
fi

if [ ! -d $1/src ]
then 
	mkdir $1/src
else
	rm -r $1/src
	mkdir $1/src
fi

if [ ! -d $1/bin ]
then
        mkdir $1/bin
else
        rm -r $1/bin
        mkdir $1/bin
fi

if [ ! -d $1/etc ]
then
        mkdir $1/etc
else
        rm -r $1/etc
        mkdir $1/etc
fi

for fajl in INSTALL_DIR/*;
do
	if [[ $fajl == *.c ]]
	then
		cp $fajl INSTALL_DIR/src
	fi
done

for fajl in ./*;
do
        if [[ $fajl == *.exe ]]
        then
                cp $fajl INSTALL_DIR/bin
        fi
done













