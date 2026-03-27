#include <stdio.h>

void roundRobin(int n, int at[], int bt[], int tq) {
    int rt[n], ct[n], wt[n], tat[n], resp[n];

    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
        resp[i] = -1;
    }

    int time = 0, completed = 0;

    while (completed < n) {
        int idle = 1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                idle = 0;

                if (resp[i] == -1) {
                    resp[i] = time - at[i];
                }

                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    ct[i] = time;
                    rt[i] = 0;
                    completed++;
                }
            }
        }

        if (idle) {
            time++;
        }
    }

    float total_wt = 0, total_tat = 0, total_rt = 0;

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += resp[i];
    }

    printf("\nTime Quantum = %d\n", tq);
    printf("Process\tAT\tBT\tCT\tWT\tTAT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i], resp[i]);
    }

    printf("Average WT = %.2f\n", total_wt / n);
    printf("Average TAT = %.2f\n", total_tat / n);
    printf("Average RT = %.2f\n", total_rt / n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n];

    for (int i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    int num_q, tq;

    printf("\nEnter number of different Time Quantums: ");
    scanf("%d", &num_q);

    for (int i = 0; i < num_q; i++) {
        printf("\nEnter Time Quantum %d: ", i + 1);
        scanf("%d", &tq);

        roundRobin(n, at, bt, tq);
    }

    return 0;
}
