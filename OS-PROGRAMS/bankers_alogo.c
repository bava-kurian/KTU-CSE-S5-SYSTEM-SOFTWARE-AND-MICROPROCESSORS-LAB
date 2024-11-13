#include <stdio.h>
int instance[20];
int max[50][50];
int available[50][50];
int avail[50];
int allocation[50][50];
int need[50][50];
int ans[50];
int visited[50];
int main()
{
    int z = 0, n, m, i, j, k, alloc = 0, flag = 0, y, p = 0;
    printf("Enter the number of instances: ");
    scanf("%d", &m);
    printf("Enter the instances: ");
    for (i = 0; i < m; i++)
    {
        printf("%c : ", (i + 65));
        scanf("%d", &instance[i]);
    }
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the max matrix: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("p%d[%c] : ", i + 1, (j + 65));
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter the allocation matrix: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("p%d[%c] : ", i + 1, (j + 65));
            scanf("%d", &allocation[i][j]);
            visited[i] = 0;
        }
    }
    for (j = 0; j < m; j++)
    {
        alloc = 0;
        for (i = 0; i < n; i++)
        {
            // calculating the need matrix
            need[i][j] = max[i][j] - allocation[i][j];
            alloc += allocation[i][j];
        }
        // entering the available jth instance in avail array
        avail[j] = instance[j] - alloc;
    }
    // copying the available instances to the available matrix
    for (j = 0; j < m; j++)
    {
        available[0][j] = avail[j];
    }

    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (visited[i] == 0)
            {
                flag = 0;
                for (j = 0; j < m; j++)
                {
                    // checking if the need of i th process is greter than the instances available
                    if (need[i][j] > available[z][j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    visited[i] = 1;
                    ans[p] = i;
                    p++;
                    // updating the available matrix after completing the processes need
                    for (y = 0; y < m; y++)
                    {
                        available[z + 1][y] = available[z][y] + allocation[i][y];
                    }
                    z++;
                }
            }
        }
    }
    int safe = 1;

    // checking if the system is safe or not
    for (i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            safe = 0;
            printf("The following system is not safe \n");
            break;
        }
    }
    if (safe == 1)
    {
        printf("The following system is safe \n");
        printf("Max        |   Allocation |   Need    |    Available   | \n");
        for (i = 0; i < n; i++)
        {
            // for printing the max matrix
            for (j = 0; j < m; j++)
            {
                printf("%2d ", max[i][j]);
            }
            printf("    |");
            // for printing the allocation matrix of the process in the same row
            for (j = 0; j < m; j++)
            {
                printf("%2d ", allocation[i][j]);
            }
            printf("    |");
            // for printing the need matrix of the process in the same row
            for (j = 0; j < m; j++)
            {
                printf("%2d ", need[i][j]);
            }
            printf("    |");
            // for printing the available matrix after completion
            for (j = 0; j < m; j++)
            {
                printf("%2d ", available[i][j]);
            }
            printf("    |");
            printf("\n");
        }
        for (i = 0; i < n; i++)
        {
            printf("p%d>>>", ans[i]);
        }
        printf("\n\n");
        // for printing the available matrix after completion
        // i.e the instance provided by the user is equal to the available at last
        printf("Available after execution : ");
        for (j = 0; j < m; j++)
        {
            printf("%2d ", available[z][j]);
        }
    }
}