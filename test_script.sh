#!/bin/bash
touch log.txt
for i in `seq 1 $1`;
do
    ./morse.run Exemplo/TabelaMorse.txt Exemplo/TheGodfather-MarioPuzo-Chapter1-English.txt b.out >> log.txt
    ./morse.run Exemplo/TabelaMorse.txt Exemplo/TheGodfather-MarioPuzo-Chapter1-English.txt b.out avl >> log.txt
done
