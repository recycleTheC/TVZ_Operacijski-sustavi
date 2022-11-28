#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("(1) Osnovni modul za OS - TVZ 2022");
MODULE_AUTHOR("Mario Kopjar");

int start(void){
	printk(KERN_INFO "Ucitavam jezgreni modul\n");
	printk(KERN_INFO "Jiffies: %lu\n", jiffies);
	printk(KERN_INFO "Proteklo vrijeme: %lu\n", jiffies/HZ);
	return 0;
}

void end(void){
	printk(KERN_INFO "Uklanjanje jezgrenog modula\n");
	printk(KERN_INFO "Jiffies: %lu\n", jiffies);
	printk(KERN_INFO "Proteklo vrijeme: %lu\n", jiffies/HZ);
}

module_init(start);
module_exit(end);
