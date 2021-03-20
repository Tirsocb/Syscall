# Syscall para verificar expresiones aritméticas balanceadas :heavy_check_mark:
Desarrollar una función que determine si una expresión aritmética se encuentra correctamente
cerrada. La función deberá retornar `Is balanced` si la expresión está correctamente cerrada y `Not balanced` de lo
contrario.

Se entiende por cerrada al hecho de que cada símbolo de paréntesis y/o corchete abierto debe tener su correspondiente cierre. 

Ejemplos:
- (5+5)[(1+1)*(2+2)]
- (((([1]))))

Dicha función debe de estar implementada en un system call.
***
# Índice :bow_and_arrow:
- [1. Archivos en el proyecto](#archivos-:open_file_folder:)

- [2. Diagrama Syscall](#diagrama-syscall-:bar_chart:)

- [3. Requerimientos](#requerimientos-:pushpin:)

- [4. Agregar syscall al kernel de Linux](#agregar-syscall-al-kernel-de-linux-:round_pushpin:)

  * [4.1. Preparación](##preparación-:battery:)
  * [4.2. Creación](##creación-:electric_plug:)
  * [4.3. Instalación](##instalación-:inbox_tray:)
  * [4.4. Resultado](##resultado-:test_tube:)

- [5. Syscall en acción](#syscall-en-acción-:bulb:)

- [6. Developers](#developers-:man_technologist:)

- [7. Referencias](#referencias-:pen:)


# Archivos :open_file_folder:
1. Checkbalanced
  * Makefile
  * checkbalanced.c
2. checkbalanced_test.c

# Diagrama Syscall :bar_chart:
![ScreenShot](https://github.com/Tirsocb/Syscall/blob/main/img/Diagrama.png)


# Requerimientos :pushpin:
1. Computadora :computer:
2. Visual Studio Code :spiral_notepad:
3. Máquina Virtual (VirtualBox) con Ubuntu 20.04 LTS :desktop_computer:

# Agregar syscall al kernel de Linux :round_pushpin:

## Preparación :battery:

El proceso se realiza dentro de la máquina virtual instalada.

Iniciar preparando el sistema operativo

```properties
sudo apt update && sudo apt upgrade -y
``` 

Descargar e instalar las paquetes para compilar el kernel

```properties
sudo apt install build-essential libncurses-dev libssl-dev libelf-dev bison flex -y
``` 

Limpiar los paquetes instalados

```properties
sudo apt clean && sudo apt autoremove -y
``` 

Descargar el código fuente del kernel de Linux (5.8.1)

```properties
wget -P ~/ https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.8.1.tar.xz
``` 

Descomprimir el tarball

```properties
tar -xvf ~/linux-5.8.1.tar.xz -C ~/
``` 

Reiniciar la máquina virtual

## Creación :electric_plug:

Cambiar al directorio del código fuente descomprimido

```properties
cd ~/linux-5.8.1/
``` 

Crear la carpeta para el syscall `checkbalanced`

```properties
mkdir checkbalanced
``` 

Crear el archivo C para el syscall

```properties
code checkbalanced/checkbalanced.c
``` 

Escribir el código correspondiente

[Código](https://github.com/Tirsocb/Syscall/blob/main/checkbalanced/checkbalanced.c)

Guardar los cambios realizados.

Crear un archivo `Makefile`

```properties
code checkbalanced/Makefile
``` 

Escribir este código

```properties
obj-y := identity.o
``` 

Guardar los cambios realizados.

Añadir el directorio del syscall al `Makefile` principal

```properties
code Makefile
``` 

Buscar `core-y`, el segundo resultado muestro lo siguiente:

`kernel/ certs/ mm/ fs/ ipc/ security/ crypto/ block/`

Añadir el directorio de nuestro syscall

```properties
kernel/ certs/ mm/ fs/ ipc/ security/ crypto/ block/ checkbalanced/
``` 

Guardar los cambios realizados.

Añadir el prototipo del syscall

```properties
code include/linux/syscalls.h
``` 

Escribir lo siguiente antes de `#endif`

```properties
asmlinkage long sys_checkbalanced(char *expression, int n);
``` 

Guardar los cambios realizados.

Añadir el syscall a la tabla de syscall del kernel. Primero abrir la tabla con

```properties
code arch/x86/entry/syscalls/syscall_64.tbl
``` 

Dependiendo del orden de filas numeradas, añadir lo siguiente. Usar tab para espacios.

```properties
441     common  checkbalanced                sys_checkbalanced
``` 

En este caso, 441 será el número del syscall añadido.

Guardar los cambios realizados.

## Instalación :inbox_tray:

Abrir la ventana de configuración con el comando

```properties
sudo make menuconfig
``` 

Usar tab para moverse entre opciones. No hacer ningún cambio, solo Guardar y Salir.

Conocer el número de cores de la computadora, puede acelerar el proceso de compilado.

```properties
nproc
``` 

En mi caso cuento con `2` cores. Entonces escribo 2 después de `-j`

Compilar el código fuente del kernel. Esto puede llevar mucho tiempo :coffee:

```properties
sudo make -j2
``` 

Preparar el instalador del kernel

```properties
sudo make modules_install -j2
``` 

Instalar el kernel

```properties
sudo make install -j2
``` 

Actualizar el bootloader del sistema operativo con el nuevo kernel

```properties
sudo update-grub
``` 

Reiniciar la computadora

## Resultado 	:test_tube:

Ejecute el siguiente comando para verificar la versión del kernel instalado. El resultado será `5.8.1`

```properties
uname -r
``` 

En el directorio de su gusto, crear un archivo C para generar un reporte del éxito o fracaso del syscall.

```properties
code checkbalanced_test.c
``` 

Escribir el siguiente código

[Código](https://github.com/Tirsocb/Syscall/blob/main/checkbalanced_test.c)

Guardar los cambios realizados.

Compilar el archivo C creado

```properties
gcc -o checkbalanced_test checkbalanced_test.c
``` 

Ejecutar el archivo C recién compilado

```properties
./checkbalanced_test
``` 

Ingresar su expresión aritmética y esperar el resultado.

# Syscall en acción :bulb:

Test con corchetes, expresión balanceada.

![ScreenShot](https://github.com/Tirsocb/Syscall/blob/main/img/03.png)

Test con expresión matemática balanceada.

![ScreenShot](https://github.com/Tirsocb/Syscall/blob/main/img/04.png)

Test con expresión matemática no balanceada.

![ScreenShot](https://github.com/Tirsocb/Syscall/blob/main/img/05.png)

# Developers :man_technologist:

[Abner Xocop Chacach](https://github.com/abnerxch) :ghost:

[Tirso Córdova](https://github.com/Tirsocb) :robot:

# Referencias :pen:

[Jihan Jasper Al-rashid](https://dev.to/jasper/adding-a-system-call-to-the-linux-kernel-5-8-1-in-ubuntu-20-04-lts-2ga8)

[Aashiq Mohammed](https://github.com/AashiqMohammed/Data-Structures/blob/master/Parentheses%20Balance)

# License :card_file_box:
[MIT](https://choosealicense.com/licenses/mit/)