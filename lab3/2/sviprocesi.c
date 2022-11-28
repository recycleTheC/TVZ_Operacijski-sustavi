#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/sched/signal.h> // naredba je premjestena u drugi library
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("(2) Modul za ispis procesa: OS - TVZ 2022");
MODULE_AUTHOR("Mario Kopjar");

int start(void){
	printk(KERN_INFO "Procesi:\n");
	
	struct task_struct *proc;
	
	for_each_process(proc)
	{
		printk(KERN_INFO "Proces '%s' (%d), stanje: %ld\n", proc->comm, proc->pid, proc->state);
		printk(KERN_INFO "- vrijeme koristenja CPU-a (user): %llu\n", proc->utime);
		printk(KERN_INFO "- vrijeme koristenja CPU-a (system): %llu\n", proc->stime);
		printk(KERN_INFO "- roditej '%s' (%d), stanje: %ld,\n", proc->real_parent->comm, proc->real_parent->pid, proc->real_parent->state);
	}
	
	return 0;
}

void end(void){
	return;
}

module_init(start);
module_exit(end);
