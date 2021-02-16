/* resume.c - resume */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * resume  --  unsuspend a process, making it ready; return the priority
 *------------------------------------------------------------------------
 */
SYSCALL resume(int pid)
{
	extern int set;
	extern unsigned long ctr1000;
	unsigned long counterStart = ctr1000;
	if(set == 1)
	{
		counterStart = ctr1000;
		struct pentry *proc = &proctab[currpid];
		proc->freq[9]++;
	}	
	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority to return		*/

	disable(ps);
	if (isbadpid(pid) || (pptr= &proctab[pid])->pstate!=PRSUSP) {
		restore(ps);
		if(set == 1)
		{
				struct pentry *proc = &proctab[currpid];
				counterStart = ctr1000 - counterStart;
				proc->avg[9] = proc->avg[9] + counterStart;
		}
		return(SYSERR);
	}
	prio = pptr->pprio;
	ready(pid, RESCHYES);
	restore(ps);
	if(set == 1)
	{
			struct pentry *proc = &proctab[currpid];
			counterStart = ctr1000 - counterStart;
			proc->avg[9] = proc->avg[9] + counterStart;
	}
	return(prio);
}
