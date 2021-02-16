#include <stdio.h>

extern long end;
extern int etext,edata;

void printsegaddress()
{
	kprintf("void printsegaddress()\n");
	kprintf("\nCurrent: etext[0x%08X]=0x%08X, edata[0x%08X]=0x%08X, ebss[0x%08X]=0x%08X\n",(int)&etext,etext,(int)&edata,edata,&end,end);
    	kprintf("Preceding: etext[0x%08X]=0x%08X, edata[0x%08X]=0x%08X, ebss[0x%08X]=0x%08X\n",(int)(&etext-1),(int)(*(&etext-1)),(&edata-1),(int)(*(&edata-1)),(&end-1),(*(&end-1)));
    	kprintf("After: etext[0x%08X]=0x%08X, edata[0x%08X]=0x%08X, ebss[0x%08X]=0x%08X\n\n",(int)&etext+1,(int)(*(&etext+1)),(&edata+1),(int)(*(&edata+1)),(&end+1),(*(&end+1)));
}

