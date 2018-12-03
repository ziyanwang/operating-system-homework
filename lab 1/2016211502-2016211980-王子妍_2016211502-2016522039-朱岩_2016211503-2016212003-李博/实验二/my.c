#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>//memset(),strncpy()
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMKEY 75

int shmid; //共享内存标识符
char *addr;//共享内存物理首地址

char* argv[] = {"What a wonderful world we are living in!"};//准备写入的数据信息

void B() {
    shmid = shmget(SHMKEY, 512, 0777); //打开共享区，内存512字节，所有人都有全部的读写以及执行权限
    addr = shmat(shmid, NULL, 0);//获得共享区首地址
    memset(addr, '\0', 512);//将addr的后512字节设置成字符'\0'
    strncpy(addr, argv[0], 512);//将argv[0]的前512个字节（不足补'\0')存入共享区addr
    exit(0);//进程结束
}

void A() {
    shmid = shmget(SHMKEY, 512, 0777|IPC_CREAT);//创建共享存储区
    addr = shmat(shmid, NULL, 0); 
    printf("get message \"%s\" from the shared memory\n", addr);//读取共享区的数据
    exit(0);
}

int main() {
  
    pid_t pid1 = fork();
    if (pid1 == 0) A();
    if (pid1 < 0) printf("A进程创建失败");
    pid_t pid2 = fork();
    if (pid2 == 0) B();
    if (pid2 < 0) printf("B进程创建失败");
    
    wait(NULL);//等待子进程执行完毕
    return 0;
}    
