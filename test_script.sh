#!/bin/bash
if [ ! -d "build" ]; then
make
fi

rm -f log.txt

for i in `seq 1 $1`;
do
	echo -e '\nConvertendo Arquivo pequeno com Tabela ordenada:' >> log.txt
    build/morse.run Exemplo/TabelaMorse.txt Exemplo/TheGodfather-MarioPuzo-Chapter1-English.txt /dev/null >> log.txt
    build/morse.run Exemplo/TabelaMorse.txt Exemplo/TheGodfather-MarioPuzo-Chapter1-English.txt /dev/null avl >> log.txt
	echo -e '\nConvertendo Arquivo pequeno com Tabela desordenada:' >> log.txt
    build/morse.run Exemplo/TabelaMorseAlt.txt Exemplo/TheGodfather-MarioPuzo-Chapter1-English.txt /dev/null >> log.txt
    build/morse.run Exemplo/TabelaMorseAlt.txt Exemplo/TheGodfather-MarioPuzo-Chapter1-English.txt /dev/null avl >> log.txt
	echo -e '\nConvertendo Arquivo grande com Tabela ordenada:' >> log.txt
    build/morse.run Exemplo/TabelaMorse.txt Exemplo/LesMiserablesPlus.txt /dev/null >> log.txt
    build/morse.run Exemplo/TabelaMorse.txt Exemplo/LesMiserablesPlus.txt /dev/null avl >> log.txt
	echo -e '\nConvertendo Arquivo grande com Tabela desordenada:' >> log.txt
    build/morse.run Exemplo/TabelaMorseAlt.txt Exemplo/LesMiserablesPlus.txt /dev/null >> log.txt
    build/morse.run Exemplo/TabelaMorseAlt.txt Exemplo/LesMiserablesPlus.txt /dev/null avl >> log.txt
done
