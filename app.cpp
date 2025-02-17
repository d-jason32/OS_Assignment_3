/*
Write a C++ program that creates an array of 20 elements. #
Fill the array elements by using the random number generator. #
Create a child process and find the minimum number in the second half of the array. 
Parent process will find the minimum number in the first half of the array. 
You must use the pipe to pass the minimum of the child to the parent process. 
Display the minimum numbers found in each process and their processor ids and finally the minimum number of the array.*/

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
    srand(time(NULL));
    // Initialize array
    int arr[20];
    int start,end;
    int arrsize = sizeof(arr)/sizeof(int);
    int min;
    printf("array size: %d\n",arrsize);
    
    int fd[2];
    if (pipe(fd)==-1) {
        return 1;
    }

    // Fills array with random integers. 
    for (size_t i = 0; i < arrsize; i++)
    {
        arr[i] = rand() % 1000;
        printf("%d\n", arr[i]);
    }

    int id = fork();
    if (id ==-1){
        return 2;
    }

    if (id==0) {
        start=11;
        end= 20;
        min = arr[11];
        printf("child loop from 11 to 20 \n");
    }
    else {
        start= 0;
        end = 10;
        min = arr[0];
        printf("parent loop from  0 to 10 \n");
     }
    
    
    
    
    int i;
    for (i=start;i<end;i++){
        if (min > arr[i]){
            min = arr[i];
        }
    }
    
    printf("calculated min: %d\n",min);
    
    if (id==0) {
        printf("Child's process id is  %d\n",getpid());
        write(fd[1],&min,sizeof(min));
        close(fd[1]);
        }
        else{
            printf("Parent's process id is  %d\n",getpid());
            close(fd[1]);
            int childMin;
            read(fd[0], &childMin,sizeof(int));
            close(fd[0]);
            if (childMin < min){
                min = childMin;
            }
            printf("Total Minimum is : %d\n",min);
            }
    
    return 0;
    }