#include <pthread.h>
#include <stdio.h>

pthread_t id1, id[10];
int num, i, j, k;
int th, b[3][3], a[3][3];
int res[3][3];

void *mul(void *p)
{
    int from, to;
    num = (int)p;
    from = (num * 3) / th;
    to = (num + 1) * 3 / th;

    for (i = from; i < to; i++)
    {
        for (j = 0; j < 3; j++)
        {
            res[i][j] = 0;
            for (k = 0; k < 3; k++)
            {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    // for (i = from; i < to; i++)
    // {
    //     printf("\n");
    //     for (j = 0; j < 3; j++)
    //     {
    //         printf("%d \t", res[i][j]);
    //     }
    // }
    // printf("\n………………………….\n");
}
int main()
{

    printf("\nEnter the 3 * 3 matrix A\n");
    for (i = 0; i < 3; i++)
    {

        for (j = 0; j < 3; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    printf("\nEnter the 3 * 3 matrix B\n");
    for (i = 0; i < 3; i++)
    {

        for (j = 0; j < 3; j++)
        {
            scanf("%d", &b[i][j]);
        }
    }
    printf("\nEnter the no of threads");
    scanf("%d", &th);

    for (i = 0; i < th; i++)
    {
        pthread_create(&id[i], NULL, mul, (void *)i);
    }

    for (i = 0; i < th; i++)
    {
        pthread_join(id[i], NULL);
    }
    for (i = 0; i < 3; i++)
    {

        for (j = 0; j < 3; j++)
        {
            printf("%d  ", res[i][j]);
        }
        printf("\n");
    }
}