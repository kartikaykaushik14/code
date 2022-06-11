C Program to create a shared memory where child process is the producer and the parent process is a consumer. The shared memory is a circular queue that has a dynamic size and has in and out pointers to help evaluate if the shared buffer is full or empty. The consumer does not wait for the child process to complete but instead keeps consuming as soon as data is added to the buffer.

Command to compile - gcc Shared_Memory.c -o Shared_Memory.out -lrt
Command to run - ./Shared_Memory.out 4