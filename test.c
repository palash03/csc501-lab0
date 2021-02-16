/* user.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

int prX;
void halt();

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */
prch(c)
char c;
{
	int i;
	sleep(5);	
}

/*void printtos()
{
	unsigned long* sp;
	asm("movl %esp,esp");
	sp = esp;
	printf("element[0x%08X]:0x%08X",sp,*sp);
	sp++;
	printf("element[0x%08X]:0x%08X",sp,*sp);
	sp++;
	printf("element[0x%08X]:0x%08X",sp,*sp);
	sp++;
	printf("element[0x%08X]:0x%08X",sp,*sp);
}
*/
int main()
{
	kprintf("Task 5 (printsyscallsummary)\n");
	syscallsummary_start();
	resume(prX = create(prch,2000,20,"proc X",1,'A'));
	sleep(10);
	syscallsummary_stop();
	printsyscallsummary();
	return 0;
	
	
	//kprintf("Current: etext[0x%08X]=%lx, edata[0x%08X]=%08X, ebss[0x%08X]=%08X\n",(int)&etext,etext,(int)&edata,edata,(int)&end,end);
    //kprintf("Preceding: etext[0x%08X]=%lx, edata[0x%08X]=%08X, ebss[0x%08X]=%08X\n",(int)(&etext-sizeof(int)),(int)(*(&etext-sizeof(int))),(&edata-sizeof(int)),(int)(*(&edata-sizeof(int))),(int)&end-sizeof(int),(int)(*(&end-sizeof(int))));
    //kprintf("After: etext[0x%08X]=%lx, edata[0x%08X]=%08X, ebss[0x%08X]=%08X\n",(int)&etext+sizeof(int),(int)(*(&etext+sizeof(int))),(int)(&edata+sizeof(int)),(int)(*(&edata+sizeof(int))),(int)(&end+sizeof(int)),(int)(*(&end+sizeof(int))));
}

/*#include<stdio.h>

void printprocstks(int priority)
{
	extern int numproc;
	struct pentry *p = &proctab[numproc];
	int i,j;
	for(i=0;i<numproc;i++)
	{
		if(p->pprio > priority)
		{
			kprintf("[%s]\n",p->pname);
			kprintf("pid: %d\n",pid);
			kprintf("priority: %d\n",p->pprio);
			kprintf("base: %d\n",p->pbase);
			kprintf("limit: %d\n",p->plimit);
			kprintf("len: %d\n",p->pstklen);
			kprintf("pointer: %d\n",p->pesp);
		}
	}
}
*/
