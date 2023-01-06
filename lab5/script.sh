#!/bin/bash

if [ ! -d "output" ]; then
	mkdir output
fi

for i in 5 10 15 20 25 30
do
	echo Mjerenje: $i jela
	./ekipa.out $i > output/mjerenje-${i}.file
done
