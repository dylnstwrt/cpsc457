/**********************************************
 * Last Name:   Stewart
 * First Name:  Dylan
 * Student ID:  30024193
 * Course:      CPSC 457
 * Tutorial:    03
 * Assignment:  2
 * Question:    Q3
 *
 * File name: scan.cpp
 * Compile with: g++ scan.cpp -o scan
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>


#define MAX_FNAME_SIZE 512
#define MAX_FILES 1024

// comparator for sort(), uses name to find file size
// and sort in descending order
bool compareSize( char array1[MAX_FNAME_SIZE], char array2[MAX_FNAME_SIZE]) {
  struct stat st1;
  struct stat st2;
  stat(array1, &st1);
  stat(array2, &st2);
  return ( st1.st_size >= st2.st_size);
}

int main( int argc, char * argv[]) {
  // handle command line arguments
  if(argc != 3) {
    fprintf(stderr, "Usage: scan <file extension> <# of files>\n");
    exit(-1);
  }
  // open 'find...'
  FILE * fp = popen( "./myFind", "r");
  if( fp == NULL) {
    perror("popen failed:");
    exit(-1);
  }
  // read in all filenames
  char buff[MAX_FNAME_SIZE];
  int nFiles = 0;
  char * files[MAX_FILES];

  char extension[MAX_FNAME_SIZE];

  // init cstring with convention of: .<extension>\n
  // used for matching files with the same extension
  strcpy(extension, ".");
  strcat(extension, argv[1]);
  strcat(extension, "\n");
  
  while(fgets(buff,MAX_FNAME_SIZE,fp)) {
    int len = strlen(buff) - 1;

    const char ch = '.';
    char *toCheck;
    
    // get .<extension>\n of the file in the directory
    toCheck = strrchr(buff, ch);

    int comp;
    // if extension matches, add file to array; iterate file count
    // break if number of files in array is equal to the number passed. 
    if ((comp = strcmp(extension, toCheck)) == 0) {
      files[nFiles] = strndup(buff,len);
      nFiles ++;
    if (nFiles >= atoi(argv[2])) break;
    }
  }

  fclose(fp);

  //sort array by size; large to small;
  std::sort(files, files+nFiles, compareSize);


  long long totalSize = 0;
  struct stat st;
  for(int i = 0 ; i < nFiles ; i ++ ) {
    if( 0 != stat(files[i],&st)) {
      perror("stat failed:");
      exit(-1);
    }
    // update totalsize with each files size, print out file name and file size
    totalSize += st.st_size;
    printf("%s %ld\n", files[i], st.st_size);
  }
  printf("Total size: %lld\n", totalSize);
  // clean up
  for(int i = 0; i < nFiles ; i ++ ) {
    free(files[i]);
  }
  // return success
  return 0;
}