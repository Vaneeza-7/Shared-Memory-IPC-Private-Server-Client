#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>


int  main(int  argc, char *argv[], char* shmPointer)
{
           
      printf("   => Client 2 has been EXEC-ed.\n");
      printf("   => Client2 exec writing to shared memory...\n");
      int num1= atoi(argv[0]);
      int num2= atoi(argv[1]);
      int num3= num1+num2;
      sprintf(shmPointer, "Sum of %d and %d is %d.", num1, num2, num3);
      printf("   => Client2 exec has written this: %s\n", shmPointer);      
     
}
