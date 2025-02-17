/*
Write a C++ program that creates an array of 20 elements. / 
Fill the array elements by using the random number generator. / 
Create a child process and find the minimum number in the second half of the array. 
Parent process will find the minimum number in the first half of the array. 
You must use the pipe to pass the minimum of the child to the parent process. 
Display the minimum numbers found in each process and their processor ids and finally the minimum number of the array.*/

#include <iostream> 
#include <cstdlib>

int main() { 
    std::cout << "Hello, World!" << std::endl; 

    // Initialize array
    int arr[20];
    int arrsize = sizeof(arr)/sizeof(int);
    
    // Fills array with random integers. 
    for (size_t i = 0; i < arrsize; i++)
    {
        arr[i] = rand() % 1000;
        std::cout << arr[i] << std::endl;
    }


    
    
    return 0; }