#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include <mpi/mpi.h>

#include "ff.h"
#include "ff_collectives.h"
#include "test_utils.h"

#define ROOT 0
#define TAG 1

int main(int argc, char ** argv){

    if (argc!=3) {
        printf("Usage: %s <count> <iterations>\n", argv[0]);
        exit(-1);
    }

    //printf("init\n");
    //MPI_Init(&argc, &argv);
    //Init the library
    ff_init(&argc, &argv);
    
    //printf("init ok\n");
    int rank = ff_get_rank();
    int commsize = ff_get_size();
    int count = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    int error=0;
    int gerror;
    int * data = (int *) malloc(sizeof(uint32_t)*count);
    if (rank==ROOT) for (int i=0; i<count; i++) data[i] = i;
    ff_schedule_h sched;

    //int gdb=0;
    //while (gdb==0){;}

    for (int i=0; i<iterations; i++){
        
        if (rank!=ROOT) memset(data, 0, sizeof(uint32_t)*count);
        else printf("iteration: %i\n", i);
        //create the schedule. NB. here the schedule is not yet posted
        FF_CHECK_FAIL(sched = ff_broadcast(data, count, sizeof(uint32_t), ROOT, TAG));
    
        //post the schedule
        ff_schedule_post(sched, 1);

        //wait for completion
        ff_schedule_wait(sched);
        ff_schedule_free(sched);
        if (rank!=ROOT){
            for (int i=0; i<count && !error; i++){
                if (data[i]!=i) error=1; 
            }
        }
    }

    //printf("Post-processing\n");
    FF_QUICK(ff_barrier(1000));

    sched = ff_reduce(&error, &gerror, 1, ROOT, 0, FF_MAX, FF_INT32_T);
    ff_schedule_post(sched, 1);
    ff_schedule_wait(sched);

    //MPI_Reduce(&error, &gerror, 1, MPI_INT, MPI_MAX, ROOT, MPI_COMM_WORLD);

    if (rank==ROOT) {
        if (gerror) printf("Failed\n");
        else printf("Completed\n");
    }

    ff_finalize();
    free(data);
}

