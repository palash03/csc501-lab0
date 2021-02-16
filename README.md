CSC501 Spring 2020

PA 0: Getting Acquainted with XINU

Due: January 21 2015, 10:00 pm

1. Objectives

The objectives of this introductory lab are to familiarize you with the process of compiling and running XINU, the tools involved, and the run-time environment and segment layout.

2. Lab setup guide

XINU is a small Unix-like operating system originally developed by Douglas Comer for instructional purposes at Purdue University. It is small enough so that we can understand it entirely within one semester. As part of lab assignment, we will re-implement or improve some apsects of XINU.
Step 1: Setting environment variables for lab assignments:

Get access to a customized VCL image -- XINU (CSC501) -- through the VCL facility
Step 2: Add a new entry into your /etc/hosts

	sudo sh -c "echo 127.0.0.1 `cs-status | head -1 | sed 's/://g'` >> /etc/hosts"
Step 3: Start a backend server at local

	sudo /bin/serial_server &
Step 4: Untar the XINU source files as follows:

Change to your home directory, if you are not already in it.

cd
Untar the XINU source by typing the following:

wget http://people.engr.ncsu.edu/gjin2/Classes/501/Spring2015/assignments/PA0/csc501-lab0.tgz
tar xzvf csc501-lab0.tgz
In your home directory, you will now have a directory named csc501-lab0. The subdirectories under this directory contain source code, header files, etc, for XINU. NOTE: the tar file name may be different from the above depending on the lab you are working on. Please refer to the lab handouts for the location of the tar file for the current lab.

Step 5: Building XINU

To compile the XINU kernel which will be downloaded and run on the backend machines, run "make" in the compile directory as follows: 
 
cd csc501-lab0/compile
make depend
make
This creates an OS image called 'xinu.elf' that will then be uploaded and run on the backend machines.
Step 6: Running XINU

The XINU code runs on backend machines. To see which of the backends are available for booting XINU, type: 
 
cs-status
This will show you who, if anyone, is logged onto each backend and how long they have been using it. To boot your copy of XINU on a backend, connect to a back-end by issuing the command:
cs-console
With no arguments cs-console will connect you to the first available backend. You may specify a backend by name (backend21 through backend100). Now download your copy of XINU by typing:
(control-@) OR (control-spacebar)

// esc to local command-mode 


(command-mode) ?        

// show a list of supported commands  


(command-mode) d 

// download command 


file: xinu.elf

// tell it to download 'xinu.elf' (assuming you are under csc501-lab0/compile)


(control-@) OR (control-spacebar)

// esc to local command-mode 


(command-mode) p        

// powercycle the backend  


XINU should boot with a "Hello World, Xinu lives!" message.

Typing (control-@) will always bring you back to '(command mode)' prompt. From here, you can quit by typing q. 
 
(control-@) OR (control-spacebar)

(command-mode) q        

// quit the backend  
3. References

The Intel manuals (Volume 1, Volume 2, Volume 3).
A brief guide on the 30386 architecture.
AT&T assembly information specific to the gnu assembler is available here as a wikibook.
Any man pages/manuals you discover that you need.
Note: The Intel document is hundreds of pages long and there is no need to print it. Please do not print it!

4. What to do

You will be using the csc501-lab0.tgz you have downloaded and compiled by following the lab setup guide. And you are asked to write several XINU functions that perform the following tasks:

long zfunction(long param)
Clear the 20th to 27th bits (count the bits from left to right) of the parameter "param" and shift it by 8 bits to the left, and then fill the right most bits with 0. For example, the input parameter 0xaabbccdd should generate a return value of 0xbbc00d00. You can assume that the size of long is 4 bytes. The code for this function should be entirely written in x86 assembly. You should not use inline assembly, (i.e., do not use asm(...)). To investigate the assembly code generated by the compiler, you can use the tool objdump -d <___.o> to disassemble an object file. The object files reside in the /compile directory within the main Xinu directory. You can also see some of the *.S files in the /sys directory for reference.

void printsegaddress()
Print the addresses indicating the end of the text, data, and BSS segments of the Xinu OS. Also print the 4-byte contents (in hexadecimal) preceding and after those addresses. This function can be written in C.

void printtos()
Print the address of the top of the run-time stack for whichever process you are currently in, right before and right after you get into the printos() printtos() function call. In addition, print the contents of upto six stack locations below the top of the stack (the four six or fewer items that have been the most recently pushed, if any). Remember that stack elements are 32 bits wide, and be careful to perform pointer arithmetic correctly. Also note that there are local variables and arguments on the stack, among other things. See the hints given for #4 below, especially on stacktrace.c and proc.h. Your function can be written entirely in C, or you can use in-line assembly if you prefer.

void printprocstks(int priority)
For each existing process with lower priority than the parameter, print the stack base, stack size, stacklimit, and stack pointer. Also, for each process, include the process name, the process id and the process priority.

To help you do this, please look into proc.h in the h/ directory. Note the proctab[] array that holds all processes. Also, note that the pesp member of the pentry structure holds the saved stack pointer. Therefore, the currently executing process has a stack pointer that is different from the value of this variable. In order to help you get the stack pointer of the currently executing process, carefully study the stacktrace.c file in the sys/ directory. The register %esp holds the current stack pointer. You can use in-line assembly(i.e., asm("...")) to do this part.

void printsyscalls()
Print the system calls which have been invoked for each process. This task is loosely based on the functionality of LTTng . There are 43 system calls declared. Please look into kernel.h in the h/ directory to see all declared system calls. However, not all of them are implemented in this XINU version. The implementation of the system calls are in the sys/ directory. You are asked to focus on the system calls in this list. 
Modifying those system calls such that they will be printed whenever they are invoked. You are asked to print the frequency (how many times each system call is invoked) of the system calls in the list for each process. In order to do this, you will need to modify the implementation of the system calls to trace them whenever they are invoked. 
You will also need to implement two other functions: 
void syscallsummary_start(): to start tracing the system calls. 
void syscallsummary_stop(): to stop tracing the system calls. 
In other words, these two functions determine the duration in which the system calls are traced. 
Implement this lab as a set of functions that can be called from main(). Each function should reside in a separate file in the sys directory, and should be incorporated into the Makefile. The files should be named after the functions they are implementing with C files having the .c extension and the assembly files having the .S extension. For example, the file that will hold void printsegaddress() should be named printsegaddress.c; and the file that will hold long zfunction(long param) should be named zfunction.S. You should put syscallsummary_start, syscallsummary_stop functions in the same file as printsyscallsummary printsyscalls function and name it as printsyscallsummary.c printsyscalls.c. If you require a header file, please name it lab0.h. Note: as you create new files, you may need to update the Makefile (located in the compile/directory) to configure it to compile your files correctly. Just look at what is done for the existing files (e.g., main.c) to see what you have to do.

5. Additional Questions

Write your answers to the following questions in a file named Lab0Answers.txt (in simple text).

Please place this file in the sys/ directory and turn it in, along with the above programming assignment.

Assuming the XINU text begins at address 0x0, draw a rough diagram of XINU's memory layout with addresses derived from your experimental measurements. Include the information you uncovered from running your version of printsegaddress() and printprocstks().
What is the difference in stack top address before and after calling printtos()? Draw a diagram to illustrate what are the contents of the items pushed into the stack between these two time points.
Which byte order is adopted in the host machine that we are using? How did you find out?
Briefly describe the mov, push, pusha, pop, and popa instructions in the x86.
In a stack frame, local variables are stored below the top of the stack. In task 3, does your result show all the local variables declared in your printtos function? If not, can you explain that? (hint: try to disable the compiler optimization by specifing -O0 in your Makefile)
Turn-in Instructions

Electronic turn-in instructions:

make sure your output is intuitive and clean---simplifying Grader's grading is always good.
go to the csc501-lab0/compile directory and do make clean.
create a subdirectory TMP under the directory csc501-lab0 and copy all the files you have modified/written, .S, .c, and .h files into the directory.
compress the csc501-lab0 directory into a tgz file and use Moodle's Submit Assignment facility. Please only upload one tgz file.
tar czf csc501-lab0.tgz csc501-lab0

You can write code in main.c to test your procedures, but please note that when we test your programs we will replace the main.c file! Therefore, do not put any functionality in the main.c file.

Also, ALL debugging output MUST be turned off before you submit your code.

Grading Policy

(10%) Source code can be compiled and the generated image is bootable. Please note that you will also get 0 point for the second part if your source code can not be compiled or can not generate a bootable image.
(75%) Each task rewards 15 points (losing points on minor problems)
(15%) Each additional question earns 3 points
Back to the CSC501 web page