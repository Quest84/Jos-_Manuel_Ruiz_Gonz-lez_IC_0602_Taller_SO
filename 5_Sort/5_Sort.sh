#!/bin/bash

input=$1
output=$2

if [ "${input}X" = "X" ];
then
	echo "Debes indicar el archivo de entrada..."
	exit 1
fi

if [ "${output}X" = "X" ];
then
	echo "Debes indicar como segundo parametro el archivo de salida..."
	exit 1
fi

echo "Analizando archivo de entrada..."
echo -e "Leyendo la linea entera:"
cat $input

echo "> Separando las palabras"
while read line
do
	for word in $line
	do
		# echo -e "Separando la linea en palabras\n $word"
		echo -e "$word" >> buffer.txt
	done
done < $input

echo "> Limpiando el buffer"
> output.txt

echo "> Ordenando las palabras"
sort buffer.txt >> output.txt
rm buffer.txt

echo ""
echo "Contenido original: "
cat $input

echo ""
echo "Contenido separado y ordenado: "
cat $output
