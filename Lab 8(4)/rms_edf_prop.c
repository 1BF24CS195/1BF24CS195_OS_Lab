#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id;
    int burst;
    int deadline;
    int period;
    int weight; 
    int ct, wt, tat;
} Process;

void edf(Process p[], int n) {
    float util = 0;

    for (int i = 0; i < n; i++)
        util += (float)p[i].burst / p[i].deadline;

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].deadline > p[j].deadline) {
                Process t = p[i]; p[i] = p[j]; p[j] = t;
            }

    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].burst;
        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].burst;
    }

    printf("\n===== EDF Scheduling =====\n");
    printf("Utilization = %.2f\n", util);
    printf("Schedulable if U <= 1\n");

    printf("ID\tBT\tDL\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].burst, p[i].deadline,
               p[i].ct, p[i].wt, p[i].tat);
}

void rms(Process p[], int n) {
    float util = 0;

    for (int i = 0; i < n; i++)
        util += (float)p[i].burst / p[i].period;

    float bound = n * (pow(2, (float)1/n) - 1);

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].period > p[j].period) {
                Process t = p[i]; p[i] = p[j]; p[j] = t;
            }

    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].burst;
        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].burst;
    }

    printf("\n===== RMS Scheduling =====\n");
    printf("Utilization = %.2f\n", util);
    printf("RM Bound = %.4f\n", bound);

    if (util <= bound)
        printf("Schedulable\n");
    else
        printf("Not guaranteed schedulable\n");

    printf("ID\tBT\tPeriod\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].burst, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
}

void proportional(Process p[], int n) {
    int total_weight = 0;

    for (int i = 0; i < n; i++)
        total_weight += p[i].weight;

    printf("\n===== Proportional Scheduling =====\n");
    printf("Total Weight = %d\n", total_weight);

    printf("ID\tWeight\tCPU Share\n");

    for (int i = 0; i < n; i++) {
        float share = (float)p[i].weight / total_weight;
        printf("%d\t%d\t%.2f\n", p[i].id, p[i].weight, share);
    }
}

int main() {
    int n;
    Process p1[MAX], p2[MAX], p3[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);

        p1[i].id = p2[i].id = p3[i].id = i;

        printf("Burst Time: ");
        scanf("%d", &p1[i].burst);

        printf("Deadline (EDF): ");
        scanf("%d", &p1[i].deadline);

        printf("Period (RMS): ");
        scanf("%d", &p1[i].period);

        printf("Weight (Proportional): ");
        scanf("%d", &p1[i].weight);

        p2[i] = p1[i];
        p3[i] = p1[i];
    }

    edf(p1, n);
    rms(p2, n);
    proportional(p3, n);

    return 0;
}