
#include <stdio.h>

void main()
{
    int n, i, j, head, seek = 0, A[20], choice, up_bound, low_bound, dist = 0;
    printf("Enter the number of tracks: ");
    scanf("%d", &n);
    printf("Enter the head position: ");
    scanf("%d", &head);
    printf("Enter the tracks: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
    // inserting head into the array
    A[n] = head;
    n = n + 1;
    printf("Enter the low bound: ");
    scanf("%d", &low_bound);
    printf("Enter the up bound: ");
    scanf("%d", &up_bound);
    // make ascending order
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (A[j] > A[j + 1])
            {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        if (A[i] == head)
        {
            j = i;
            break;
        }
    }
    printf("\nService order: ");
    for (i = j; i < n; i++)
    {
        printf(" %d ", A[i]);
    }
    dist += up_bound - head;
    printf(" %d ", up_bound);
    for (i = j - 1; i >= 0; i--)
    {
        printf(" %d ", A[i]);
    }
    dist += up_bound - A[0];
    printf("\nTotal head movement: %d\n", dist);
}
