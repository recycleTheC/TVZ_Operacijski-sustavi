#!/bin/sh

for i in 10 100 1000 10000 100000 1000000
do
echo
echo === Mjerenje za $i procesa djece ===
./lab2.out $i > mjerenje-$i.file
./parser.out mjerenje-$i.file
echo ========== Kraj mjerenja ===========
done
