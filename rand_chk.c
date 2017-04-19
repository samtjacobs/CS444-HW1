#include <stdio.h>
#include <string.h>

unsigned int use_rdrand()
{
    unsigned int to_return=0;
	__asm__ __volatile__(
	                     "rdrand %0;"
	                     : "=r"(to_return)
	                     );
	return to_return;
}

int main(int argc, char **argv)
{

	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;

	char vendor[13];
	
	eax = 0x01;

	__asm__ __volatile__(
	                     "cpuid;"
	                     : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
	                     : "a"(eax)
	                     );
	
	if(ecx & 0x40000000){
		//use rdrand
        printf("rdrand asm found\n");
        printf("Random: %u\n", (int)use_rdrand());
	}
	else{
		//use mt19937
        printf("rdrand not found\n");
	}

	return 0;
}
