#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// using namespace std;
struct Node
{
    int arrivalTime, burstTime, priority;
    struct Node *next;
} * front, *rear;
void swap(struct Node *xp, struct Node *yp)
{
    struct Node temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(struct Node *arr, int n, bool priority)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        if (priority)
        {
            for (j = i + 1; j < n; j++)
                if (arr[j].priority > arr[min_idx].priority)
                    min_idx = j;
        }
        else
        {
            for (j = i + 1; j < n; j++)
                if (arr[j].burstTime < arr[min_idx].burstTime)
                    min_idx = j;
        }

        swap(&arr[min_idx], &arr[i]);
    }
}

void addProcess(int arrivalTime, int busrtTime, int priority)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->arrivalTime = arrivalTime;
    temp->burstTime = busrtTime;
    temp->priority = priority;

    if (rear == NULL)
    {
        front = rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
}

void fcfs()
{
    if (front == NULL)
    {
        printf("Queue is Empty\n");
        return;
    }
    int waitingTime, tat, completionTime, i = 1;
    waitingTime = tat = completionTime = 0;
    struct Node *temp = front;
    printf("\nFCFS ALGORITHM\n");
    printf("Processes Burst time  Waiting time  Turn around time  Completion Time\n");
    while (temp != NULL)
    {
        tat = 0;
        completionTime += temp->burstTime;
        tat = completionTime - temp->arrivalTime;
        waitingTime = tat - temp->burstTime;
        printf("%d \t\t %d\t    %d\t\t  %d \t\t %d\n", i, temp->burstTime, waitingTime, tat, completionTime);
        temp = temp->next;
        i++;
    }
}

void sjf(int count)
{

    struct Node *arr = (struct Node *)malloc(count * sizeof(struct Node));
    struct Node *temp = front;
    int waitingTime, tat, completionTime, i = 1;
    waitingTime = tat = completionTime = 0;
    for (int i = 0; i < count; i++)
    {
        arr[i] = *temp;
        temp = temp->next;
    }

    sort(arr, count, false);
    printf("\nSJF ALGORITHM\n");
    printf("Processes Burst time  Waiting time  Turn around time  Completion Time\n");
    for (int i = 0; i < count; i++)
    {
        tat = 0;
        completionTime += arr[i].burstTime;
        tat = completionTime - arr[i].arrivalTime;
        waitingTime = tat - arr[i].burstTime;
        printf("%d \t\t %d\t    %d\t\t  %d \t\t %d\n", i, arr[i].burstTime, waitingTime, tat, completionTime);
    }
    free(arr);
}

void priority(int count)
{
    struct Node *arr = (struct Node *)malloc(count * sizeof(struct Node));
    struct Node *temp = front;
    for (int i = 0; i < count; i++)
    {
        arr[i] = *temp;
        temp = temp->next;
    }
    sort(arr, count, true);
    printf("\nPRIORITY ALGORITHM\n");
    printf("Processes Burst time  Waiting time  Turn around time  Priority   Completion Time\n");

    int waitingTime, tat, completionTime, i = 1;
    waitingTime = tat = completionTime = 0;
    for (int i = 0; i < count; i++)
    {
        tat = 0;
        completionTime += arr[i].burstTime;
        tat = completionTime - arr[i].arrivalTime;
        waitingTime = tat - arr[i].burstTime;
        printf("%d \t\t %d\t    %d\t\t  %d\t\t  %d \t\t %d\n", i, arr[i].burstTime, waitingTime, tat, arr[i].priority, completionTime);
    }
}

int accept(bool priority)
{
    int count;
    printf("Enter Number of Processes : ");
    scanf("%d", &count);
    int burstTime, arrivalTime, prio = 0;
    for (int i = 0; i < count; i++)
    {
        prio = 0;
        printf("Process %d\n", i + 1);
        printf("Enter Burst Time : \n");
        scanf("%d", &burstTime);
        printf("Enter Arrival Time : \n");
        scanf("%d", &arrivalTime);
        if (priority)
        {
            printf("Enter Priority : \n");
            scanf("%d", &prio);
        }
        addProcess(arrivalTime, burstTime, prio);
        printf("\n");
    }
    return count;
}
void clearQueue()
{
    struct Node *temp = front;
    // while (temp != NULL)
    // {
    //     free(temp);
    //     temp = temp->next;
    // }
}
int main()
{
    int count, choice = 4;
    do
    {
        printf("CPU Scheduling Algorithm\n1. FCFS\n2. SJF\n3. Priority\n4. Exit\n\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            count = accept(false);
            fcfs();
            clearQueue();
            break;
        case 2:
            count = accept(false);
            sjf(count);
            clearQueue();
            break;
        case 3:
            count = accept(true);
            priority(count);
            clearQueue();
            break;
        case 4:
            break;
        }
    } while (choice != 4);
    return 0;
}