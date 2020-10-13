#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Nicolas Mahnic");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("HolaMundo LKM");

static int __init hello_init(void){
	pr_info("My name is holamundoMK\n");
	printk(KERN_ALERT "holamundoMK: Hola mundo!. Soy el kernel\n");
	return 0;
}

static void __exit hello_exit(void){
	printk(KERN_ALERT "holamundoMK: Adios mundo!. Soy el kernel\n");
}

module_init(hello_init);
module_exit(hello_exit);