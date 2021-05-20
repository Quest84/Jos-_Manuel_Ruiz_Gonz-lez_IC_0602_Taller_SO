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

# Del archivo se debe seguir el siguiente formato:
# $f1 = username
# $f2 = password *por defecto es el nombre de usuario, pero se debe cambiar con el primer inicio de sesión
# $f3 = User ID *no se utiliza sí se deja en blanco
# $f4 = Group ID (GID), este ID debe existir en /etc/group
# $f5 = User ID INFO
# $f6 = home directory
# $f7 = comand shell

crearUsuarios(){
	# echo "----> Crear Usuario <-----"
	eval username="$1"
	eval password="$2"
	eval userID="$3"
	eval groupID="$4"
	eval userIDInfo="$5"
	eval homeDirectory="$6"
	eval shell="$7"
	
	# Evalua si existe el grupo
	echo ""
	echo "---- Comprobando si existe el grupo ${groupID} ----"
	if grep -q ${groupID} /etc/group
	then
		echo "---------------------------------------"
		echo "El ID del grupo ${groupID} si existe"
		# Evaluar si existe el usuario
		if grep -q ${username} /etc/passwd
		then
			echo "--------------------------------------------"
			echo "El usuario ${username} ya está registrado"
		else
			echo "--------------------------------------------"
			echo "Se creará el usuario ${username}"
	      		useradd -c "${userID} ${userIDInfo}" -p "${password}" -d "${homeDirectory}""${username}" -s "${shell}" "${username}" -u "${groupID}"
		      	echo "----> Usuario: ${username} creado con exito <----" 
		 	echo "Usuario: ${username} Contraseña: ${password}"
			echo "--------------------------------------------"
		fi
	else 
		echo "El ID del grupo ${groupID} no existe"
	fi
}

while IFS=: read -r f1 f2 f3 f4 f5 f6 f7
do
	crearUsuarios "\${f1}" "\${f2}" "\${f3}" "\${f4}" "\${f5}" "\${f6}" "\${f7}"
done < ${file}

exit 0
