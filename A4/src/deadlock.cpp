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
#include <vector>

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
        std::cerr << "No args required, Aborting..." << std::endl;
        exit(EXIT_FAILURE);
    }

    while(running) {

        bool reading = true;
        std::string line;
        std::unordered_map<std::string, std::pair<bool, std::vector<int>>> graph; // might need to tweak for optimization

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
            
            if(isRequest(line))
            {
                
            }


            else if(isAssignment(line)) 
            {
                
            }

        }

        // deconstruct graph, check each process for presence of cycle
        // use a toposort?

    }

}

/**
 * @brief checks for presence of substring " -> " indicating a 
 * resource request edge
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
 * allocation edge
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

    std::cout << process << " : " << resource << std::endl;
}