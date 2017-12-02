#!/bin/bash

DATA=`date +%d-%m-%Y`
PLIK=backup_$DATA.tar

tar -czvf $PLIK /etc/*.conf
