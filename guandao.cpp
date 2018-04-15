#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>			
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
main()
{
    int fd[2];
    int fd2[2];   					
    pid_t pid;
    pid_t pid1;
    char in[50];
    in[0] = '\0';

    int status;
    int status_2;

	const char * s = NULL;
    if(pipe(fd) < 0)  				
        printf("Create Pipe Error!\n");
    if(pipe(fd2)< 0)  				
        printf("Create Pipe Error!\n");

    if((pid = fork()) < 0)printf("Fork Error!\n");
    else if(pid == 0)  				
    {	

     	if(s == NULL){

	 	  	s = "Child process 1 is sending a message";
	 
	        close(fd[0]);
	       write(fd[1],s,strlen(s));	   
	       	s = NULL;
    	}
    	
    	exit(20);
    } 
    if(pid > 0 && wait(&status)&&WIFEXITED(status) != 0&&WEXITSTATUS(status) == 20 ){

    	if(strlen(in) == 0){

    		close(fd[1]);
    		read(fd[0],in,50);
  			if(strlen(in) != 0)cout<<in<<endl;
  			memset(in,'\0',50);
  			fflush(stdin);
  		}
    } 
   

    
    if((pid1 = fork()&&pid != 0) < 0) printf("Fork2 Error\n");

    else if(pid1 == 0){
    	
    
    	if(s == NULL){
    		
	 	  	s = "Child process 2 is sending a message";
	 	 
	        close(fd2[0]);				
	        write(fd2[1],s,strlen(s));
	       	s = NULL;

    	}
    	
    	exit(10);
    }
     if(pid1 > 0&&wait(&status_2)&&WIFEXITED(status_2) != 0&&WEXITSTATUS(status_2) == 10 ){

    	if(strlen(in) == 0){
    		close(fd2[1]);
    		read(fd2[0],in,sizeof(in));
  			if(strlen(in) != 0)cout<<in<<endl;
  			memset(in,'\0',sizeof(in));
  		}
    }

  } 	

