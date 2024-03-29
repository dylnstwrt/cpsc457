/**
 * @file fat.cpp
 * @author Pavol Federl, Modified by Dylan Stewart (UCID:30024193)
 * @brief Modified skeleton code for assignment 5, question 7, CPSC457 in Fall 2019.
 * @date 2019-12-02
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

typedef std::string SS;
typedef std::vector<SS> VS;

struct DEntry {
    SS fname = SS( 4096, 0);
    int size = 0;
    int ind = 0;
    bool tooManyBlocks = true;
    bool tooFewBlocks = false;
    bool hasCycle = true;
    bool sharesBlocks = false;
};

static SS join( const VS & toks, const SS & sep) {
    SS res;
    bool first = true;
    for( auto & t : toks) { res += (first ? "" : sep) + t; first = false;}
    return res;
}

int checkBlockAndCycle(int blockSize, DEntry & file, std::vector<int> & fat, std::unordered_multiset<int> & visited)
{
    int index = file.ind;
    int blocksUsed = 0;
    int dupes = 0;
    std::unordered_set<int> cycleDetect;

    auto temp = (double)file.size / (double)blockSize;
    int ceiling = std::ceil(temp);

    while( (index != -1) && (cycleDetect.find(index) == cycleDetect.end()) )
    {
        blocksUsed += 1;
        cycleDetect.insert(index);
        visited.insert(index);
        if (visited.count(index) > 1) 
        {
            file.sharesBlocks = true;
            ++dupes;
        }
        index = fat[index];
    }

    auto totalSize = blockSize * blocksUsed;

    if (cycleDetect.find(index) == cycleDetect.end())
    {
        file.hasCycle = false;
    }

    if (totalSize < file.size)
    {
        file.tooFewBlocks = true;
        file.tooManyBlocks = false;
    }
    else
    {
        if (blocksUsed <= ceiling)
        {
            file.tooManyBlocks = false;
        }
    }
    return dupes;
}

void checkShared(DEntry & file, std::vector<int> & fat, std::unordered_multiset<int> & visited)
{
    std::unordered_set<int> cycleDetect;
    int index = file.ind;
    while ((index != -1) && (cycleDetect.find(index) == cycleDetect.end()))
    {
        if (visited.count(index) > 1)
        {
            file.sharesBlocks = true;
            break;
        }
        else
        {
            cycleDetect.insert(index);
            index = fat[index];
        }
        
    }
}

// re-implement this function
//
// Parameters:
//   blockSize - contains block size as read in from input
//   files - array containing the entries as read in from input
//   fat - array representing the FAT as read in from input
// Return value:
//   the function should return the number of free blocks
//   also, for ever entry in the files[] array, you need to set the appropriate flags:
//      i.e. tooManyBlocks, tooFewBlocks, hasCycle and sharesBlocks
int checkConsistency( int blockSize, std::vector<DEntry> & files, std::vector<int> & fat)
{    
    std::unordered_multiset<int> visitedIndices;
    int dupes = 0;
    for (auto &file : files)
    {
        dupes += checkBlockAndCycle(blockSize, file, fat, visitedIndices);
    }
    for (auto &file : files)
    {
        if (file.sharesBlocks) continue;
        checkShared(file, fat, visitedIndices);
    }
    return (fat.size() - (visitedIndices.size() - dupes));
}

int main()
{
    try {
        // read in blockSize, nFiles, fatSize
        int blockSize, nFiles, fatSize;
        if( 3 != scanf( "%d %d %d", & blockSize, & nFiles, & fatSize))
            throw "cannot read blockSize, nFiles and fatSize";
        if( blockSize < 1 || blockSize > 1024) throw "bad block size";
        if( nFiles < 0 || nFiles > 50) throw "bad number of files";
        if( fatSize < 1 || fatSize > 200000) throw "bad FAT size";
        // read in the entries
        std::vector<DEntry> entries;
        for( int i = 0 ; i < nFiles ; i ++ ) {
            DEntry e;
            if( 3 != scanf( "%s %d %d", (char *) e.fname.c_str(), & e.ind, & e.size))
                throw "bad file entry";
            e.fname = e.fname.c_str();
            if( e.fname.size() < 1 || e.fname.size() > 16)
                throw "bad filename in file entry";
            if( e.ind < -1 || e.ind >= fatSize) throw "bad first block in fille entry";
            if( e.size < 0 || e.size > 1073741824) throw "bad file size in file entry";
            entries.push_back( e);
        }
        // read in the FAT
        std::vector<int> fat( fatSize);
        for( int i = 0 ; i < fatSize ; i ++ ) {
            if( 1 != scanf( "%d", & fat[i])) throw "could not read FAT entry";
            if( fat[i] < -1 || fat[i] >= fatSize) throw "bad FAT entry";
        }

        // run the consistency check
        int nFreeBlocks = checkConsistency( blockSize, entries, fat);

        // format the output
        size_t maxflen = 0;
        for( auto & e : entries ) maxflen = std::max( maxflen, e.fname.size());
        SS fmt = "  %" + std::to_string( maxflen) + "s: %s\n";

        printf( "Issues with files:\n");
        for( auto & e : entries ) {
            VS issues;
            if( e.tooFewBlocks) issues.push_back( "not enough blocks");
            if( e.tooManyBlocks) issues.push_back( "too many blocks");
            if( e.hasCycle) issues.push_back( "contains cycle");
            if( e.sharesBlocks) issues.push_back( "shares blocks");
            printf( fmt.c_str(), e.fname.c_str(), join( issues, ", ").c_str());
        }
        printf( "Number of free blocks: %d\n", nFreeBlocks);
    }
    catch( const char * err) {
        fprintf( stderr, "Error: %s\n", err);
    }
    catch( ... ) {
        fprintf( stderr, "Errro: unknown.\n");
    }
    return 0;
}
