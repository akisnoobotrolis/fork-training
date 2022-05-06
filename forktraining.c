

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
int pid1, pid2,pid3,pid4,pid5,pid6;
int w1,w2,w3,w0;
int fd[2],n;
char message[100];
char *line="Hello from your child \n";
pipe(fd);
pid1=fork();
if (pid1==0)
	{	
	pid3=fork();
	if (pid3>0){
		printf("i am p1 with pid %d and my parents id is %d\n",getpid(),getppid());
		close(fd[1]);
		n=read(fd[0],message,sizeof(message));
		write(1,message,n);
		close(fd[0]);
	}
	else if(pid3==0){
		close(fd[0]);
		write(fd[1],line,strlen(line)+1);
		close(fd[1]);
		printf("i am p3 with pid %d and my parents id is %d\n",getpid(),getppid());
	}
}
else{
	pid2=fork();
	if (pid2==0)
		{	
		/*
		int n;
		printf("give n:");
		scanf("%d",&n);
	
		for (int i = 0; i < n; ++i)
		{
		if (fork()==0)
			{
				printf("i am child proccess %d with pid %d and ppid %d \n",i,getpid(),getppid());
				exit(0);
			}
		}
		for (int i = 0; i < n; ++i)
		{
			wait(NULL);
		}
		*/
		pid4=fork();
		if (pid4>0){	
			pid5=fork();
			if (pid5>0){
				pid6=fork();
				if (pid6>0){
					w1=waitpid(pid4,NULL,0);
					w2=waitpid(pid5,NULL,0);
					w3=waitpid(pid6,NULL,0);
					printf("i am the p2 with id %d and my parents id is%d\nThe ids of my children, are:\npid4=%d\npid5=%d\npid6=%d\n",getpid(),getppid(),w1,w2,w3);
				}
				else if (pid6==0)
				{
					printf("i am p6 with pid %d and my parents id is %d\n",getpid(),getppid());
				}
			}
			else{
				printf("i am p5 with pid %d and my parents id is %d\n",getpid(),getppid());
				}
			}
		else{
			printf("i am p4 with pid %d and my parents id is %d\n",getpid(),getppid());
			}
		}
	else{
		w0=waitpid(pid1,NULL,0);
		printf("the exit value of pid1 is %d\n", w0);
		printf("i am p0 with pid %d and my parents id is %d\n\n\n",getpid(),getppid());
		execlp("cat","cat","-n","ls.c",NULL);
		}
	

}
return 0;
}