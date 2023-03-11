#include<stdio.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include<errno.h>

#define SIZE 1050

/*struct message{*/

/*   int bytes;*/
/*   char buffer[SIZE];*/

/*};*/


int main()
{
   int shmID;
   char* shared_memory;
   char buffer[SIZE];
   int num1=5, num2=3;
   int num3=num1+num2;
   //struct message* msg;
   
   //create shared memory
   shmID = shmget(IPC_PRIVATE, SIZE, 0644|IPC_CREAT);
   if (shmID == -1) {
      perror("shmget");
      return 1;
   }
   
   
   //attach shared memory
   shared_memory = (char *) shmat(shmID, NULL, 0);
   if (shared_memory == (void *) -1) {
      perror("shmat");
      return 1;
   }
   
   //sprintf(buffer, "Server writing to shared memory. Sum of %d and %d is %d", num1, num2, num3);
   
   //write to shared memory
   printf("Server writing to shared memory...\n");
   sprintf(shared_memory, "Sum of %d and %d is %d", num1, num2, num3);
   printf("Server has written: \n  %s \n", shared_memory);
   
/*   int bytes=sizeof(buffer)/sizeof(buffer[0]);*/
/*   printf("Server has written %d bytes to shared memory.\n", bytes);*/
  
   
   printf("Server is now forking a child process...\n"); 
   
   pid_t pid = fork();
   if(pid<0)
   {
      printf("Error. Server could not fork.\n");
   }
   else if(pid==0)
   {
     //child client process
      printf("   ~ Client1 reading from shared memory...\n");
      printf("   ~ Client1 has read this: %s\n", shared_memory);
      num1=2, num2=7;
      num3=num1+num2;
      printf("   ~ Client1 writing its own message...\n");
      sprintf(shared_memory,"Sum of %d and %d is %d", num1, num2, num3);
      printf("   ~ Client1 is now going to exit\n");      
      exit(0);
   }
   int status;
   wait(&status);
   printf("Server has waited on Client. Completion detected.\n");
   printf("Server has read reply from Client1. The reply is:\n %s\n", shared_memory);
   pid=fork();
   if(pid<0)
   {
      printf("Error. Server could not fork.\n");
   }
   else if(pid==0)
   {
       num3--;
       num2--;
       num1--;
       num3--;
       printf("   ~ Client2 writing its own message...\n");
       sprintf(shared_memory, "Sum of %d and %d is %d", num1, num2, num3);
       printf("   ~ Client2 has written: %s\n", shared_memory);
       printf("   ~ Client2 is going to exit.\nBut wait...\n");
       execl("/home/vaneeza/i210390_OS_Assignment1/sum","9", "1", shared_memory, NULL);
       printf("Exec Failed");
       exit(0);
   }
   
   wait(&status);
   printf("Server has read reply from Client2. The reply is:\n  %s\n", shared_memory);
   
   //detach shared memory
   shmdt(shared_memory);
   printf("Server has detached shared memory\n");
   shmctl(shmID, IPC_RMID, NULL);
   printf("Server has removed shared memory\n"); 
   return 0;
}


