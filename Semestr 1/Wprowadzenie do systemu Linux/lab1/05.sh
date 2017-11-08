#!/bin/bash

SCIEZKA=pierwszy

if [ -d $SCIEZKA ]
then
	rm -R $SCIEZKA
	echo "Sciezka $SCIEZKA zostala usunieta"
else
	echo "Sciezka $SCIEZKA nieistnieje"
fi
