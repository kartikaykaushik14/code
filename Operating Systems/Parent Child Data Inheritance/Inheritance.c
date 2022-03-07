#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

	pid_t pid, parentId;
	parentId = getpid();
	pid = fork();

	if(pid < 0){
		/* Error occured */
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if(pid == 0){
		/* Child Process */
		printf("Child Process: Process ID of parent process= %d\n", parentId);
	}
	else{
		/* Parent Process */
		wait(NULL);
		printf("Parent Process: Process ID = %d\n", getpid());
	}
	return 0;
}

