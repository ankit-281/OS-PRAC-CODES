#include <stdio.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int id, at, bt, rt, ct, tat, wt;
    bool completed, inQueue;
} Process;

int queue[MAX];
int front = -1, rear = -1;

void enqueue(int val) {
    if ((rear + 1) % MAX == front) return; // queue full
    if (front == -1) front = 0;
    rear = (rear + 1) % MAX;
    queue[rear] = val;
}

int dequeue() {
    if (front == -1) return -1; // queue empty
    int val = queue[front];
    if (front == rear) front = rear = -1;
    else front = (front + 1) % MAX;
    return val;
}

int main() {
    int n, tq, time = 0, complete = 0;
    float avgTAT = 0, avgWT = 0;

    printf("This is Round Robin process scheduling\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
        p[i].rt = p[i].bt;
        p[i].completed = false;
        p[i].inQueue = false;
    }

    // Sort by arrival time
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].at > p[j+1].at) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    printf("\nGantt Chart:\n");

    if (p[0].at > 0) {
        printf("%d IDLE %d ", time, p[0].at);
        time = p[0].at;
    }

    enqueue(0);
    p[0].inQueue = true;

    while (complete < n) {
        int idx = dequeue();

        if (idx == -1) {
            printf("%d IDLE ", time);
            time++;

            for (int i = 0; i < n; i++) {
                if (!p[i].inQueue && !p[i].completed && p[i].at <= time) {
                    enqueue(i);
                    p[i].inQueue = true;
                }
            }

            continue;
        }

        int execTime = (p[idx].rt > tq) ? tq : p[idx].rt;
        printf("%d P%d ", time, p[idx].id);
        time += execTime;
        p[idx].rt -= execTime;

        // Check for new arrivals
        for (int i = 0; i < n; i++) {
            if (!p[i].inQueue && !p[i].completed && p[i].at <= time) {
                enqueue(i);
                p[i].inQueue = true;
            }
        }

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = true;
            complete++;
        } else {
            enqueue(idx);
        }
    }
    printf("%d\n", time); // Print final time

    // Print table
    printf("\nId\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        avgTAT += p[i].tat;
        avgWT += p[i].wt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("Avg TAT: %.2f, Avg WT: %.2f\n", avgTAT / n, avgWT / n);
    return 0;
}
