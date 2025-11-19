#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_CAPACITY 5000
#define MAX_RUNWAYS 100
#define TAKEOFF_START_ID 1
#define LANDING_START_ID 5001

typedef struct
{
    int id;
    int requestTime;
} Plane;

typedef struct
{
    Plane data[QUEUE_CAPACITY];
    int head;
    int tail;
    int size;
} SeqQueue;

typedef struct
{
    int busy;
    int freeAt;
    int totalBusy;
} Runway;

SeqQueue landingQueue;
SeqQueue takeoffQueue;
Runway runways[MAX_RUNWAYS];
int runwayCount = 0;
int landTime = 0;
int takeoffTime = 0;
int nextTakeoffId = TAKEOFF_START_ID;
int nextLandingId = LANDING_START_ID;
long totalLandingWait = 0;
long totalTakeoffWait = 0;
int totalLandingPlanes = 0;
int totalTakeoffPlanes = 0;
int currentTime = 0;
int airportClosed = 0;

void initQueue(SeqQueue *q)
{
    q->head = 0;
    q->size = 0;
    q->tail = 0;
}

int isEmpty(SeqQueue *q)
{
    return q->size == 0;
}

int isFull(SeqQueue *q)
{
    return q->size == QUEUE_CAPACITY;
}

int enqueue(SeqQueue *q, Plane p)
{
    if(isFull(q)) return -1;
    q->data[q->tail] = p;
    q->tail = (q->tail + 1) % QUEUE_CAPACITY;
    q->size++;
    return 0;
}

int dequeue(SeqQueue *q, Plane *p)
{
    if(isEmpty(q)) return -1;
    if(p)
    {
        *p = q->data[q->head];
        q->head = (q->head + 1) % QUEUE_CAPACITY;
        q->size--;
        return 0;
    }
    return 0;
}

void initRunways(int n)
{
    for(int i = 0; i < n; ++i)
    {
        runways[i].busy = 0;
        runways[i].freeAt = 0;
        runways[i].totalBusy = 0;
    }
}

int allRunwaysFree()
{
    for (int i = 0; i < runwayCount; i++)
    {
        if (runways[i].busy)
            return 0;
    }
    return 1;
}

void printCurrentTimeHeader(int time)
{
    printf("Current Time: %4d\n", time);
}

void printRunwayFree(int runwayIndex)
{
    printf("runway %02d is free\n", runwayIndex + 1);
}

void printPlaneLanding(int planeId, int runwayIndex)
{
    printf("airplane %04d is ready to land on runway %02d\n", planeId, runwayIndex + 1);
}

void printPlaneTakeoff(int planeId, int runwayIndex)
{
    printf("airplane %04d is ready to takeoff on runway %02d\n", planeId, runwayIndex + 1);
}

void printSimulationFinished()
{
    printf("simulation finished\n");
}

void printFinalStatistics(int simTime)
{
    printf("simulation time: %4d\n", simTime);

    double avgLandingWait = 0.0;
    double avgTakeoffWait = 0.0;
    if(totalLandingPlanes > 0) avgLandingWait = (double)totalLandingWait / totalLandingPlanes;
    if(totalTakeoffPlanes > 0) avgTakeoffWait = (double)totalTakeoffWait / totalTakeoffPlanes;

    printf("average waiting time of landing: %4.1f\n", avgLandingWait);
    printf("average waiting time of takeoff: %4.1f\n", avgTakeoffWait);

    long sumBusy = 0;
    for(int i = 0; i < runwayCount; i++)
    {
        printf("runway %02d busy time: %4d\n", i + 1, runways[i].totalBusy);
        sumBusy += runways[i].totalBusy;
    }

    double avgBusy = 0.0;
    if(runwayCount > 0)
    {
        avgBusy = (double)sumBusy / runwayCount;
    }
    double percent = 0.0;
    if(simTime > 0)
    {
        percent = avgBusy * 100.0 / simTime;
    }
    printf("runway average busy time percentage: %4.1f%%\n", percent);
}

int main()
{
    initQueue(&landingQueue);
    initQueue(&takeoffQueue);
    scanf("%d %d %d", &runwayCount, &landTime, &takeoffTime);
    if (runwayCount > MAX_RUNWAYS)
        runwayCount = MAX_RUNWAYS;
    initRunways(runwayCount);
    
    while(1)
    {
        printCurrentTimeHeader(currentTime);
        
        for(int i = 0; i < runwayCount; i++)
        {
            if(runways[i].busy && runways[i].freeAt == currentTime)
            {
                runways[i].busy = 0;
                runways[i].freeAt = 0;
                printRunwayFree(i);
            }
        }

        if(airportClosed && isEmpty(&landingQueue) && isEmpty(&takeoffQueue) && allRunwaysFree())
        {
            printSimulationFinished();
            printFinalStatistics(currentTime);
            break;
        }

        int newLanding = 0, newTakeoff = 0;
        if(!airportClosed)
        {
            scanf("%d %d", &newLanding, &newTakeoff);
            if(newLanding == -1 && newTakeoff == -1)
            {
                airportClosed = 1;
                newLanding = 0;
                newTakeoff = 0;
            }
        }
        else
        {
            newLanding = 0;
            newTakeoff = 0;
        }

        for(int i = 0; i < newLanding; i++)
        {
            Plane p;
            p.id = nextLandingId++;
            p.requestTime = currentTime;
            enqueue(&landingQueue, p);
        }

        for(int i = 0; i < newTakeoff; i++)
        {
            Plane p;
            p.id = nextTakeoffId++;
            p.requestTime = currentTime;
            enqueue(&takeoffQueue, p);
        }

        for(int i = 0; i < runwayCount; i++)
        {
            if(!runways[i].busy)
            {
                if(!isEmpty(&landingQueue))
                {
                    Plane p;
                    dequeue(&landingQueue, &p);
                    totalLandingWait += (currentTime - p.requestTime);
                    totalLandingPlanes++;
                    runways[i].busy = 1;
                    runways[i].freeAt = currentTime + landTime;
                    printPlaneLanding(p.id, i);
                }
                else if(!isEmpty(&takeoffQueue))
                {
                    Plane p;
                    dequeue(&takeoffQueue, &p);
                    totalTakeoffWait += (currentTime - p.requestTime);
                    totalTakeoffPlanes++;
                    runways[i].busy = 1;
                    runways[i].freeAt = currentTime + takeoffTime;
                    printPlaneTakeoff(p.id, i);
                }
            }
        }

        for(int i = 0; i < runwayCount; ++i)
        {
            if(runways[i].busy && runways[i].freeAt > currentTime)
            {
                runways[i].totalBusy++;
            }
        }
    
        currentTime++;
    }

    return 0;
}