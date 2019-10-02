

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string.h>

using namespace std;

void listCont(char name[256]);

int main(int argc, char *argv[]) {
    DIR *stream = opendir("./");
    struct dirent *info = NULL;
    while ((info = readdir(stream)) != NULL) {
        if (!(strncmp(info->d_name, ".", 1))) {
            continue;
        } else {
            cout << "./" << info->d_name << endl;
        }
    }   
}