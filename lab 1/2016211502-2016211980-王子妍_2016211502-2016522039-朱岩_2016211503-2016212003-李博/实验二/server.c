#include<stdio.h>  
#include<sys/types.h>  
#include<sys/ipc.h>  
#include<sys/msg.h> 
#include<stdlib.h>
 
struct msgtype
{
    long mtype;                         //type
    char mtext[256];                    //text
}msg;
int msgqid;
void server()
{
    int pid;
    int i,*pint;
    msgqid=msgget(75,0777|IPC_CREAT);//set up a message queue    SVKEY=75
    for(;;)
    {
        msgrcv(msgqid,&msg,sizeof(struct msgtype),1,0);//receive message REQ=1
        pint=(int*)msg.mtext;
        pid=*pint;                        //get client's pid
        printf("serving for client,client's pid:'%d'\n",pid);
        msg.mtype=pid;
        pid=getpid();
        msgsnd(msgqid,&msg,sizeof(pid),0);//向 client 进程发送应答消息
    }
    //msgctl(msgqid,IPC_RMID,0);
    exit(0);
}
int main()
{
    server();
    return 0;
}
    

