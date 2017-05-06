#!/bin/bash

if [ $# != 1 ]
then
	echo "Uzycie $0 <plik>"
	exit
fi

PLIK=$1
ROZSZERZENIE=${PLIK#*.}

case $ROZSZERZENIE in
zip)
	unzip $PLIK
;;
tar)
	tar -xvf $PLIK
;;
*) echo "Nieznane rozszerzenie pliku"
esac
