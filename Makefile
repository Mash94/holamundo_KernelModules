KERNEL_SOURCE = /lib/modules/$(shell uname -r)/build
MOD_NAME = holamundoMK

# Converts a module object in LKM
obj-m += src/$(MOD_NAME).o

#compila el modulo haciendo una llamada al Makefile que esta en '/lib/modules/$(shell uname -r)/build'
all:
	make -C ${KERNEL_SOURCE} M=${PWD} modules

#limpia todos los archivos objetos
clean:
	make -C ${KERNEL_SOURCE} M=${PWD} clean

#revisa si el modulo esta instalado
cat:
	cat /proc/modules | grep $(MOD_NAME)

#instala el modulo
insmod:
	sudo insmod src/$(MOD_NAME).ko

#desinstala el modulo
rmmod:
	sudo rmmod src/$(MOD_NAME).ko

#muestra los mensajes (dmesg), en el ejemplo todos los printk imprimen el nombre del archivo
dmesg:
	dmesg | grep $(MOD_NAME) 