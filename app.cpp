#include <iostream> 
#include <string.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>


int main() { 
    // Initialize time seed for the random integer. 
    srand(time(NULL));
    
    // Initialize array
    int arr[20];
    int start,end;
    int arrsize = sizeof(arr)/sizeof(int);
    int min;
    printf("array size: %d\n",arrsize);
    
    // Initialize pipe
    int fd[2];
    if (pipe(fd)==-1) {
        return 1;
    }

    // Fills array with random integers. 
    for (size_t i = 0; i < arrsize; i++){
        arr[i] = rand() % 1000;
        printf("%d\n", arr[i]);
    }

    int id = fork();
    if (id ==-1){
        return 2;
    }

    if (id==0) {
        // Child process
        start=10;
        end= 19;
        min = arr[10];
        printf("Child loop from index 10 to 19.\n");
    }
    else {
        // Parent process
        start= 0;
        end = 9;
        min = arr[0];
        printf("Parent loop from  index 0 to 9.\n");
    }
    
    for (int i = start;i <= end;i++){
        if (min > arr[i]){
            min = arr[i];
        }
    }
    
    printf("Calculated min: %d\n",min);
    
    if (id==0) {
        printf("Child's process id is  %d.\n",getpid());
        write(fd[1],&min,sizeof(min));
        close(fd[1]);
        }
        else{
            printf("Parent's process id is  %d.\n",getpid());
            close(fd[1]);
            int childMin;
            read(fd[0], &childMin,sizeof(int));
            close(fd[0]);
            printf("Child minimum is %d\n", childMin);
            printf("Parent minimum is %d\n", min);

            // Determines if parent or child minimum is smaller.
            if (childMin < min){
                min = childMin;
            }
            printf("Total Minimum is : %d\n",min);
            }
    
    return 0;
}