#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int n, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;

        printf("\nProcess P%d:\n", p[i].id);

        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].arrivalTime);

        printf("Enter Burst Time: ");
        scanf("%d", &p[i].burstTime);

        printf("Enter Priority (lower number = higher priority): ");
        scanf("%d", &p[i].priority);

        p[i].remainingTime = p[i].burstTime;

        p[i].completionTime = 0;
        p[i].waitingTime = 0;
        p[i].turnaroundTime = 0;
    }

    int time = p[0].arrivalTime;

    for (i = 1; i < n; i++)
        if (p[i].arrivalTime < time)
            time = p[i].arrivalTime;

    int completed = 0;
    float totalWaitingTime = 0.0f;

    while (completed < n) {

        int sel = -1;
        int bestPr = 1e9;

        for (i = 0; i < n; i++) {
            if (p[i].remainingTime > 0 && p[i].arrivalTime <= time) {
                if (p[i].priority < bestPr) {
                    bestPr = p[i].priority;
                    sel = i;
                }
            }
        }

        if (sel == -1) {
            int nextArrival = 1e9;

            for (i = 0; i < n; i++)
                if (p[i].remainingTime > 0 && p[i].arrivalTime < nextArrival)
                    nextArrival = p[i].arrivalTime;

            time = nextArrival;
            continue;
        }

        p[sel].remainingTime--;
        time++;

        if (p[sel].remainingTime == 0) {
            p[sel].completionTime = time;

            p[sel].turnaroundTime = p[sel].completionTime - p[sel].arrivalTime;

            p[sel].waitingTime = p[sel].turnaroundTime - p[sel].burstTime;

            totalWaitingTime += p[sel].waitingTime;

            completed++;
        }
    }

    printf("\n--- Priority Preemptive Scheduling (with Arrival Times) ---\n");
    printf("--------------------------------------------------------------------------\n");

    printf("%-6s %-12s %-10s %-10s %-12s %-12s %-10s\n",
           "PID", "Arrival", "Burst", "Priority", "Completion", "Turnaround", "Waiting");
    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("P%-5d %-12d %-10d %-10d %-12d %-12d %-10d\n",
               p[i].id,
               p[i].arrivalTime,
               p[i].burstTime,
               p[i].priority,
               p[i].completionTime,
               p[i].turnaroundTime,
               p[i].waitingTime);
    }

    printf("--------------------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);

    return 0;
}