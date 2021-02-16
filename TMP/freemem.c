/* freemem.c - freemem */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <mem.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  freemem  --  free a memory block, returning it to memlist
 *------------------------------------------------------------------------
 */
SYSCALL	freemem(struct mblock *block, unsigned size)
{
	extern int set;
	extern unsigned long ctr1000;
	unsigned long counterStart = ctr1000;
	if(set == 1)
	{
		counterStart = ctr1000;
		struct pentry *proc = &proctab[currpid];
		proc->freq[0]++;
	}	
	STATWORD ps;    
	struct	mblock	*p, *q;
	unsigned top;

	if (size==0 || (unsigned)block>(unsigned)maxaddr
	    || ((unsigned)block)<((unsigned) &end))
	{
		if(set == 1)
		{
			struct pentry *proc = &proctab[currpid];
			counterStart = ctr1000 - counterStart;
			proc->avg[0] = proc->avg[0] + counterStart;
		}
		return(SYSERR);
	}
	size = (unsigned)roundmb(size);
	disable(ps);
	for( p=memlist.mnext,q= &memlist;
	     p != (struct mblock *) NULL && p < block ;
	     q=p,p=p->mnext )
		;
	if (((top=q->mlen+(unsigned)q)>(unsigned)block && q!= &memlist) ||
	    (p!=NULL && (size+(unsigned)block) > (unsigned)p )) {
		restore(ps);
		if(set == 1)
		{
			struct pentry *proc = &proctab[currpid];
			counterStart = ctr1000 - counterStart;
			proc->avg[0] = proc->avg[0] + counterStart;
		}
		return(SYSERR);
	}
	if ( q!= &memlist && top == (unsigned)block )
			q->mlen += size;
	else {
		block->mlen = size;
		block->mnext = p;
		q->mnext = block;
		q = block;
	}
	if ( (unsigned)( q->mlen + (unsigned)q ) == (unsigned)p) {
		q->mlen += p->mlen;
		q->mnext = p->mnext;
	}
	restore(ps);
	if(set == 1)
	{
		struct pentry *proc = &proctab[currpid];
		counterStart = ctr1000 - counterStart;
		proc->avg[0] = proc->avg[0] + counterStart;
	}
	return(OK);
}
