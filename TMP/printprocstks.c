#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

struct pentry *p;
extern int currpid;
long *esp;

void printprocstks(int priority)
{
	kprintf("void printprocstks(int priority)\n");
	int i;
	for(i=0;i<NPROC;i++)
	{
		p = &proctab[i];
		if(p->pprio > priority)
		{
			kprintf("Process [%s]\n",p->pname);
			kprintf("\tpid: %d\n",i);
			kprintf("\tpriority: %d\n",p->pprio);
			kprintf("\tbase: %08X\n",p->pbase);
			kprintf("\tlimit: %08Xx\n",p->plimit);
			kprintf("\tlen: %d\n",p->pstklen);
			if(i == currpid)
			{
				asm("movl %esp,esp");
				kprintf("\tpointer: 0x%08X\n",esp);
			}
			else
			{
				kprintf("pointer: 0x%08X\n",p->pesp);
			}			
		}
	}
	kprintf("\n");
}
