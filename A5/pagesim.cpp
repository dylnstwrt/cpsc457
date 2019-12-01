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
#include <string>
#include <vector>
#include <stack>

std::string optimal(int, std::vector<int>);
std::string lru(int, std::vector<int>);
std::string clockAlg(int, std::vector<int>);

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        std::cerr << "Usage: pagesim <available frames>\n";
        exit(-1);
    }
    
    int frames = atoi(argv[1]); 

        std::vector<int> reference;
        int pagenum;

        while(true)
        {
            if (std::scanf("%d", &pagenum) != 1) break;
            reference.push_back(pagenum);
        }

        std::cout << optimal(frames, reference);
        std::cout << lru(frames, reference);
        std::cout << clockAlg(frames,reference) << "\n";
    //}
    return(0);
}

/**
 * @brief 
 * 
 * @param maxFrames 
 * @param reference 
 * @return std::string 
 */
std::string optimal(int maxFrames, std::vector<int> reference)
{   
    std::string toWrite;
    std::vector<int> frames(maxFrames, -1);
    int faults = 0;
    
    while(!reference.empty())
    {
        int toInsert = reference[0];
        
        if (std::find(frames.begin(), frames.end(), toInsert) != frames.end())
        {
            reference.erase(reference.begin());
            continue;
        }
        else
        {   
            int indexToReplace = -1;
            int distance = -1;
            
            for (int i = 0; i < frames.size(); i++)
            {
                if (frames[i] == -1)
                {
                    indexToReplace = i;
                    break;
                }
            }
            
            if(indexToReplace == -1)
            {
                for (int i = 0; i < frames.size(); i++)
                {
                    if (std::find(reference.begin(), reference.end(), frames[i]) == reference.end())
                    {
                        indexToReplace = i;
                        break;
                    }
                }
            }
            
            if(indexToReplace == -1)
            {
                for (int i = 0; i < frames.size(); i++)
                {
                    auto iter = std::find(reference.begin(), reference.end(), frames[i]);
                    auto dist = std::distance(reference.begin(), iter);
                    
                    if (dist > distance)
                    {
                        distance = dist;
                        indexToReplace = i;
                    }
                }
            }
            
            frames[indexToReplace] = toInsert;
            reference.erase(reference.begin());
            ++faults;
        }
    }
    
    toWrite += "\nOptimal:\n\t- frames:";
    for (auto page : frames)
    {
        toWrite += " " + std::to_string(page);
    }
    toWrite += "\n\t- page faults: " + std::to_string(faults);
    return toWrite;
}

/**
 * @brief TODO counter based version of the lru implementation.
 * 
 * @param maxFrames 
 * @param reference 
 * @return std::string 
 */
std::string lru(int maxFrames, std::vector<int> reference)
{
    std::string toWrite;
    std::vector<int> frames(maxFrames, -1);
    std::deque<int>  leastUsed;
    int faults = 0;
    
    while(!reference.empty())
    {
        int toInsert = reference[0];
        
        /* already exists in frames*/
        if (std::find(frames.begin(), frames.end(), toInsert) != frames.end())
        {
            reference.erase(reference.begin());
            auto toRemove = std::find(leastUsed.begin(), leastUsed.end(), toInsert);
            leastUsed.erase(toRemove);
            leastUsed.push_back(toInsert);
            continue;
        }
        else
        {   
            int indexToReplace = -1;
            
            /*has empty frame*/
            for (int i = 0; i < frames.size(); i++)
            {
                if (frames[i] == -1)
                {
                    indexToReplace = i;
                    break;
                }
            }
            
            /* pop stack for page to replace in frames*/
            if (indexToReplace == -1)
            {
                auto page = leastUsed.front();
                leastUsed.pop_front();
                
                auto iter = std::find(frames.begin(), frames.end(), page);
                indexToReplace = std::distance(frames.begin(), iter);
                
            }
            
            leastUsed.push_back(toInsert);
            frames[indexToReplace] = toInsert;
            reference.erase(reference.begin());
            ++faults;
        }
    }
    
    toWrite += "\nLRU:\n\t- frames:";
    for (auto page : frames)
    {
        toWrite += " " + std::to_string(page);
    }
    toWrite += "\n\t- page faults: " + std::to_string(faults);
    return toWrite;
}

std::string clockAlg(int maxFrames, std::vector<int> reference)
{
    std::string toWrite;
    std::vector<int> frames(maxFrames, -1);
    int faults = 0;
    
    while(!reference.empty())
    {
        int toInsert = reference[0];
        
        if (std::find(frames.begin(), frames.end(), toInsert) != frames.end())
        {
            reference.erase(reference.begin());
            continue;
        }
        else
        {   
            int indexToReplace = -1;
            
            for (int i = 0; i < frames.size(); i++)
            {
                if (frames[i] == -1)
                {
                    indexToReplace = i;
                    break;
                }
            }
            
            
            
            
            frames[indexToReplace] = toInsert;
            reference.erase(reference.begin());
            ++faults;
        }
    }
    
    toWrite += "\nOptimal:\n\t- frames:";
    for (auto page : frames)
    {
        toWrite += " " + std::to_string(page);
    }
    toWrite += "\n\t- page faults: " + std::to_string(faults);
    return toWrite;
}