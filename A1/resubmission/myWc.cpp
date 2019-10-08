/**********************************************
 * Last Name:   Stewart
 * First Name:  Dylan
 * Student ID:  30024193
 * Course:      CPSC 457
 * Tutorial:    03
 * Assignment:  1
 * Question:    Q4
 *
 * File name: countLines.cpp
 * 
 * NOTE: Was previously submitted in Spring 2019 CPSC 457 by me
 * NOTE #2: Re-Submission
 *********************************************/

#include <unistd.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

const int BUFFER_SIZE = 1000000;


int main (int argc, char * const argv[])
{
  // get the file name from command line
  string filename;
  if (argc != 2) {
    cerr << "Usage: readFile <input file> " << endl;
    return -1;
  }
  else {
    filename = argv[1];
  }
  
  // open the file for reading
  int fd = open(filename.c_str(), O_RDONLY);
  if( fd < 0) {
    cerr << "Could not open file " << filename << "\n";
    exit(-1);
  }

  // initialize buffer for file to be read into, as well as the count of '\n'
  int count = 0;
  int bytesRead;
  char buf[BUFFER_SIZE];
  if ((bytesRead = read(fd, buf, BUFFER_SIZE)) >= 1){
      // iterate through each index of the buffer
      for (int i = 0; i < bytesRead; i++) {
          // check for presence of the new line escape character
          if ('\n' == buf[i]) count++;
      }
  }
  // close file and report results
  close(fd);
  cout << count << " " << filename << "\n";
  return 0;
}
