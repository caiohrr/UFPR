#!/bin/bash


VALORES_TESTE=(64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000)

for n in ${VALORES_TESTE[@]}
do 
        ./gera_entrada $n > testes/$n.in
done
