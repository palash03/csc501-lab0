/* scount.c - scount */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <sem.h>

/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL scount(int sem)
{
	extern int set;
	extern unsigned long ctr1000;
	unsigned long counterStart = ctr1000;
	if(set == 1)
	{
			counterStart = ctr1000;
			struct pentry *proc = &proctab[currpid];
			proc->freq[10]++;
	}

extern	struct	sentry	semaph[];

	if (isbadsem(sem) || semaph[sem].sstate==SFREE)
	{
		if(set == 1)
		{
				struct pentry *proc = &proctab[currpid];
				counterStart = ctr1000 - counterStart;
				proc->avg[10] = proc->avg[10] + counterStart;
		}
		return(SYSERR);
	}
	if(set == 1)
	{
			struct pentry *proc = &proctab[currpid];
			counterStart = ctr1000 - counterStart;
			proc->avg[10] = proc->avg[10] + counterStart;
	}
	return(semaph[sem].semcnt);
}
