#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int i = 0;
char buffer[30] = "Shared Memory";
char msg[30];
sem_t patientWaiting, treatmentDone, docAvailable;
pthread_t docThread, patientThread;

void up(sem_t *sem)
{
    sem_post(sem);
}

void down(sem_t *sem)
{
    sem_wait(sem);
}
void consultDoctor()
{
    sprintf(msg, "Doc Consulted by Patient %d\n", i);
    printf(msg);
    sprintf(buffer, "Patient Name is %d \n", i);
}
void noteTreatment()
{
    sprintf(msg, "Treatment Noted : %s\n\n", buffer);
    printf(msg);
    i++;
}
void treatPatient()
{
    sprintf(msg, "Treating Patient : %s", buffer);
    printf(msg);
    sprintf(buffer, "Treatment for Patient %d \n", i);
}
void *doctorProcess(void *arg)
{
    while (i < 10)
    {
        down(&patientWaiting);
        treatPatient();
        up(&treatmentDone);
    }
    pthread_exit(NULL);
}

void *patientProcess(void *arg)

{
    while (i < 10)
    {
        down(&docAvailable);
        consultDoctor();
        up(&patientWaiting);
        down(&treatmentDone);
        noteTreatment();
        up(&docAvailable);
    }
    pthread_exit(NULL);
}

int main()
{

    sem_init(&patientWaiting, 0, 0);
    sem_init(&treatmentDone, 0, 0);
    sem_init(&docAvailable, 0, 1);
    pthread_create(&patientThread, NULL, patientProcess, NULL);
    pthread_create(&docThread, NULL, doctorProcess, NULL);
    pthread_join(docThread, NULL);
    pthread_join(patientThread, NULL);
    sem_destroy(&patientWaiting);
    sem_destroy(&treatmentDone);
    sem_destroy(&docAvailable);
    return 0;
}