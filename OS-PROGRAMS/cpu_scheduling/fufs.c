#include<stdio.h>

struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int visited;
}p[20];

void main(){
    int i,j,n,time,count,min;
    printf("Enter the number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
            printf("\nEnter process id,at,bt: ");
            scanf("%d%d%d",&p[i].pid,&p[i].at,&p[i].bt);
            p[i].visited=0;
    }
    time =0;
    count=0;
    while(count<n)
    {
        min=-1;
        for (int i=0;i<n;i++)
        {
            if(p[i].at<time && p[i].visited!=1)
            {
                if(min==-1|| p[i].at>p[min].at)
                {
                    min=i;
                }
            }
            if(min==-1)
            {
                time++;
            }
            else
            {
                p[i].ct=time+p[i].bt;
                p[i].tat=p[i].ct-p[i].at;
                p[i].wt=p[i].tat-p[i].bt;
                p[i].visited=1;
                count++;
            }

        }
    }
    printf("pid\tat\tbt\tct\ttat\twt\n");
    printf("------------------------------------------------------------------------------------\n");
    for(i=0;i<n;i++){
        printf("p%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
        printf("------------------------------------------------------------------------------------\n");
    }
}
