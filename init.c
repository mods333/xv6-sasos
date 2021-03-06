// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *argv1[] = { "ipc_process1", 0 };
char *argv2[] = { "test_queue", 0 };
char *argv3[] = { "shmem_process1", 0 };

int
main(void)
{
  int pid, wpid;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  for(;;){
    printf(1, "Why don't we try forkexec\n");
    //forkexec("ipc_process1", argv);
    printf(1,"Calling test Queue : \n");
    forkexec("test_queue", argv2);
    wait();
    printf(1,"Calling shared memory demo\n");
    forkexec("shmem_process1", argv3);
    printf(1, "OMG!!! I can't believe it worked\n");
    for(;;);
    /*
     * Following code is not going to run
     */

    printf(1, "init: starting sh\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", argv1);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
