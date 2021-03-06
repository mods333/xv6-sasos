#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


char *argv[] = {"ipc_process2",0};

int
main()
{

  //int pid;

  // for parent to write and child to read
  int ip[2] = {3,4};

  // for child to write and parent to read
  int op[2] = {5,6};


  int count = 1000;
  int buf_size = 7;
  char buffer[15] = "0000000";
  char readbuff[20];
  int readnum;

  printf(1,"in ipc 1 \n");

  // Creating pipes
  if(pipe(ip) == -1){
    printf(1, " Error in creating pipe \n");
    exit();
  }

  if(pipe(op) == -1){
    printf(1, "Error in creating pipe #2 \n ");
    exit();
  }


  forkexec("ipc_process2", argv);


  for(int i = 0; i < count; i++){
    // Write into pipe 1
    if(write(ip[1], buffer, buf_size) != buf_size){
      printf(1," Error in write");
      exit();

    }


    // Read from the child pipe

    if(read(op[0],readbuff,buf_size) != buf_size){
      printf(1,"\n Error in read by parent");
      exit();
    }

    //printf(1,"\n Parent read : %s \n", readbuff);
    readnum = atoi(readbuff);
    printf(1,"Number is(p) : %d \n", readnum);

    readnum += 2;

    itoa(readnum, buffer, 10);


  }





  printf(1,"\n Out of the loop \n");
  //
  wait();
  exit();
}
