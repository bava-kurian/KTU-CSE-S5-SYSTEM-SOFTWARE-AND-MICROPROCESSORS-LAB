
#include <stdio.h>
struct Process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int visited;
    int remaining;
} p[10], temp;
int front = -1, rear = -1, q[100];
void push(int x)
{
    if (front == -1)
    {
        front = 0;
    }
    q[++rear] = x;
}
int pop()
{
    if (front == -1 || front > rear)
    {
        return -1;
    }
    else
    {
        int elem = q[front++];
        if (front > rear)
        { // Reset queue if it becomes empty
            front = rear = -1;
        }
        return elem;
    }
}

// Round Robin
void main()
{
    int n, i, j, min, time, total_tat = 0, total_wt = 0, count = 0, qua = 0, elem, k, z = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the process id: ");
        scanf("%d", &p[i].pid);
        printf("\nEnter the arrivat time and burst time");
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].visited = 0;
        p[i].remaining = p[i].bt;
    }
    printf("\nEnter the time quantum: ");
    scanf("%d", &qua);
    printf("id\tat\tbt\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt);
    }
    time = 0;
    printf("\nGantt Chart: \n");

    while (count < n)
    {
        for (i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].visited == 0)
            {
                push(i);
                p[i].visited = 1;
            }
        }
        k = 0;
        elem = pop();
        if (elem == -1)
        {
            time++;
            z++;
        }
        else
        {
            if (z != 0)
            {
                printf("%d >>>>>>>>>>>>> %d idle\n", time - z, time);
                z = 0;
            }
            printf("%d >>>>>>>>>>>>> ", time);
            while (k < qua && p[elem].remaining > 0)
            {
                p[elem].remaining--;
                time++;
                k++;
                for (i = 0; i < n; i++)
                {
                    if (p[i].at <= time && p[i].visited == 0)
                    {
                        push(i);
                        p[i].visited = 1;
                    }
                }
            }
            if (p[elem].remaining == 0)
            {
                printf("%d p%d \n", time, p[elem].pid);
                p[elem].ct = time;
                p[elem].tat = p[elem].ct - p[elem].at;
                p[elem].wt = p[elem].tat - p[elem].bt;
                total_tat = total_tat + p[elem].tat;
                total_wt = total_wt + p[elem].wt;
                count++;
            }
            else
            {
                printf("%d p%d \n", time, p[elem].pid);
                push(elem);
            }
        }
    }
    printf("| id\t| at\t| bt\t| ct\t| tat\t| wt\n");
    printf("_______________________________________\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t| %d\t| %d\t| %d\t| %d\t| %d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        printf("________________________________________\n");
    }
    printf("average tat: %f\n average wt: %f\n", (float)total_tat / n, (float)total_wt / n);
}
