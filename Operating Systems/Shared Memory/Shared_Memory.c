#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
        pid_t pid;
	
	// If no argument for n is provided in input throw error
	if(argc != 2){
		fprintf(stderr, "An integer parameter is required\n");
		return 1;
	}

	int n = atoi(argv[1]);
	
	// If negative argument for n is provided in input throw error
	if(n < 0){
		fprintf(stderr, "An integer >=0	is required\n");
		return 1;
	}
	
	void  *ptr;

	const char* name = "buffer";
        int shm_fd;
	
        shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	
	// We define a shared memory with two integers - in pointer and out pointer and an n sized float
	// This buffer is a circular buffer and hence (n-1) elements can be stored in it.
	int buf_size = n*sizeof(float)+2*sizeof(int);
        ftruncate(shm_fd, buf_size);
	
	// If failed to create a shared memory
	if (shm_fd == -1) {
        	fprintf(stderr, "shmget failed\n");
        	fflush(stdout);
        	exit(EXIT_FAILURE);
   	}

	pid = fork();
	// If failed to create a child
        if(pid < 0){
                /* Error occured */
                fprintf(stderr, "Fork Failed");
                return 1;
        }
        else if(pid == 0){
		/* Child Process */
		ptr = mmap(0, buf_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);	
		
		// The shared memory is split such that 
		// ptr to ptr+n-1 is the buffer
		// ptr+n is in pointer
		int* in_p = (int*)ptr + n;
		
		// ptr+n+1 is out pointer
		int* out_p = (int*)ptr + n + 1;

		*in_p = 0;
		*out_p = 0;

		for(int y = 0; y < n; y++){
			float z = 0.25*y*y;
			
			// Wait if buffer is full
			while ((*in_p + 1) % n  == *out_p);
			
			// Store data to buffer whose index is in pointer
			*((float*)ptr + *in_p) = z;

			// Increment in pointer in circular manner	
			*in_p = (*in_p + 1) % n;
			
			//Wait for random interval of time
			srand(time(0));
			float randomIntval = ((float)(rand() % 5000))/1000;
			printf("Sleep for %f secs\n",randomIntval);
			fflush(stdout);
			sleep(randomIntval);	
		}	
        }
        else{
		/* Parent Process */

		// The below 3 lines of code could be implemented before calling the fork to child 
		// and the same values could be inherited by the child process. I have defined it twice
		// to enable parent and child to have different permissions though in this question they
		// need the same permissions.

		ptr = mmap(0, buf_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
		int* in_p = (int*)ptr + n;
                int* out_p = (int*)ptr + n + 1;

		for(int y = 0; y < n; y++){
			
			// Wait if buffer is empty
			while (*in_p == * out_p);
			printf("Output Element %d = %f\n", y+1, *((float*)ptr + *out_p));
                	fflush(stdout);
			
			// Increment out pointer in circular manner  
			*out_p = (*out_p + 1) % n;
		}
		
        }
	shm_unlink(name);
        return 0;
}
