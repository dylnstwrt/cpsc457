/**********************************************
 * Last Name:   Stewart
 * First Name:  Dylan
 * Student ID:  30024193
 * Course:      CPSC 457
 * Tutorial:    03
 * Assignment:  2
 * Question:    Q2
 *
 * File name: myFind.cpp
 *********************************************/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string.h>

using namespace std;

void myFind(string name);

int main(int argc, char *argv[]) {
         myFind(".");
}


void myFind(string name) {
    // initialize stream and dirent struct; open stream using parameter
    DIR *stream = NULL;
    struct dirent *info = NULL;
    stream = opendir(name.c_str());

    //if stream is valid, populate dirent struct
    if (stream != NULL) {
        info = readdir(stream);
        // for all valid files in the directory
        while( info != NULL) { 
            // if link to current/prev directory; skip
            if ((string(info->d_name) == ".") || (string(info->d_name)== "..")) {
                info = readdir(stream);
                continue;
            }
            // concat name with / and the current selected item in the directory
            string fullpath = name + "/" + info->d_name;
            // using d_type flag; check if current item is a directory and recurse if true
            if (info->d_type == DT_DIR) {
                myFind(fullpath);
            } else {
                // note to self, find -type f shows all files, not just regular ones like the DT_REG flag shows.
                cout << fullpath << endl;
            }
            // iterate to next item in directory
            info = readdir(stream);
        }
    }
    // close stream
    closedir(stream);
}