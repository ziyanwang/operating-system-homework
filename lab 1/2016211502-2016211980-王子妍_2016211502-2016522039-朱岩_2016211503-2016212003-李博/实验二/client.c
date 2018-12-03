#include<stdio.h>
#include<sys/types.h>  
#include<sys/ipc.h>  
#include<sys/msg.h>  

#include<stdlib.h>
struct msgtype
{
    long mtype;          //type
    char mtext[256];     //text
}msg;
int msgqid;
void client()
{
    int i,pid;
    msgqid=msgget(75,0777);//SVKEY=75  set up a message queue
    pid=getpid();//get the current process id
    int *pint;
    pint=(int*)msg.mtext;
    *pint=pid;
    
    msg.mtype=1;
    
    msgsnd(msgqid,&msg,sizeof(int),0);//send
    msgrcv(msgqid,&msg,sizeof(struct msgtype),pid,0);
    printf("receive reply from,server's pid:%d \n",pid);
    exit(0);
}
int main()
{
    client();
    return 0;
}
    


