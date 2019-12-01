/**
 * @file pagesim.cpp
 * @author Dylan Stewart (UCID:30024193)
 * @brief 
 * @date 2019-11-30
 * 
 * @copyright Copyright (c) 2019
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

std::string optimal(int, std::vector<int>);

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        std::cerr << "Usage: pagesim <available frames>\n";
        exit(-1);
    }
    
    bool reading = true;
    int frames = atoi(argv[1]); 

    while (reading)
    {
        std::vector<int> reference;
        int pagenum;

        while(true)
        {
            if (std::scanf("%ld", &pagenum) != 1) break;
            reference.push_back(pagenum);
        }

        std::cout << optimal(frames, reference) << "\n";
    }
    return(0);
}

std::string optimal(int maxFrames, std::vector<int> reference)
{   
    int faults = 0;
    std::set<int> frames;
    for (int i = 0; i < reference.size(); i++)
    {
        int toInsert = reference[i];
        if ((frames.size() < maxFrames) || (frames.find(toInsert) != frames.end()))
        {
           auto checkPair = frames.insert(toInsert);
           if (checkPair.second) ++faults;
        }
        else
        {
            /* look ahead in reference*/
            std::vector<int> pages;
            for (auto x : frames) pages.push_back(x);
            while (pages.size() != 1)
            {
                
                // what if two frames are no longer referenced? iterator will equal end(); break tie how?
                auto iterator = std::find_first_of(reference.begin()+i, reference.end(), pages.begin(), pages.end());
                auto index = std::distance(reference.begin(), iterator);

                pages.erase(std::find(pages.begin(), pages.end(), reference[index]));

            }
            int toRemove = pages[0];
            frames.erase(toRemove);
            frames.emplace(toInsert);
            ++faults;
        }
    }
}