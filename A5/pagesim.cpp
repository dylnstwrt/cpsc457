/**
 * @author Dylan Stewart
 * 
 **/

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>


int main(int argc, char *argv[]) {
    if (argc != 2) 
    {
        std::cerr << "Usage: pagesim <available frames>\n";
    }
    
    bool reading = true;
    int frames = atoi(argv[1]);
    
    while (reading)
    {
        std::vector<int> frames;
        int faults;
        
        std::string line;
    }
}