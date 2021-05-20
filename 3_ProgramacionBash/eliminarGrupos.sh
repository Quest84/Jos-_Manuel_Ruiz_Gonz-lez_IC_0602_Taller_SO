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
	echo "Debes indicar el archivo del listado de los grupos a eliminar..."
	exit 1
fi

# El archivo con el listado de grupos a eliminar:
# Ejemplo:
# $f1 = nombreGrupo

eliminarGrupo(){
	#echo "-----> Eliminar Grupo <-----"
	eval nombreGrupo="$1"
	groupdel "${nombreGrupo}"
	if [ $? -eq $SUCCESS ];
	then
		echo "Grupo [${nombreGrupo}] eliminado correctamente..."
	else
		echo "Grupo [${nombreGrupo}] no se pudo eliminar o no existe..."
	fi
}

while IFS=: read -r f1
do
	eliminarGrupo "\${f1}"
done < ${file}

exit 0
