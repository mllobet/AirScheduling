#!/bin/bash

FILES=*.air

# Results1.txt
for f in $FILES
do
../main $f /dev/null 1 ek '-s' >> "Resultado1.txt"
done

## Results2.txt
for f in $FILES
do
../main $f /dev/null 2 ek '-s' >> "Resultado2.txt"
done

## Results2.txt
for f in $FILES
do
../main $f /dev/null 1 ek '-t' >> "t_1_ek.csv"
done

## Results2.txt
for f in $FILES
do
../main $f /dev/null 2 ek '-t' >> "t_2_ek.csv"
done

## Results2.txt
for f in $FILES
do
../main $f /dev/null 1 di '-t' >> "t_1_di.csv"
done

## Results2.txt
for f in $FILES
do
../main $f /dev/null 2 di '-t' >> "t_2_di.csv"
done
