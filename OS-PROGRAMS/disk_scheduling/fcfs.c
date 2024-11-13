#include <stdio.h>

void main()
{
    int n, i, j, head, seek = 0, A[20], choice, up_bound, low_bound, dist = 0;
    printf("Enter the number of tracks: ");
    scanf("%d", &n);
    printf("Enter the head position: ");
    scanf("%d", &head);
    printf("Enter the tracks: ");
    A[0] = head;
    for (i = 1; i < n + 1; i++)
    {
        scanf("%d", &A[i]);
    }
    n = n + 1;
    printf("\nService order: %d", head);
    for (i = 1; i < n; i++)
    {
        printf(" %d ", A[i]);
        if (A[i] > A[i - 1])
        {
            dist += A[i] - A[i - 1];
        }
        else
        {
            dist += A[i - 1] - A[i];
        }
    }
    printf("\nTotal head movement: %d\n", dist);
}