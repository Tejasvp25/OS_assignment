/**
 * @file sce_q2.c
 * @brief Clinic problem solution for OS SCE
 * @author Tejasvp25
 * Contact: tejasvp25@gmail.com
 * 
 * https://github.com/Tejasvp25/OS_assignment/blob/main/Newfolder/sce_q2.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Using i count as Patient Name for convenience
int i = 0;
// Shared buffer acroos thread
char buffer[30] = "Shared Memory";
char msg[30];

/**
* patientWaiting - Will be Initialized to 0
* treatmentDone - Will be Initialized to 0
* docAvailable - Will be Initialized to 1
*/
sem_t patientWaiting, treatmentDone, docAvailable;

pthread_t docThread, patientThread;

// Wrapper function for sem_post()
void up(sem_t *sem)
{
    sem_post(sem);
}

// Wrapper function for sem_wait()
void down(sem_t *sem)
{
    sem_wait(sem);
}
void consultDoctor()
{
    sprintf(msg, "Doc Consulted by Patient %d\n", i);
    printf(msg);
    // Write Patient name to buffer which will be used in treatPatient()
    sprintf(buffer, "Patient Name is %d \n", i);
}
void treatPatient()
{
    sprintf(msg, "Treating Patient : %s", buffer);
    printf(msg);
    // Write Treatment to buffer which will be used in noteTreatment()
    sprintf(buffer, "Treatment for Patient %d \n", i);
}
void noteTreatment()
{
    sprintf(msg, "Treatment Noted : %s\n\n", buffer);
    printf(msg);
    i++;
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
    /**
     * initialize semaphore
     * param1: Reference to semaphore
     * param2: pshared , non-zero = Shared between processes , 0 = Shared between threads
     * param3: initial value
    */
    sem_init(&patientWaiting, 0, 0);
    sem_init(&treatmentDone, 0, 0);
    sem_init(&docAvailable, 0, 1);

    /**
     * Create thread for patientThread and docThread
     * param1: reference to thread
     * param2: thread attributes
     * param3: routine
     * param4: Routine arguments
    */
    pthread_create(&patientThread, NULL, patientProcess, NULL);
    pthread_create(&docThread, NULL, doctorProcess, NULL);

    /**
     * Wait for thread to end
     * status contains a pointer to the status argument passed by the ending thread as part of pthread_exit().
    */
    pthread_join(docThread, NULL);
    pthread_join(patientThread, NULL);

    // Destroy all semaphores
    sem_destroy(&patientWaiting);
    sem_destroy(&treatmentDone);
    sem_destroy(&docAvailable);
    return 0;
}