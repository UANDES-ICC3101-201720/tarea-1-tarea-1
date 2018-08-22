#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "types.h"
#include "const.h"
#include "util.h"
#include <ctype.h>
#include <pthread.h>

float list[16];
int n = sizeof(list);
int target;
bool key_found = false;

// TODO: implement
void* serial_binsearch(void *params) {
    int low = 0, mid, high = n-1; // define the lowest, mid and highest positions
    while (low <= high) {
         mid = (low + high) / 2;
         if (list[mid] < target) {
            low = mid + 1;
        }
         else if (list[mid] > target) {
            high = mid - 1;
        }
        else if (list[mid] == target)  {
            key_found = true;
            break;
        }
     }
    
}

// TODO: implement
int max_threads = sysconf(_SC_NPROCESSORS_ONLN);
int part = 0;
void* parallel_binsearch(void *params) {
    int thread_part = part++;
    int low = thread_part * (n / max_threads); //each thread will check 1 / max_threads of the array
    int mid;
    int high =(thread_part + 1) * (n / max_threads);

    while (low <= high) {
        mid = (high - low) / 2 + low;
        if (list[mid] < target){
            low = mid + 1;
        }
        else if (list[mid] > target) {
            high = mid - 1;
        }
        else else if (list[mid] == target)  {
            key_found = true;
            break;
        }

    }
}

int main(int argc, char** argv) {

    /* TODO: parse arguments with getopt */
    int E_value;
    int T_value;
    int P_value;

    int index;
    int c;

    opterr = 0;

    if (argc == 1) {
        fprintf(stderr, "[binsearch] No arguments where given\n");
        exit(-2);
    }

    while( (c = getopt(argc, argv, "E:T:P:")) != -1) {
        switch(c) {
            case 'E':
                E_value = atoi(optarg);
                break;
            case 'T':
                T_value = atoi(optarg);
                break;
            case 'P':
                P_value = atoi(optarg);
                break;
            case '?':
                if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default: 
                abort();
        }

    }

    if (E_value < 1) {
        fprintf(stderr, "[binsearch] Invalid value for E flag\n");
    }
    else if (T_value < 3 || T_value > 9) {
        fprintf(stderr, "[binsearch] Invalid value for T flag\n");
    }
    else if (P_value < 0 || P_value > pow(10, T_value) - 1) {
        fprintf(stderr, "[binsearch] Invalid value for P flag\n"); 
     }
    for (index = optind; index < argc; index++)
        printf ("[binsearch] Non-option argument %s\n", argv[index]);
    
    /* TODO: start datagen here as a child process. */

    pid_t pid_datagen;
    pid_datagen = fork();
    if (pid_datagen == -1) {
        perror("[binsearch] Fork failed!");
        exit(EXIT_FAILURE);
    }
    else if (pid_datagen == 0) {
        printf("[binsearch] Datagen created as a child process\n");
        _exit(EXIT_SUCCESS);
    }


    /* TODO: move this time measurement to right before the execution of each binsearch algorithms
     * in your experiment code. It now stands here just for demonstrating time measurement. */
    clock_t cbegin = clock();

    printf("[binsearch] Starting up...\n");

    /* Get the number of CPU cores available */
    printf("[binsearch] Number of cores available: '%ld'\n", sysconf(_SC_NPROCESSORS_ONLN));

    /* TODO: implement code for your experiments using data provided by datagen and your
     * serial and parallel versions of binsearch.
     * */



    /* TODO: connect to datagen and ask for the necessary data in each experiment round.
     * Create a Unix domain socket with DSOCKET_PATH (see const.h).
     * Talk to datagen using the messages specified in the assignment description document.
     * Read the values generated by datagen from the socket and use them to run your
     * experiments
     * */

    /* Probe time elapsed. */
    clock_t cend = clock();

    // Time elapsed in miliseconds.
    double time_elapsed = ((double) (cend - cbegin) / CLOCKS_PER_SEC) * 1000;

    printf("Time elapsed '%lf' [ms].\n", time_elapsed);

    exit(EXIT_SUCCESS);
}