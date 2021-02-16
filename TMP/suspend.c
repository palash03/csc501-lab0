/* suspend.c - suspend */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  suspend  --  suspend a process, placing it in hibernation
 *------------------------------------------------------------------------
 */
SYSCALL	suspend(int pid)
{
	extern int set;
	extern unsigned long ctr1000;
	unsigned long counterStart = ctr1000;
	if(set == 1)
	{
			counterStart = ctr1000;
			struct pentry *proc = &proctab[currpid];
			proc->freq[24]++;
	}
	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority returned		*/

	disable(ps);
	if (isbadpid(pid) || pid==NULLPROC ||
	 ((pptr= &proctab[pid])->pstate!=PRCURR && pptr->pstate!=PRREADY)) {
		restore(ps);
		if(set == 1)
		{
				struct pentry *proc = &proctab[currpid];
				counterStart = ctr1000 - counterStart;
				proc->avg[24] = proc->avg[24] + counterStart;
		}
		return(SYSERR);
	}
	if (pptr->pstate == PRREADY) {
		pptr->pstate = PRSUSP;
		dequeue(pid);
	}
	else {
		pptr->pstate = PRSUSP;
		resched();
	}
	prio = pptr->pprio;
	restore(ps);
	if(set == 1)
	{
			struct pentry *proc = &proctab[currpid];
			counterStart = ctr1000 - counterStart;
			proc->avg[24] = proc->avg[24] + counterStart;
	}
	return(prio);
}
