/* getprio.c - getprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * getprio -- return the scheduling priority of a given process
 *------------------------------------------------------------------------
 */
SYSCALL getprio(int pid)
{
	extern int set;
	extern unsigned long ctr1000;
	unsigned long counterStart = ctr1000;
	if(set == 1)
	{
			counterStart = ctr1000;
			struct pentry *proc = &proctab[currpid];
			proc->freq[3]++;
	}

	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		if(set == 1)
		{
			struct pentry *proc = &proctab[currpid];
			counterStart = ctr1000 - counterStart;
			proc->avg[3] = proc->avg[3] + counterStart;
		}
		return(SYSERR);
	}
	restore(ps);
	if(set == 1)
	{
		struct pentry *proc = &proctab[currpid];
		counterStart = ctr1000 - counterStart;
		proc->avg[3] = proc->avg[3] + counterStart;
	}
	return(pptr->pprio);
}
