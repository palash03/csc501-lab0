/* sleep1000.c - sleep1000 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * sleep1000 --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
SYSCALL sleep1000(int n)
{
	extern int set;
	extern unsigned long ctr1000;
	unsigned long counterStart = ctr1000;
	if(set == 1)
	{
			counterStart = ctr1000;
			struct pentry *proc = &proctab[currpid];
			proc->freq[21]++;
	}
	STATWORD ps;    

	if (n < 0  || clkruns==0)
	{
		if(set == 1)
		{
				struct pentry *proc = &proctab[currpid];
				counterStart = ctr1000 - counterStart;
				proc->avg[21] = proc->avg[21] + counterStart;
		}
	    return(SYSERR);
	}
	disable(ps);
	if (n == 0) {		/* sleep1000(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	if(set == 1)
	{
			struct pentry *proc = &proctab[currpid];
			counterStart = ctr1000 - counterStart;
			proc->avg[21] = proc->avg[21] + counterStart;
	}
	return(OK);
}
