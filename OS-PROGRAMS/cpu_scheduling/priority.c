
#include <stdio.h>
struct Process
{
    int pid;
    int at;
    int bt;
    int priority;
    int ct;
    int tat;
    int wt;
    int visited;
} p[10], temp;

// Priority
void main()
{
    int n, i, j, priority, time, total_tat = 0, total_wt = 0, count = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the process id: ");
        scanf("%d", &p[i].pid);
        printf("\nEnter the arrivat time and burst time");
        scanf("%d %d", &p[i].at, &p[i].bt);
        printf("Enter the priority: ");
        scanf("%d", &p[i].priority);
        p[i].visited = 0;
    }
    printf("id\tat\tbt\tpriority\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].priority);
    }
    time = 0;
    while (count < n)
    {
        priority = -1;
        for (j = 0; j < n; j++)
        {
            if (p[j].at <= time && p[j].visited == 0)
            {
                if (priority == -1 || p[j].priority < p[priority].priority)
                {
                    priority = j;
                }
            }
        }
        if (priority == -1)
        {
            time++;
        }
        else
        {
            p[priority].visited = 1;
            p[priority].ct = p[priority].bt + time;
            p[priority].tat = p[priority].ct - p[priority].at;
            p[priority].wt = p[priority].tat - p[priority].bt;
            total_tat = total_tat + p[priority].tat;
            total_wt = total_wt + p[priority].wt;
            time = p[priority].ct;
            count++;
        }
    }
    printf("| id\t| at\t| bt\t| pri\t| ct\t| tat\t| wt\n");
    printf("_______________________________________\n");
    for (i = 0; i < n; i++)
    {
        printf("p%d\t| %d\t| %d\t| %d\t| %d\t| %d\t| %d\n", p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
        printf("________________________________________\n");
    }
    printf("average tat: %d\n average wt: %d\n", total_tat / n, total_wt / n);
}
