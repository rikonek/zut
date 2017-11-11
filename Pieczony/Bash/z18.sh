#!/bin/bash
for i in `find /etc/* -maxdepth 0 -type d -exec du -d0 -k {} \; | cut -f1` ; do
	sum=$(expr $sum + $i)
done
echo "Zajetosc: " $sum "KB"
