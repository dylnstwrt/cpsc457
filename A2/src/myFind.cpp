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
    DIR *stream = NULL;
    struct dirent *info = NULL;
    stream = opendir(name.c_str());

    if (stream != NULL) {
        info = readdir(stream);
        while( info != NULL) {
            if ((string(info->d_name) == ".") || (string(info->d_name)== "..")) {
                info = readdir(stream);
                continue;
            }
            string fullpath = name + "/" + info->d_name;
            if (info->d_type == DT_DIR) {
                myFind(fullpath);
            } else {
                cout << fullpath << endl;
            }
            info = readdir(stream);
        }
    }
    closedir(stream);
}