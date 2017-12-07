#!/bin/bash
touch log.txt
for i in `seq 1 $1`;
do
    ./morse.run Exemplo/TabelaMorse.txt Exemplo/TheGodfather-MarioPuzo-Chapter1-English.txt /dev/null >> log.txt
    ./morse.run Exemplo/TabelaMorse.txt Exemplo/TheGodfather-MarioPuzo-Chapter1-English.txt /dev/null avl >> log.txt
done
