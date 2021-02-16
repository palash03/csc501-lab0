/* gettime.c - gettime */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <date.h>

extern int getutim(unsigned long *);

/*------------------------------------------------------------------------
 *  gettime  -  get local time in seconds past Jan 1, 1970
 *------------------------------------------------------------------------
 */
SYSCALL	gettime(long *timvar)
{
	extern int set;
	extern unsigned long ctr1000;
	unsigned long counterStart = ctr1000;
	if(set == 1)
	{
			counterStart = ctr1000;
			struct pentry *proc = &proctab[currpid];
			proc->freq[4]++;
	}

    /* long	now; */

	/* FIXME -- no getutim */
	if(set == 1)
	{
		struct pentry *proc = &proctab[currpid];
		counterStart = ctr1000 - counterStart;
		proc->avg[4] = proc->avg[4] + counterStart;
	}
    return OK;
}
