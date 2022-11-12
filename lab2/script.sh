#!/bin/bash

if [ ! -f "lab2" ]; then
	gcc lab2.c -o lab2.out
fi

if [ ! -f "parser" ]; then
	gcc parser.c -o parser.out
fi

if [ ! -d "output" ]; then
	mkdir output
fi


for i in 10 100 1000 10000 100000 1000000
do
	echo
	echo === Mjerenje za $i procesa djece ===
	./lab2.out $i > output/mjerenje-$i.file
	./parser.out output/mjerenje-$i.file
	echo ========== Kraj mjerenja ===========
done
