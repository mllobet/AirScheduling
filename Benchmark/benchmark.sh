#!/bin/bash

FILES=./*.air

for f in $FILES
do
../main $f /dev/null $1 $2 >> "Resultado"$1"_"$2.txt
done
