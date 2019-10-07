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

using namespace std;

const int BUFFER_SIZE = 256;
const int MAX_INT_COUNT = 1000000;

int main(int argc, char *argv[]) {

    if (argc != 3) {
        cout << "Usage: <input file> <# of threads>" << endl;
        exit(EXIT_FAILURE);
    }

    int lineCount = 0;
    int toAdd;

    ifstream stream;
    stream.open(argv[1]);


    char integer[BUFFER_SIZE];
    int array[MAX_INT_COUNT];

      while (!stream.eof()) {
          memset(integer, 0, 256);
          stream.getline(integer, 256);
          toAdd = atoi(integer);
          array[lineCount] = toAdd;
          lineCount = lineCount + 1; 
      }
    stream.close();

    
    return EXIT_SUCCESS;
}