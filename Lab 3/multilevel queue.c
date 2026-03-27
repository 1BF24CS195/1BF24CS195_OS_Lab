#include <stdio.h>
#include <string.h>
#define MAX_PROCESSES 100

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int type;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int started;
    int start_time;
} Process;

typedef struct {
    int items[MAX_PROCESSES];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

int isEmpty(Queue* q) {
    return q->rear < q->front;
}

void enqueue(Queue* q, int value) {
    if (q->rear < MAX_PROCESSES - 1) {
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    if (!isEmpty(q)) {
        int val = q->items[q->front];
        q->front++;
        return val;
    }
    return -1;
}

int compareArrival(const void* a, const void* b) {
    Process* p1 = (Process*)a;
    Process* p2 = (Process*)b;
    if (p1->arrival_time < p2->arrival_time)
        return -1;
    else if (p1->arrival_time > p2->arrival_time)
        return 1;
    else
        return 0;
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);
        printf("Enter arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &processes[i].type);

        processes[i].process_id = i;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].started = 0;
        processes[i].start_time = -1;
    }

    qsort(processes, n, sizeof(Process), compareArrival);

    Queue systemQueue, userQueue;
    initQueue(&systemQueue);
    initQueue(&userQueue);

    int completed = 0;
    int current_time = 0;
    int i = 0;
    Process* current_process = NULL;

    while (completed < n) {
        while (i < n && processes[i].arrival_time <= current_time) {
            if (processes[i].type == 0)
                enqueue(&systemQueue, i);
            else
                enqueue(&userQueue, i);
            i++;
        }

        if (current_process != NULL) {
            if (current_process->type == 1 && !isEmpty(&systemQueue)) {
                enqueue(&userQueue, current_process - processes);
                current_process = NULL;
            }
        }

        if (current_process == NULL) {
            if (!isEmpty(&systemQueue)) {
                int idx = dequeue(&systemQueue);
                current_process = &processes[idx];
            } else if (!isEmpty(&userQueue)) {
                int idx = dequeue(&userQueue);
                current_process = &processes[idx];
            } else {
                current_time++;
                continue;
            }
        }

        if (current_process->started == 0) {
            current_process->start_time = current_time;
            current_process->started = 1;
        }

        current_process->remaining_time--;
        current_time++;

        if (current_process->remaining_time == 0) {
            current_process->completion_time = current_time;
            current_process->turnaround_time = current_process->completion_time - current_process->arrival_time;
            current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
            completed++;
            current_process = NULL;
        }
    }

    printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");
    double total_wt = 0, total_tat = 0;
    for (int j = 0; j < n; j++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               processes[j].process_id,
               (processes[j].type == 0) ? "System" : "User",
               processes[j].arrival_time,
               processes[j].burst_time,
               processes[j].completion_time,
               processes[j].waiting_time,
               processes[j].turnaround_time);

        total_wt += processes[j].waiting_time;
        total_tat += processes[j].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
