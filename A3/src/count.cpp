/**********************************************
 * Last Name:   Stewart
 * First Name:  Dylan
 * Student ID:  30024193
 * Course:      CPSC 457
 * Tutorial:    03
 * Assignment:  3
 * Question:    Q2
 *
 * File name: count.cpp
 * Compile with:  g++ count.c -O2 -lpthread -o count
 *********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <thread>

void divCheck(int64_t, int64_t, int64_t, int64_t);

using namespace std;
volatile bool notPrime = false;


/// primality test, if n is prime, return 1, else return 0
int isPrime(int64_t n)
{
     if( n <= 1) return 0; // small numbers are not primes
     if( n <= 3) return 1; // 2 and 3 are prime
     if( n % 2 == 0 || n % 3 == 0) return 0; // multiples of 2 and 3 are not primes
     int64_t i = 5;
     int64_t max = sqrt(n);
     while( i <= max) {
         if (n % i == 0 || n % (i+2) == 0) return 0;
         i += 6;
     }
     return 1;
}

void divCheck(int64_t start, int64_t end, int64_t n, int64_t max) {
    int64_t i = start;
    while ((i % 2 == 0) || (i % 3 == 0)) { // might have to be good enough
        i++;
    }
    while ((i <= end) && (i <= max)) {
        if (notPrime) return;
        if (n % i == 0 || n % (i+2) == 0) {
            notPrime = true;
            return;
        }
        i += 6;
    }
}

/* 
    Algorithm from isPrime() remains the same, with the exception that if the while
    loop is required, the range is split into equal sized groups and mentioned
    groups will be divided amongst the nThreads threads; theorhetically providing
    nThread multiple speed up to the prime number finding algorithm.

    Uses a global flag to signal when a thread has found a number which divides
    n, signalling that it it not a prime number.

    Issues with edgecases, specifically in medium.txt; ran out of time;
    nThread 3,  8,  and 16 results in counts off by 1 or 2;
 */

int isPrimeParallel(int64_t n, int64_t nThreads) {
    thread threads[nThreads];

    if( n <= 1) return 0; // small numbers are not primes
    if( n <= 3) return 1; // 2 and 3 are prime
    if( n % 2 == 0 || n % 3 == 0) return 0; // multiples of 2 and 3 are not primes

    int64_t i = 5;
    int64_t max = sqrt(n);

    int64_t size = max / nThreads;

    // issues here, divCheck will miss cases where n is divisible, inflating
    // the prime count incorrectly.
    for (int64_t j = 0; j < nThreads; j++) {
        threads[j] = thread(divCheck, i, i+size, n, max);
        i = i+size;
    }

    for(int64_t k = 0; k < nThreads; k++) {
        threads[k].join();
    }

    if (notPrime) {
        return 0;
    } else {
        return 1;
    }
}

int main( int argc, char ** argv)
{
    /// parse command line arguments
    int nThreads = 1;
    if( argc != 1 && argc != 2) {
        printf("Uasge: countPrimes [nThreads]\n");
        exit(-1);
    }
    if( argc == 2) nThreads = atoi( argv[1]);

    /// handle invalid arguments
    if( nThreads < 1 || nThreads > 256) {
        printf("Bad arguments. 1 <= nThreads <= 256!\n");
    }

    /// count the primes
    printf("Counting primes using %d thread%s.\n",
           nThreads, nThreads == 1 ? "" : "s");
    int64_t count = 0;
    while( 1) {
        int64_t num;
        if( 1 != scanf("%ld", & num)) break;
        if( isPrimeParallel(num, nThreads)) count ++;
        notPrime = false;
    }

    /// report results
    printf("Found %ld primes.\n", count);

    return 0;
}

