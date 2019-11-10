/**********************************************
 * Last Name:   Stewart
 * First Name:  Dylan
 * Student ID:  30024193
 * Course:      CPSC 457
 * Tutorial:    03
 * Assignment:  4
 * Question:    Q4
 *
 * File name: Scheduler.cpp
 *********************************************/
#include <iostream>
#include <string>
#include <queue>
#include <deque>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>

/* 
#include <bits/stdc++.h>
 */

using namespace std;

// comparator for priority queue in SJF for insertion of elements depending
// on remaining burst size. 
struct burstCompare
{
    bool operator()(pair<int, int> lhs, pair<int, int> rhs)
    {
        return lhs.second > rhs.second;
    }
};

void SJF(vector<int> arrivals, vector<int> bursts)
{
    int time = 0;
    vector<int> completed;
    vector<int> timeWaiting(arrivals.size(), 0);
    int processCount = arrivals.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, burstCompare> waiting;

    cout << "Time ";
    for (int i = 0; i < processCount; i++)
    {
        cout << "P" << i << " ";
    }
    cout << endl
         << "------------------------------------------------------------" << endl;

    while (true)
    {

        cout << right << setw(3) << time << "  ";
        // check if processes have arrive, place in priority queue if they have
        for (int i = 0; i < processCount; i++)
        {
            if (arrivals.at(i) == time)
            {
                // pair: PID, remaining bursts
                pair<int, int> toPush(i, bursts.at(i));
                waiting.push(toPush);
            }
        }

        // if processes in queue, execute them
        if (!waiting.empty())
        {
            pair<int, int> toExecute(waiting.top());
            waiting.pop();

            for (int i = 0; i < processCount; i++)
            {
                bool complete = (find(completed.begin(), completed.end(), i) != completed.end());
                if (i == toExecute.first)
                {
                    cout << right << setw(2) << "#";
                }
                else if ((arrivals.at(i) <= time) && (!complete))
                {
                    cout << right << setw(2) << ".";
                    timeWaiting.at(i)++;
                }
                else
                {
                    cout << right << setw(2) << " ";
                }
                cout << " ";
            }

            toExecute.second = toExecute.second - 1;
            if (toExecute.second != 0)
            {
                waiting.push(toExecute);
            }
            else
            {
                completed.push_back(toExecute.first);
            }
        }

        cout << endl;
        if (completed.size() == processCount)
            break;
        time++;
    }

    cout << "------------------------------------------------------------" << endl;
    double avg = 0;
    for (int i = 0; i < timeWaiting.size(); i++)
    {
        printf("P%i waited %i.000 sec.\n", i, timeWaiting.at(i));
        avg += timeWaiting.at(i);
    }
    avg = avg / timeWaiting.size();
    printf("Average waiting time = %.3f sec.\n", avg);
}

void RR(vector<int> arrivals, vector<int> bursts, int quantum)
{
    int time = 0;
    int succCount = 0;
    vector<int> completed (0);
    vector<int> timeWaiting(arrivals.size(), 0);
    int processCount = arrivals.size();
    deque<pair<int, int>> waiting;

    cout << "Time ";
    for (int i = 0; i < processCount; i++)
    {
        cout << "P" << i << " ";
    }
    cout << endl
         << "------------------------------------------------------------" << endl;

    while (true)
    {
        cout << right << setw(3) << time << "  ";
         for (int i = 0; i < processCount; i++)
        {
            if (arrivals.at(i) == time)
            {
                // pair: PID, remaining bursts
                pair<int, int> toPush(i, bursts.at(i));
                waiting.push_back(toPush);
            }
        }

        if (!waiting.empty()) 
        {
            pair<int,int> toExecute(waiting.front());
            waiting.pop_front();

            for (int i = 0; i < processCount; i++) {
                bool complete = (find(completed.begin(), completed.end(), i) != completed.end());
                if (i == toExecute.first) {
                    cout << right << setw(2) << "#";
                    toExecute.second--;
                    succCount++;
                } else if ((arrivals.at(i) <= time) && (!complete)) {
                    cout << right << setw(2) << ".";
                    timeWaiting.at(i)++;
                } else {
                    cout << right << setw(2) << " ";
                }
                cout << " ";
            }

            if(toExecute.second == 0) {
                succCount = 0;
                completed.push_back(toExecute.first);
            } else if (succCount == quantum) {
                waiting.push_back(toExecute);
                succCount = 0;
            } else {
                waiting.push_front(toExecute);
            }
        }
        cout << endl;
        if (completed.size() == processCount)
            break;
        time+=1;
    }

    cout << "------------------------------------------------------------" << endl;
    double avg = 0;
    for (int i = 0; i < timeWaiting.size(); i++)
    {
        printf("P%i waited %i.000 sec.\n", i, timeWaiting.at(i));
        avg += timeWaiting.at(i);
    }
    avg = avg / timeWaiting.size();
    printf("Average waiting time = %.3f sec.\n", avg);
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cerr << "Usage: "
             << "scheduler <RR/SJF> <Quantum for RR>" << endl;
        exit(1);
    }

    string fileName(argv[1]);
    string algorithm(argv[2]);

    if ((algorithm.compare("RR") != 0) && (algorithm.compare("SJF") != 0))
    {
        cerr << "Invalid Algorithm" << endl;
        exit(1);
    }

    if ((algorithm.compare("RR") == 0) && (argc != 4))
    {
        cerr << "Quantum Required for RR" << endl;
        exit(1);
    }
    else if ((algorithm.compare("SJF") == 0) && (argc == 4))
    {
        cerr << "No quantum required for SJF" << endl;
        exit(1);
    }

    string line;
    ifstream myFile(fileName);
    vector<int> arrivals;
    vector<int> bursts;

    if (!myFile.is_open())
    {
        cout << "Unable to open file" << endl;
        exit(-1);
    }

    int processCount = 0;

    while (getline(myFile, line))
    {

        processCount++;
        stringstream splitter(line);
        string temp;

        for (int i = 0; i < 2; i++)
        {
            getline(splitter, temp, ' ');
            if (i == 0)
            {
                arrivals.push_back(stoi(temp));
            }
            else
            {
                bursts.push_back(stoi(temp));
            }
        }
    }

    myFile.close();

    if (algorithm.compare("SJF") == 0)
    {
        SJF(arrivals, bursts);
    }

    if (algorithm.compare("RR") == 0)
    {
        RR(arrivals, bursts, atoi(argv[3]));
    }
}