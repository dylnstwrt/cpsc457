/**********************************************
 * Last Name:   Stewart
 * First Name:  Dylan
 * Student ID:  30024193
 * Course:      CPSC 457
 * Tutorial:    03
 * Assignment:  4
 * Question:    Q6
 *
 * File name: deadlock.cpp
 * compile with g++ -O2 -deadlock.cpp -o deadlock
 *********************************************/

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

#define REQUEST " -> "
#define ASSIGN " <- "

bool running = true;

bool isAssignment(std::string);
bool isRequest(std::string);
bool isEOS(std::string);

void getMembers(std::string, std::string&, std::string&);

/**
 * @brief nested while loops to check for user inputs, inner loop breaks on 
 * detection of both "#" or EOF, outer loop only breaks on EOF, indicating that
 * user is done with input.
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main (int argc, char* argv[]) {

    if (argc != 1) {
        std::cerr << "No args required, Aborting..." << "";
        exit(EXIT_FAILURE);
    }

    while(running) {

        bool reading = true;
        int processCount = 0;

        std::string line;
        //note: a lack of an element in either of the maps implies that it is a deadend/terminal node
        // TODO Change to outgoing list not incoming.
        std::map<std::string, std::vector<std::string>> graph; // key = node, map = outgoing edges
        std::vector<int> deadlockedProcesses; // for reading out

        while(reading)
        {   

            std::getline(std::cin, line);

            if (isEOS(line) || (std::cin.eof())) //EOF = Ctrl+D in UNIX
            {
                running = !(std::cin.eof());
                break;
            }

            std::string process;
            std::string resource;

            getMembers(line, process, resource);
            
            if(isRequest(line)) // -> 
            {
                if (graph.count(process) == 0)
                {
                    graph.emplace(process, std::vector<std::string>{resource});
                } else {                                
                   graph[process].emplace_back(resource);
                }
            }


            else if(isAssignment(line)) // <-
            {
                if (graph.count(resource) == 0) 
                {
                    graph.emplace(resource, std::vector<std::string>{process});
                } else {
                    graph[resource].emplace_back(process);
                }
            }
        }
        
        for (auto it = graph.begin(); it != graph.end(); it++) {
            for (int i = 0; i < it->second.size(); i++) {
                if (graph.count(it->second[i]) == 0) {
                    it->second.erase(it->second.begin() + i);
                }
            }
        }
        
        while(!graph.empty()){
            bool leafFound = true;
            
            while (leafFound) { // prune entries with empty lists until no more
                leafFound = false;
                for (auto it = graph.begin(); it != graph.end(); it++) {
                    if (it->second.empty()) {
                        graph.erase(it->first);
                        leafFound = true;
                        break;
                    }
                }
            }
            
            bool graphUpdated = false;

            for (auto itt = graph.begin(); itt != graph.end(); itt++) {
                for (int i = 0; i < itt->second.size(); i++){
                    if (graph.count(itt->second[i]) < 1){
                        itt->second.erase(itt->second.begin() + i);
                        graphUpdated = true;
                    }
                }
            }
            if (!graphUpdated) break;
        }
        
        
        
          for (auto it = graph.begin(); it != graph.end(); it++) {
            if (it->first.at(0) == 'P') deadlockedProcesses.emplace_back(stoi(it->first.substr(1)));
        } 
        
        std::sort(deadlockedProcesses.begin(), deadlockedProcesses.end());

        std::cout << "Deadlocked processes:";
        if (!(deadlockedProcesses.size() == 0)) {
            for (int i = 0; i < deadlockedProcesses.size(); i++)
                {std::cout << " " << deadlockedProcesses.at(i);}
            std::cout << "\n";
        } else {
            std::cout << " none" << "\n";
        }
    }

}

/**
 * @brief checks for presence of substring " -> " indicating a 
 * resource assignment edge
 * 
 * @param line 
 * @return true 
 * @return false 
 */
bool isAssignment(std::string line) 
{
    std::size_t pos = line.find(ASSIGN);
    return (pos != std::string::npos);
}

/**
 * @brief checks for presence of substring " <- " indicating a resource
 * request edge
 * 
 * @param line line from standard input
 * @return true 
 * @return false 
 */
bool isRequest(std::string line) 
{
    std::size_t pos = line.find(REQUEST);
    return (pos!= std::string::npos);
}

/**
 * @brief checks for presecne of "#" in string, indicating end of section for
 * the particular graph
 * 
 * @param line line taken from standard input
 * @return true 
 * @return false 
 */
bool isEOS(std::string line) 
{
    std::size_t pos = line.find("#");
    return (pos!=std::string::npos);
}

/**
 * @brief set the process string to "P<#>" and resource string to "R<#>" 
 * 
 * @param line full line taken from standard input
 * @param process the pointer to a string variable representing a process
 * @param resource the pointer to a string variable representing a resource
 */
void getMembers(std::string line, std::string &process, std::string &resource) 
{
    std::string delim = (isRequest(line)) ? REQUEST : ASSIGN;
    std::size_t pos = line.find(delim);

    process = "P" + line.substr(0, pos);
    resource = "R" + line.substr(pos+delim.length());

    /* std::cout << process << " : " << resource << "\n"; */
}