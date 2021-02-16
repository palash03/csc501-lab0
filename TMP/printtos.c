#include<stdio.h>

unsigned long *esp,*ebp;
void printtos()
{
	asm("movl %ebp,ebp");
	asm("movl %esp,esp");
	kprintf("void printtos()\n");
        kprintf("Before [0x%08X]: 0x%08X\n",ebp+2,*(ebp+2));
	kprintf("After [0x%08X]: 0x%08X\n",ebp,*ebp);
	unsigned long* sp;
	sp = esp;
	sp++;
	kprintf("\telement[0x%08X]:0x%08X\n",sp,*sp);
	sp++;
	kprintf("\telement[0x%08X]:0x%08X\n",sp,*sp);
	sp++;
	kprintf("\telement[0x%08X]:0x%08X\n",sp,*sp);
	sp++;
	kprintf("\telement[0x%08X]:0x%08X\n\n",sp,*sp);
}
