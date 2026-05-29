#include <stdio.h>

int fifo(int p[], int n, int f) {
    int fr[10], i, j, k = 0, fault = 0, found;

    for(i = 0; i < f; i++) fr[i] = -1;

    for(i = 0; i < n; i++) {
        found = 0;
        for(j = 0; j < f; j++)
            if(fr[j] == p[i]) found = 1;

        if(!found) {
            fr[k] = p[i];
            k = (k + 1) % f;
            fault++;
        }
    }
    return fault;
}

int lru(int p[], int n, int f) {
    int fr[10], time[10], i, j, pos, min, fault = 0;

    for(i = 0; i < f; i++) {
        fr[i] = -1;
        time[i] = -1;
    }

    for(i = 0; i < n; i++) {
        int found = 0;
        for(j = 0; j < f; j++) {
            if(fr[j] == p[i]) {
                found = 1;
                time[j] = i;
            }
        }

        if(!found) {
            min = time[0];
            pos = 0;

            for(j = 1; j < f; j++) {
                if(time[j] < min) {
                    min = time[j];
                    pos = j;
                }
            }
            fr[pos] = p[i];
            time[pos] = i;
            fault++;
        }
    }
    return fault;
}

int optimal(int p[], int n, int f) {
    int fr[10], i, j, k, pos, farthest, fault = 0;

    for(i = 0; i < f; i++)
        fr[i] = -1;

    for(i = 0; i < n; i++) {
        int found = 0;

        for(j = 0; j < f; j++) {
            if(fr[j] == p[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            pos = -1;
            farthest = -1;

            for(j = 0; j < f; j++) {
                int nextUse = -1;

                for(k = i + 1; k < n; k++) {
                    if(fr[j] == p[k]) {
                        nextUse = k;
                        break;
                    }
                }

                if(nextUse == -1) {
                    pos = j;
                    break;
                }

                if(nextUse > farthest) {
                    farthest = nextUse;
                    pos = j;
                }
            }

            fr[pos] = p[i];
            fault++;
        }
    }

    return fault;
}

int main() {
    int p[20], n, f, i;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter pages: ");
    for(i = 0; i < n; i++)
        scanf("%d", &p[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);
    printf("\nFIFO Faults    = %d", fifo(p, n, f));
    printf("\nLRU Faults     = %d", lru(p, n, f));
    printf("\nOptimal Faults = %d", optimal(p, n, f));
}
