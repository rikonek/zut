#!/bin/bash

function sprawdz_argumenty
{
	if [ $# != 2 ]
	then
		echo "Uzycie $0 <argument1> <argument2>"
		exit
	fi
}

function zapisz_do_pliku
{
	if [ -f $2 ]
	then
		rm $2
	fi
	for i in $(seq 1 ${#1})
	do
		echo ${1:i-1:1} >> $2
	done
}

sprawdz_argumenty $@
for i in $@
do
	echo $i
	zapisz_do_pliku $1 $2
done
