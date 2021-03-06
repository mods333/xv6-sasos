#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main()
{
  int ip[2] = {3,4};
  char *argv[] = {"shmem_process2",0};
  int* mem;
  int* cmem;
  int md;

  printf(1,"in shmem 1 \n");

  // Creating pipes
  if(pipe(ip) == -1){
    printf(1, " Error in creating pipe \n");
    exit();
  }

  forkexec("shmem_process2", argv);

  md = shmem_alloc();
  mem = shmem_getref(md);
  cmem = shmem_getref(shmem_mapdup(md));
  if(md < 0 || mem == 0 || cmem == 0){
    printf(1, "Error in allocating shared memory\n");
    exit();
  }
  printf(1, "Allocated memory at 0x%x\n", mem);

  *mem = 1;

  // inform the child of the allocated memory
  if(write(ip[1], (char*)&cmem, sizeof(int*)) != sizeof(int*)){
    printf(1, " Error in write\n");
    exit();
  }

  wait();

  printf(1, "Got back %d\n", *mem);

  if(shmem_free(md) != 0){
    printf(1, "Unable to free shared mem\n");
    exit();
  }

  exit();
}
