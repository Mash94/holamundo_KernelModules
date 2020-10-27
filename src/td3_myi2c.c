#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>

#define MENOR 0
#define CANT_DISP 1

static dev_t myi2c;
struct cdev * myi2c_cdev;

struct file_operations i2c_ops;

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Nicolas Mahnic");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("HolaMundo LKM");

static int __init hello_init(void){
	pr_alert("td3_myi2c: Soy el modulo td3_myi2c del kernel\n");
	myi2c_cdev = cdev_alloc();
	if((alloc_chrdev_region(&myi2c, MENOR, CANT_DISP, "td3_myi2c")) < 0){
		pr_alert("td3_myi2c: No es posible asignar el numero mayor\n");
		return 0;
	}
	pr_alert("td3_myi2c: Numero mayor asignado %d\n", MAJOR(myi2c));
	cdev_init(myi2c_cdev, &i2c_ops);
	myi2c_cdev->owner = THIS_MODULE;
	myi2c_cdev->dev = myi2c;
	if((cdev_add(myi2c_cdev, myi2c, CANT_DISP)) < 0){
		unregister_chrdev_region(myi2c, CANT_DISP);
		pr_alert("td3_myi2c: No es no es posible registrar el dispositivo\n");
		return 0;
	}
	return 0;
}

static void __exit hello_exit(void){
	printk(KERN_ALERT "td3_myi2c: Adios mundo!. Soy el kernel\n");
	cdev_del(myi2c_cdev);
	unregister_chrdev_region(myi2c, CANT_DISP);
}

module_init(hello_init);
module_exit(hello_exit);