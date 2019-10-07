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

    if (argc != 2) {
        cout << "Usage: <input file> <# of threads>" << endl;
        exit(EXIT_FAILURE);
    }

    int lineCount = 0;

    ifstream stream;
    stream.open(argv[1]);

    char integer[BUFFER_SIZE];
    int array[MAX_INT_COUNT];

    stream.close();
    return EXIT_SUCCESS;
}