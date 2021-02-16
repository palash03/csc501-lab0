/* stacktrace.c - stacktrace */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

static unsigned long	*esp;
static unsigned long	*ebp;

#define STKDETAIL

/*------------------------------------------------------------------------
 * stacktrace - print a stack backtrace for a process
 *------------------------------------------------------------------------
 */
SYSCALL stacktrace(int pid)
{
	extern int set;
	extern unsigned long ctr1000;
	unsigned long counterStart = ctr1000;
	if(set == 1)
	{
			counterStart = ctr1000;
			struct pentry *proc = &proctab[currpid];
			proc->freq[23]++;
	}
	struct pentry	*proc = &proctab[pid];
	unsigned long	*sp, *fp;

	if (pid != 0 && isbadpid(pid))
	{
		if(set == 1)
		{
				struct pentry *proc = &proctab[currpid];
				counterStart = ctr1000 - counterStart;
				proc->avg[23] = proc->avg[23] + counterStart;
		}
		return SYSERR;
	}
	if (pid == currpid) {
		asm("movl %esp,esp");
		asm("movl %ebp,ebp");
		sp = esp;
		fp = ebp;
	} else {
		sp = (unsigned long *)proc->pesp;
		fp = sp + 2; 		/* where ctxsw leaves it */
	}
	kprintf("sp %X fp %X proc->pbase %X\n", sp, fp, proc->pbase);
#ifdef STKDETAIL
	while (sp < (unsigned long *)proc->pbase) {
		for (; sp < fp; sp++)
			kprintf("DATA (%08X) %08X (%d)\n", sp, *sp, *sp);
		if (*sp == MAGIC)
			break;
		kprintf("\nFP   (%08X) %08X (%d)\n", sp, *sp, *sp);
		fp = (unsigned long *) *sp++;
		if (fp <= sp) {
			kprintf("bad stack, fp (%08X) <= sp (%08X)\n", fp, sp);
			if(set == 1)
			{
					struct pentry *proc = &proctab[currpid];
					counterStart = ctr1000 - counterStart;
					proc->avg[23] = proc->avg[23] + counterStart;
			}
			return SYSERR;
		}
		kprintf("RET  0x%X\n", *sp);
		sp++;
	}
	kprintf("MAGIC (should be %X): %X\n", MAGIC, *sp);
	if (sp != (unsigned long *)proc->pbase) {
		kprintf("unexpected short stack\n");
		if(set == 1)
		{
				struct pentry *proc = &proctab[currpid];
				counterStart = ctr1000 - counterStart;
				proc->avg[23] = proc->avg[23] + counterStart;
		}
		return SYSERR;
	}
#endif
	if(set == 1)
	{
			struct pentry *proc = &proctab[currpid];
			counterStart = ctr1000 - counterStart;
			proc->avg[23] = proc->avg[23] + counterStart;
	}
	return OK;
}
