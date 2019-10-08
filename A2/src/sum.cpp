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
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

long threadSum = 0;

const int BUFFER_SIZE = 512;
const int MAX_INT_COUNT = 1000000;

int main(int argc, char *argv[]) {

    if (argc != 3) {
        cout << "Usage: <input file> <# of threads>" << endl;
        exit(EXIT_FAILURE);
    }
    
    fstream read;
    read.open(argv[1], ios::in);

    int lineCount = 0;

    int integers[MAX_INT_COUNT];

    string str;
    while (getline(read, str)) {
        integers[lineCount] = atoi(str.c_str());
        //cout << integers[lineCount] << endl;
        lineCount++;
    }
    
    return EXIT_SUCCESS;
}