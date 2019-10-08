/**********************************************
 * Last Name:   Stewart
 * First Name:  Dylan
 * Student ID:  30024193
 * Course:      CPSC 457
 * Tutorial:    03
 * Assignment:  2
 * Question:    Q5
 *
 * File name: sum.cpp
 * Compile with: g++ sum.cpp -lpthread -o sum
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cmath> 
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

const int BUFFER_SIZE = 512;
const int MAX_INT_COUNT = 1000000;

long total = 0;
int integers[MAX_INT_COUNT];

// method invoked by each thread
void threadsum(int start, int end){
    long threadtotal = 0;
    for(int i = start; i < end; i++) {
        threadtotal += integers[i];
    }
    total += threadtotal;
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        cout << "Usage: <input file> <# of threads>" << endl;
        exit(EXIT_FAILURE);
    }
    
    //open stream to read in line by line
    fstream read;
    read.open(argv[1], ios::in);

    if (!read.is_open()) {
        cout << "Failed to open: " << argv[1] << endl; 
        exit(EXIT_FAILURE);
    }

    int lineCount = 0;

    // read and count all lines in the file
    string str;
    while (getline(read, str)) {
        integers[lineCount] = atoi(str.c_str());
        lineCount++;
    }

    // get number of threads
    // find modulo to determine how many entries each thread will add
    int threads = atoi(argv[2]);
    int mid = lineCount % threads;

    // for decimal precision for ceil and floor
    float quotient = ((float)lineCount / threads);

    int ceiling = (int)ceil(quotient);
    int flr = floor(quotient);

    // init thread array
    thread threadArr[threads];

    //ini size and index to determine each thread's bounds
    int size;
    int index = 0;

    for(int j = 0; j < threads; j++) {
        // set size depending on which number of thread
        size = j < mid ? ceiling : flr; 
        // create thread
        threadArr[j] = thread(threadsum, index, index+size);
        // update array index for next thread creation
        index += size;
        // print out thread number and ID
        cout << "Thread " << j+1 << ": " << threadArr[j].get_id() << endl;
    }
    // join all threads in the array
    for (int k = 0; k < threads; k++) {
        threadArr[k].join();
    }
    // print out final sum
    cout << "Sum = " << total << endl;
    return EXIT_SUCCESS;
}