# multithreaded_primes
A multithreaded prime number generator.

Compile with: gcc -g -Wall multithread_primes.c -o multithread_primes -lm -pthread

This simple program generates an array of prime numbers.
Run the program with: ./multithread_primes [n]

This will calculate the prime numbers between 2 and n.

Right now this is very inefficient. It simply runs through
all numbers less than the square root of n, and zeroes out
their multiples.

In the future, I'd like to find a way to make this more efficient
than the serial version of this program.
