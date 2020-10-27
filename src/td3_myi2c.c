#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>

#define MENOR 0
#define CANT_DISP 1
#define DEVICE_NAME "td3_myi2c"

static dev_t myi2c;
struct cdev * myi2c_cdev;
struct file_operations i2c_ops;

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Nicolas Mahnic R5054");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("TD3_MYI2C LKM");

static int __init i2c_init(void){
	pr_alert("%s: Soy el modulo td3_myi2c del kernel\n", DEVICE_NAME);
	myi2c_cdev = cdev_alloc();
	
	if((alloc_chrdev_region(&myi2c, MENOR, CANT_DISP, DEVICE_NAME)) < 0){
		pr_alert("%s: No es posible asignar el numero mayor\n", DEVICE_NAME);
		return -1;
	}

	pr_alert("%s: Numero mayor asignado %d 0x%X\n", DEVICE_NAME, MAJOR(myi2c), MAJOR(myi2c));
	//cdev_init(myi2c_cdev, &i2c_ops);
	myi2c_cdev->ops = &i2c_ops;
	myi2c_cdev->owner = THIS_MODULE;
	myi2c_cdev->dev = myi2c;
	if((cdev_add(myi2c_cdev, myi2c, CANT_DISP)) < 0){
		unregister_chrdev_region(myi2c, CANT_DISP);
		pr_alert("%s: No es no es posible registrar el dispositivo\n", DEVICE_NAME);
		return -1;
	}
	return 0;
}

static void __exit i2c_exit(void){
	printk(KERN_ALERT "%s: Adios mundo!. Soy el kernel\n", DEVICE_NAME);
	cdev_del(myi2c_cdev);
	unregister_chrdev_region(myi2c, CANT_DISP);
}

module_init(i2c_init);
module_exit(i2c_exit);