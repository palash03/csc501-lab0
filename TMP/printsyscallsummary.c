#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

void syscallsummary_start();
void syscallsummary_stop();

void syscallsummary_start()
{
	extern int set;
	int i,j;
	set = 1;
	for(i=0;i<NPROC;i++)
	{
		struct pentry *proc = &proctab[i];
		for(j=0;j<27;j++)
		{
			proc->freq[j] = 0;
			proc->avg[j] = 0;		
		}
	}
}

void syscallsummary_stop()
{
	extern int set;
	set = 0;
}

void printsyscallsummary()
{
	int i,j;
	int flag = 1;
	char a[27][15] = {"freemem","chprio","getpid","getprio","gettime","kill","receive","recvclr","recvtim","resume","scount","sdelete","send","setdev","setnok","screate","signal","signaln","sleep","sleep10","sleep100","sleep1000","sreset","stacktrace","unsleep","wait"};
	for(i=0;i<NPROC;i++)
	{
		struct pentry *proc = &proctab[i];
		for(j=0;j<27;j++)
		{
			if(proc->freq[j] > 0)
			{
				if(flag == 1)
                		{
                        		flag = 0;
                        		printf("Process [pid:%d]\n",i);
                		}
				//printf("Process [pid:%d]\n",i);
				printf("\tSyscall: sys_%s, count: %d, average execution time: %d\n",a[j],proc->freq[j],(proc->avg[j])/(proc->freq[j]));	
			}		
		}
		flag = 1;
	}	
}
