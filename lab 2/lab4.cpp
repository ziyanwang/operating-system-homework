#include <stdio.h>    
#include <stdlib.h>    
#include <string.h>    
typedef struct node    
{    
      char name[20];    /*���̵�����*/    
      int prio;     /*���̵����ȼ�*/    
      int round;     /*����CPU��ʱ��Ƭ*/    
      int cputime;    /*CPUִ��ʱ��*/    
      int needtime;    /*����ִ������Ҫ��ʱ��*/    
      char state;     /*���̵�״̬��W--����̬��R--ִ��̬��F--���̬*/    
      int count;     /*��¼ִ�еĴ���*/    
      struct node *next;   /*����ָ��*/    
}PCB;    
PCB *ready=NULL,*run=NULL,*finish=NULL; /*�����������У��������У�ִ�ж��к���ɶ���*/    
int num;    
void GetFirst();    /*�Ӿ�������ȡ�õ�һ���ڵ�*/    
void Output();     /*���������Ϣ*/    
void InsertPrio(PCB *in);  /*�������ȼ����У��涨������ԽС�����ȼ�Խ��*/    
void InsertTime(PCB *in);  /*ʱ��Ƭ����*/    
void InsertFinish(PCB *in);  /*ʱ��Ƭ����*/    
void PrioCreate();    /*���ȼ����뺯��*/    
void TimeCreate();    /*ʱ��Ƭ���뺯��*/    
void Priority();    /*�������ȼ�����*/    
void RoundRun();    /*ʱ��Ƭ��ת����*/    
int main(void)    
{    
      char chose;    
      printf("������Ҫ�����Ľ�����Ŀ:\n");    
      scanf("%d",&num);    
      getchar();    
      printf("������̵ĵ��ȷ�����(P/R)\n");    
      scanf("%c",&chose);    
      switch(chose)    
      {    
      case 'P':    
      case 'p':    
        PrioCreate();    
        Priority();        
        break;    
      case 'R':    
      case 'r':    
        TimeCreate();    
        RoundRun();    
        break;    
      default:break;    
      }    
      Output();    
      return 0;    
    }    
    void GetFirst()  /*ȡ�õ�һ���������нڵ�*/    
    {    
      run = ready;    

      if(ready!=NULL)    
      {    
        run ->state = 'R';    
        ready = ready ->next;    
        run ->next = NULL;    
      }    
    }    
    void Output()    /*���������Ϣ*/    
    {    
      PCB *p;    
      /*p = ready;*/    
      printf("������\t���ȼ�\tʱ��Ƭ\tcpuʱ��\t��Ҫʱ��\t����״̬\t������\n");    
       p = ready; 
      while(p!=NULL)    
      {    
        printf("%s\t%d\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);    
        p = p->next;    
      }    
      p = finish;    
      while(p!=NULL)    
      {    
        printf("%s\t%d\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);    
        p = p->next;    
      }    
      p = run;    
      while(p!=NULL)    
      {    
        printf("%s\t%d\t%d\t%d\t%d\t\t%c\t\t%d\n",p->name,p->prio,p->round,p->cputime,p->needtime,p->state,p->count);    
        p = p->next;    
      }    
    }    
    void InsertPrio(PCB *in) /*�������ȼ����У��涨������ԽС�����ȼ�Խ��*/    
    {    
      PCB *fst,*nxt;    
      fst = nxt = ready;    

      if(ready == NULL)  /*�������Ϊ�գ���Ϊ��һ��Ԫ��*/    
      {    
        in->next = ready;    
        ready = in;    
      }    
      else     /*�鵽���ʵ�λ�ý��в���*/    
      {    
        if(in ->prio > fst ->prio)  /*�ȵ�һ����Ҫ��(���ڵ���)������뵽��ͷ*/    
        {    
          in->next = ready;    
          ready = in;    
        }    
        else    
        {    
          while(fst->next != NULL)  /*�ƶ�ָ����ҵ�һ������С��Ԫ�ص�λ�ý��в���*/    
          {    
            nxt = fst;    
            fst = fst->next;    
          }    

          if(fst ->next == NULL) /*�Ѿ���������β���������ȼ�����С��������뵽��β����*/    
          {    
            in ->next = fst ->next;    
            fst ->next = in;    
          }    
          else     /*���뵽������*/    
          {    
            nxt = in;    
            in ->next = fst;    
          }    
        }    
      }    
    }    
    void InsertTime(PCB *in)  /*�����̲��뵽��������β��*/    
    {    
      PCB *fst;    
      fst = ready;    

      if(ready == NULL)    
      {    
        in->next = ready;    
        ready = in;    
      }    
      else    
      {    
        while(fst->next != NULL)    
        {    
          fst = fst->next;    
        }    
        in ->next = fst ->next;    
        fst ->next = in;    
      }    
    }    
    void InsertFinish(PCB *in)  /*�����̲��뵽��ɶ���β��*/    
    {    
      PCB *fst;    
      fst = finish;    

      if(finish == NULL)    
      {    
        in->next = finish;    
        finish = in;    
      }    
      else    
      {    
        while(fst->next != NULL)    
        {    
          fst = fst->next;    
        }    
        in ->next = fst ->next;    
        fst ->next = in;    
      }    
    }    
    void PrioCreate() /*���ȼ��������뺯��*/    
    {    
      PCB *tmp;    
      int i;    

      printf("����������ֺͽ�������ʱ�䣺\n");    
      for(i = 0;i < num; i++)    
      {    
        if((tmp = (PCB *)malloc(sizeof(PCB)))==NULL)    
        {    
          perror("malloc");    
          exit(1);    
        }    
        scanf("%s",tmp->name);    
        getchar();    /*���ջس�����*/    
        scanf("%d",&(tmp->needtime));    
        tmp ->cputime = 0;    
        tmp ->state ='W';    
        tmp ->prio = 50 - tmp->needtime;  /*���������ȼ�����Ҫ��ʱ��Խ�࣬���ȼ�Խ��*/    
        tmp ->round = 0;    
        tmp ->count = 0;    
        InsertPrio(tmp);      /*�������ȼ��Ӹߵ��ͣ����뵽��������*/    
      }    
    }    
    void TimeCreate() /*ʱ��Ƭ���뺯��*/    
    {    
      PCB *tmp;    
      int i;    

      printf("����������ֺͽ���ʱ��Ƭ����ʱ�䣺\n");    
      for(i = 0;i < num; i++)    
      {    
        if((tmp = (PCB *)malloc(sizeof(PCB)))==NULL)    
        {    
          perror("malloc");    
          exit(1);    
        }    
        scanf("%s",tmp->name);    
        getchar();    
        scanf("%d",&(tmp->needtime));    
        tmp ->cputime = 0;    
        tmp ->state ='W';    
        tmp ->prio = 0;    
        tmp ->round = 2;  /*����ÿ�������������ʱ��Ƭ��2*/    
        tmp ->count = 0;    
        InsertTime(tmp);    
      }    
    }    
    void Priority()   /*�������ȼ����ȣ�ÿ��ִ��һ��ʱ��Ƭ*/    
    {    
      int flag = 1;    

      GetFirst();    
      while(run != NULL)  /*���������в�Ϊ��ʱ������Ƚ�����ִ�ж���ִ��*/    
      {    
        Output();  /*���ÿ�ε��ȹ����и����ڵ��״̬*/    
        while(flag)    
        {    
          run->prio -= 0; /*���ȼ���ȥ��,����Ϊ0�����ȼ�����*/    
          run->cputime++; /*CPUʱ��Ƭ��һ*/    
          run->needtime--;/*����ִ����ɵ�ʣ��ʱ���һ*/    
          if(run->needtime == 0)/*�������ִ����ϣ�������״̬��ΪF��������뵽��ɶ���*/    
          {    
            run ->state = 'F';    
            run->count++; /*����ִ�еĴ�����һ*/    
            InsertFinish(run);    
            flag = 0;    
          }    
          else   /*������״̬��ΪW�����������*/    
          {    
            run->state = 'W';    
            run->count++; /*����ִ�еĴ�����һ*/    
            InsertTime(run);    
            flag = 0;    
          }    
        }    
        flag = 1;    
        GetFirst();    /*����ȡ�������ж�ͷ���̽���ִ�ж���*/    
      }    
    }    
    void RoundRun()    /*ʱ��Ƭ��ת�����㷨*/    
    {    

      int flag = 1;    

      GetFirst();    
      while(run != NULL)    
      {    
        Output();    
        while(flag)    
        {    
          run->count++;    
          run->cputime++;    
          run->needtime--;    
          if(run->needtime == 0) /*����ִ�����*/    
          {    
            run ->state = 'F';    
            InsertFinish(run);    
            flag = 0;    
          }    
          else if(run->count == run->round)/*ʱ��Ƭ����*/    
          {    
            run->state = 'W';    
            run->count = 0;   /*���������㣬Ϊ�´���׼��*/    
            InsertTime(run);    
            flag = 0;    
          }    
        }    
        flag = 1;    
        GetFirst();    
      }    
}   
