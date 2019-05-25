#include<bits/stdc++.h>
#include <fstream>
using namespace std;
typedef struct{
 
    int arrival;
    int burst;
    int priorty;
    int index;
    int status;
}process;
 
process p[5];

void swap(process *x,process *y)
{
    process temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
 
void bublesort(process p[], int n)
{
 
    int i,j;
    for(i=0;i<(n-1);i++)
        for(j=0;j<(n-(i+1));j++)
            if(p[j].arrival > p[j+1].arrival||(p[j].arrival==p[j+1].arrival&&p[j].priorty>p[j+1].priorty))
                swap(&p[j],&p[j+1]);
}
 
void sortpr(process p[],int n)
{
    int i,j;
    for(i=0;i<(n-1);i++)
        for(j=0;j<(n-(i+1));j++)
            if(p[j].priorty > p[j+1].priorty)
                swap(&p[j],&p[j+1]);
}
 
void deletep(process p[],int size,int index)
{ 
    int i=index;
    while(i<size-1)
    {
        p[i]=p[i+1];
        i++;
    }
    return;
}
 
bool nonew(process p[],int size)
{ 
    for(int i=0;i<size;i++)
    {
        if(p[i].status==0 )return false;
    }
    return true;
}
 
bool noready(process p[],int size)
{
    for(int i=0;i<size;i++)
        if(p[i].status==1)
            return false;
    return true;
}
 
int ready(process p[],int size)
{ 
    int min=0;
    for(int i=0;i<size;i++)
        if(p[i].status==1&&p[i].priorty<p[min].priorty)
            min=i;
    return min;
}
 
void NonPreemtive(process p[],int size)
{ 
    int i,j,minpr,current=p[0].arrival;
    int tt[5];
    for(i=0;i<size-1;i++)
    {
        printf("p%d from %d to %d\n",p[i].index,current,current+p[i].burst);
        tt[i]=current+p[i].burst-p[i].arrival;
        current=current+p[i].burst;
        if (p[i+1].arrival==current)
        {
            continue;
        }
        else
        {
            if(p[i+1].arrival>current)
            {
                current=p[i+1].arrival;
            }
            else
            {
                j=i+1;
                minpr=p[j].priorty;
                for(j=i+1;j<size;j++)
                { 
                    if(p[j].arrival<current)
                    {
                        if (p[j].priorty<minpr)
                        {
                            minpr=p[j].priorty;
                            swap(&p[i+1],&p[j]);
                        }
                    }
                }
            }
        }
    }
    printf("p%d from %d to %d\n",p[i].index,current,current+p[i].burst);
    tt[i]=current+p[i].burst-p[i].arrival;
    float sum=0;
    for (int i = 0; i < 5; ++i)
    {
        sum+=tt[i];
    }
    cout <<"Avg turnaround time:"<< sum/5.0<< endl;
}
 
void NonPreemtiveAging(process p[],int size)
{
    int i,j,minpr,current=p[0].arrival;
    int tt[5];
    for(i=0;i<size-1;i++)
    { 
        printf("p%d from %d to %d\n",p[i].index,current,current+p[i].burst);
        tt[i]=current+p[i].burst-p[i].arrival;
        current=current+p[i].burst;
        if (p[i+1].arrival==current)
        {
            continue;
        }
        else{
            if(p[i+1].arrival>current)
            {
                current=p[i+1].arrival;
            }
            else{ 
                j=i+1;
                minpr=p[j].priorty-(current-p[j].arrival)/5;
                for(j=i+1;j<size;j++)
                { 
                    if(p[j].arrival<current)
                    {
                        if (p[j].priorty-(current-p[j].arrival)/5<minpr)
                        {
                            minpr=p[j].priorty-(current-p[j].arrival)/5;
                            swap(&p[i+1],&p[j]);
                        }
                    }
                }
            }
        }
    }
    printf("p%d from %d to %d\n",p[i].index,current,current+p[i].burst);
    tt[i]=current+p[i].burst-p[i].arrival;
    float sum=0;
    for (int i = 0; i < 5; ++i)
    {
        sum+=tt[i];
    }
    cout <<"Avg turnaround time:"<< sum/5.0<< endl;
}
 
void Preemtive(process p[],int size)
{
    int i=0,current=p[0].arrival,j,test;
    int tt[5]={ 0 };
    
    while(size!=0)
    {
        printf("p%d from %d to ",p[i].index,current);
        if(nonew(p,size)){
            printf("%d\n",current+p[i].burst);
            tt[i]=current+p[i].burst-p[i].arrival;
            current=current+p[i].burst;
            deletep(p,size,i);
            size--;
            if(size==0) 
                break;
            i=ready(p,size);
            continue;
        }
        else
        {
            test=0;
            for(j=0;j<size;j++)
            {
                if(p[j].arrival<current+p[i].burst)    
                {
                    if(p[j].status==1)
                        continue;
                    if(p[j].priorty<p[i].priorty)
                    {
                        printf(" %d\n",p[j].arrival);
                        // tt[i]+=current+p[].burst;
                        p[i].burst=p[i].burst-(p[j].arrival-current);
                        p[i].status=1;
                        current=p[j].arrival;
                        test=1;
                        i=j;
                        break;
                    }
                    else 
                        p[j].status=1;
                }
                else if(p[j].arrival==current+p[i].burst)
                    p[j].status=1;
            }
            if(test==1)
                continue;

            printf("%d\n",current+p[i].burst);
            tt[i]=current+p[i].burst-p[i].arrival;
            current=current+p[i].burst;
            deletep(p,size,i);
            size--;
            if (!noready(p,size))
            {
                i=ready(p,size);
            }
            else 
            {
                current=p[i].arrival;
            }
        }
    }
    float sum=0;
    for (int i = 0; i < 5; ++i)
    {
        sum+=tt[i];
    }
    cout <<"Avg turnaround time:"<< sum/5.0<< endl;
    
    return;
}

void readinput()
{
    int i;
    fstream myfile("./tmp",ios_base::in);
    for (i=0;i<5;i++)
    {
//take input from file or manually
        
        // myfile.open ("tmp");     
        // printf("\nenter the arrival time of p %d:",i);
        // scanf("%d",&p[i].arrival);
        // string tmp;
        myfile >> p[i].arrival;
        // p[i].arrival=stoi(tmp);
        // printf("enter the burst time of p %d:",i);
        myfile >> p[i].burst;
        // scanf("%d",&p[i].burst);
        // myfile >> tmp;
        // p[i].burst=stoi(tmp);
        // printf("enter the priorty of p %d:",i);
        myfile >> p[i].priorty;
        // scanf("%d",&p[i].priorty);
        // myfile >> tmp;
        // p[i].priorty=stoi(tmp);
        p[i].status=0;
        p[i].index=i;
    }
    myfile.close();
    bublesort(p,5);
    printf("\nsorted:\nprocess \t\tarrival time \t\tburst time \t\tpriorty\n");
    for (i=0;i<5;i++)
    {
        printf( " p%d \t\t\t%d \t\t\t%d \t\t\t%d\n",p[i].index,p[i].arrival,p[i].burst,p[i].priorty);
    }
}

int roundRobin()
{
  int count,n=5,time,remain,flag=0,time_quantum; 
  int wait_time=0,turnaround_time=0,at[10],bt[10],rt[10]; 
  fstream myfile("./temp1",ios_base::in);
  // printf("Enter Total Process:\t "); 
  // scanf("%d",&n); 
  remain=n; 
  for(count=0;count<n;count++) 
  { 
    // printf("Enter Arrival Time and Burst Time for Process Process Number %d :",count+1); 
    // scanf("%d",&at[count]); 
    // scanf("%d",&bt[count]); 
    myfile>>at[count];
    myfile>>bt[count];
    rt[count]=bt[count]; 
  } 
  // printf("Enter Time Quantum:\t"); 
  // scanf("%d",&time_quantum); 
  myfile>>time_quantum;
  printf("\n\nProcess\t\t\tTurnaround Time\t\t\tWaiting Time\n\n"); 
  for(time=0,count=0;remain!=0;) 
  { 
    if(rt[count]<=time_quantum && rt[count]>0) 
    { 
      time+=rt[count]; 
      rt[count]=0; 
      flag=1; 
    } 
    else if(rt[count]>0) 
    { 
      rt[count]-=time_quantum; 
      time+=time_quantum; 
    } 
    if(rt[count]==0 && flag==1) 
    { 
      remain--; 
      printf("P[%d]\t\t\t\t%d\t\t\t\t%d\n",count+1,time-at[count],time-at[count]-bt[count]); 
      wait_time+=time-at[count]-bt[count]; 
      turnaround_time+=time-at[count]; 
      flag=0; 
    } 
    if(count==n-1) 
      count=0; 
    else if(at[count+1]<=time) 
      count++; 
    else 
      count=0; 
  } 
  // printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
  printf("Avg Turnaround Time = %f",turnaround_time*1.0/n); 
  
  myfile.close();
  return 0;
}

int SJF()
{
  int temp, i, j, limit=5, sum = 0, position;
  float average_wait_time, average_turnaround_time;
  int burst_time[20], process[20], waiting_time[20], turnaround_time[20];
  // printf("\nEnter Total Number of Processes:\t");
  // scanf("%d", &limit); 
  fstream myfile("./temp2",ios_base::in);
  for(i = 0; i < limit; i++)
  {
        // printf("Enter Burst Time For Process[%d]:\t", i + 1);
        // scanf("%d", &burst_time[i]);
        myfile>>burst_time[i];
        process[i] = i + 1;
  }
  for(i = 0; i < limit; i++)
  {
        position = i;
        for(j = i + 1; j < limit; j++)
        {
              if(burst_time[j] < burst_time[position])
              {
                    position = j;
              }
        }
        temp = burst_time[i];
        burst_time[i] = burst_time[position];
        burst_time[position] = temp;
        temp = process[i];
        process[i] = process[position];
        process[position] = temp;
  } 
  waiting_time[0] = 0;
  for(i = 1; i < limit; i++)
  {
        waiting_time[i] = 0;
        for(j = 0; j < i; j++)
        {
              waiting_time[i] = waiting_time[i] + burst_time[j];
        } 
        sum = sum + waiting_time[i];
  }
  average_wait_time = (float)sum / limit;
  sum = 0;
  printf("\nProcess ID\t\tBurst Time\t Waiting Time\t Turnaround Time\n");
  for(i = 0; i < limit; i++)
  {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        sum = sum + turnaround_time[i];
        printf("\nProcess[%d]\t\t%d\t\t %d\t\t %d\n", process[i], burst_time[i], waiting_time[i], turnaround_time[i]);
  }
  average_turnaround_time = (float)sum / limit;
  // printf("\nAverage Waiting Time:\t%f\n", average_wait_time);
  printf("\nAverage Turnaround Time:\t%f\n", average_turnaround_time);
  myfile.close();
  return 0;
}
 
int main()
{
    int c=1;
    printf("Welcome\n");
    // printf( "Choose the mode of scedueling:\npress 1 for non preemtive\npress 2 for non preemtive with aging\npress 3 for preemptive\npress 4 for Round Robin\npress 3 for Shortest Job First\n");
    // scanf("%d",&c);
    
    switch(c)
    {
        case 1:
            cout << "NonPreemptive Priority scheduling"<< endl;
            readinput();
            NonPreemtive(p,5);
            cout << endl;
            cout << endl;
            cout << endl;
            // break;
        case 2:
            cout << "NonPreemptive Priority scheduling with aging"<< endl;
            readinput();
            NonPreemtiveAging(p,5);
            cout << endl;
            cout << endl;
            cout << endl;
            // break;
        case 3:
            cout << "Preemptive Priority scheduling"<< endl;
            readinput();
            Preemtive(p,5);
            cout << endl;
            cout << endl;
            cout << endl;
            // break;
        case 4:
            cout << "RoundRobin:"<< endl;
            
            roundRobin();
            cout << endl;
            cout << endl;
            cout << endl;
            // break;
        case 5:
            cout << "Shortest Job First:"<< endl;
            
            SJF();
            cout << endl;
            cout << endl;
            cout << endl;
            // break;
    }

    getchar();
}
