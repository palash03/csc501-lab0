/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep(int n)
{
	extern int set;
	extern unsigned long ctr1000;
	unsigned long counterStart = ctr1000;
	if(set == 1)
	{
       	 	counterStart = ctr1000;
       	 	struct pentry *proc = &proctab[currpid];
        	proc->freq[18]++;
	}
	STATWORD ps;    
	if (n<0 || clkruns==0)
	{
		if(set == 1)        
                {
			struct pentry *proc = &proctab[currpid];
                	counterStart = ctr1000 - counterStart;
			proc->avg[18] += counterStart;
		}			
		return(SYSERR);   
	}
	if (n == 0) {
	        disable(ps);
		resched();
		restore(ps);
		if(set == 1)                  
	        {
			struct pentry *proc = &proctab[currpid];
                	counterStart = ctr1000 - counterStart;
                        proc->avg[18] = proc->avg[18] + counterStart;
		}
		return(OK);
	}
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0)
		sleep10(10*n);
	if(set == 1)
	{
		struct pentry *proc = &proctab[currpid];
		counterStart = ctr1000 - counterStart;
        	proc->avg[18] = proc->avg[18] + counterStart;
	}
	return(OK);
}
