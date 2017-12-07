#!/bin/bash
if [ ! -d "build" ]; then
make
fi

rm -f log.txt

for i in `seq 1 $1`;
do
    build/morse.run Exemplo/TabelaMorse.txt Exemplo/TheGodfather-MarioPuzo-Chapter1-English.txt /dev/null >> log.txt
    build/morse.run Exemplo/TabelaMorse.txt Exemplo/TheGodfather-MarioPuzo-Chapter1-English.txt /dev/null avl >> log.txt
done
