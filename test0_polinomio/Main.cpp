#include <stdio.h>
#include <string>
#include <time.h>

#include <inttypes.h>   //To print uint64_t https://shengyu7697.github.io/cpp-printf-int64_t-uint64_t/

#include "common/hal.h"
#include "CommonLibrary.cpp"

#include <stdlib.h> /* srand, rand */
#include <unistd.h>
#include <arm_neon.h>

//uint64_t t0, t1, t_total;

static inline void hal_init_perfcounters(int do_reset, int enable_divider)
{

#ifdef cycles

#ifdef __aarch64__
    #elif __armv7l__

        // in general enable all counters (including cycle counter)
        int value = 1;

    // perform reset:  
    if (do_reset)
    {
        value |= 2;     // reset all counters to zero.
        value |= 4;     // reset cycle counter to zero.
    }

    if (enable_divider)
        value |= 8;     // enable "by 64" divider for CCNT.

    value |= 16;

    // program the performance-counter control-register:
    asm volatile ("MCR p15, 0, %0, c9, c12, 0\t\n" :: "r"(value));

    // enable all counters:  
    asm volatile ("MCR p15, 0, %0, c9, c12, 1\t\n" :: "r"(0x8000000f));

    // clear overflows:
    asm volatile ("MCR p15, 0, %0, c9, c12, 3\t\n" :: "r"(0x8000000f));

#endif

#endif
}



int main()
{
    // NOTE:
    //  1. If you want to measure nanoseconds, in the Makefile change MEASURETIME to "nanoseconds", i.e.:
    //      MEASURETIME = nanoseconds
    //  2. If you want to measure CPU Cycles, in the Makefile change MEASURETIME to "cycles", i.e.:
    //      MEASURETIME = cycles

   for(int k= 2; k<2048;k+=50){
   for(int h= 0; h<100;h++){

    hal_init_perfcounters(1, 1);

    unsigned long long startTime = 0;
    unsigned long long endTime = 0;
    unsigned long long totalTime = 0;

    startTime = get_timestamp();

    //Do something. This code is just an example
    /*for (int i = 0; i < 99999; i++) {
        int temp = (int)(i * i * i * i);
    }*/

	uint16_t arr1 []={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	uint16_t arr2 []={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};	
	
    int N =k+k-1;

    uint16_t res[N];   
    for (int i=0; i<N; i++){   
        res[i] = 0;
    }
	for (int i=0; i<k; i++){   
		for (int j=0; j<k; j++ ){
            if ( (i+j) > N ) { 
                }else{
                    res[i+j] +=  arr1[i]*arr2[j];
                }
        }
    }
	if(k==2){
		k=0;
	}
    endTime = get_timestamp();

    unsigned long long executionTime = ((unsigned long long)(endTime - startTime));
    totalTime = executionTime;
    
        printf("%llu", totalTime);

	   if(h==99){
			printf("\n");
	   }else{
			printf(",");
	   }	
   }
   }
    return 0;
}



