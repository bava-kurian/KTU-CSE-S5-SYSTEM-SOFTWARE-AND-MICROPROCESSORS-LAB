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
} p[10], temp;

// SJF
void main()
{
    int n, i, j, min, time, total_tat, total_wt, count = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the process id: ");
        scanf("%d", &p[i].pid);
        printf("\nEnter the arrivat time and burst time");
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].visited = 0;
    }
    printf("id\tat\tbt\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt);
    }
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[i].at > p[i + 1].at)
            {
                temp = p[i];
                p[i] = p[i + 1];
                p[i + 1] = temp;
            }
        }
    }
    time = 0;
    while (count < n)
    {
        min = -1;
        for (j = 0; j < n; j++)
        {
            if (p[j].at <= time && p[j].visited == 0)
            {
                if (min == -1 || p[j].bt < p[min].bt)
                {
                    min = j;
                }
            }
        }
        if (min == -1)
        {
            time++;
        }
        else
        {
            p[min].visited = 1;
            p[min].ct = p[min].bt + time;
            p[min].tat = p[min].ct - p[min].at;
            p[min].wt = p[min].tat - p[min].bt;
            total_tat = total_tat + p[min].tat;
            total_wt = total_wt + p[min].wt;
            time = p[min].ct;
            count++;
        }
    }
    printf("| id\t| at\t| bt\t| ct\t| tat\t| wt\n");
    printf("_______________________________________\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t| %d\t| %d\t| %d\t| %d\t| %d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        printf("________________________________________\n");
    }
    printf("average tat: %d\n average wt: %d\n", total_tat / n, total_wt / n);
}