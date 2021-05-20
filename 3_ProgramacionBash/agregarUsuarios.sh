#!/bin/bash
ROOT_UID=0
SUCCESS=0

# Ejecutar como usuario root
if [ "$UID" -ne "$ROOT_UID" ]
then
	echo "Se debe estar como root para ejecutar este script"
	exit $$E_NOTROOT
fi

file=$1

if [ "${file}X" = "X" ];
then
	echo "Debes indicar el archivo del listado con el listado de los usuarios a ingresar..."
	exit 1
fi

# el archivo debe se
