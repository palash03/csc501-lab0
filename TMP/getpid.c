/* getpid.c - getpid */

#include <conf.h>
#include <kernel.h>
#include <proc.h>

/*------------------------------------------------------------------------
 * getpid  --  get the process id of currently executing process
 *------------------------------------------------------------------------
 */
SYSCALL getpid()
{
	extern int set;
	extern unsigned long ctr1000;
	unsigned long counterStart = ctr1000;
	if(set == 1)
	{
		counterStart = ctr1000;
		struct pentry *proc = &proctab[currpid];
		proc->freq[2]++;
	}
	if(set == 1)
	{
		struct pentry *proc = &proctab[currpid];
		counterStart = ctr1000 - counterStart;
		proc->avg[2] = proc->avg[2] + counterStart;
	}
	return(currpid);
}
