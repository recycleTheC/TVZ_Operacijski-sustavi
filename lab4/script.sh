#!/bin/bash

if [ ! -d "output" ]; then
	mkdir output
fi

echo > output/mjerenje-procesi.file
echo > output/mjerenje-dretve.file

for i in 1 10 100 1000 10000 100000
do
	for j in {1..20}
	do
		echo $j,$i >> output/mjerenje-procesi.file
		{ time ./procesi.out $i; } 2>>output/mjerenje-procesi.file
		echo $j,$i >> output/mjerenje-dretve.file
		{ time ./dretve.out $i; } 2>>output/mjerenje-dretve.file
	done
done
