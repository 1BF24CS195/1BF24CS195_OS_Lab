#include <stdio.h>

int main() {
    int nb, np, i, j;

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);

    int blockSize[nb];

    printf("Enter sizes of %d memory blocks:\n", nb);
    for(i = 0; i < nb; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &np);

    int process[np];

    printf("Enter sizes of %d processes:\n", np);
    for(i = 0; i < np; i++) {
        scanf("%d", &process[i]);
    }

    int firstFit[np], bestFit[np], worstFit[np];

    for(i = 0; i < np; i++) {
        firstFit[i] = -1;
        bestFit[i] = -1;
        worstFit[i] = -1;
    }

    // ---------------- FIRST FIT ----------------
    int used1[nb];

    for(i = 0; i < nb; i++)
        used1[i] = 0;

    for(i = 0; i < np; i++) {
        for(j = 0; j < nb; j++) {
            if(!used1[j] && blockSize[j] >= process[i]) {
                firstFit[i] = j;
                used1[j] = 1;
                break;
            }
        }
    }

    // ---------------- BEST FIT ----------------
    int used2[nb];

    for(i = 0; i < nb; i++)
        used2[i] = 0;

    for(i = 0; i < np; i++) {
        int best = -1;

        for(j = 0; j < nb; j++) {
            if(!used2[j] && blockSize[j] >= process[i]) {

                if(best == -1 || blockSize[j] < blockSize[best]) {
                    best = j;
                }
            }
        }

        if(best != -1) {
            bestFit[i] = best;
            used2[best] = 1;
        }
    }

    // ---------------- WORST FIT ----------------
    int used3[nb];

    for(i = 0; i < nb; i++)
        used3[i] = 0;

    for(i = 0; i < np; i++) {
        int worst = -1;

        for(j = 0; j < nb; j++) {
            if(!used3[j] && blockSize[j] >= process[i]) {

                if(worst == -1 || blockSize[j] > blockSize[worst]) {
                    worst = j;
                }
            }
        }

        if(worst != -1) {
            worstFit[i] = worst;
            used3[worst] = 1;
        }
    }

    printf("\n--- First Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(i = 0; i < np; i++) {
        if(firstFit[i] != -1)
            printf("%d\t\t%d\t\t%d\n", i + 1, process[i], firstFit[i] + 1);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, process[i]);
    }

    printf("\n--- Best Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(i = 0; i < np; i++) {
        if(bestFit[i] != -1)
            printf("%d\t\t%d\t\t%d\n", i + 1, process[i], bestFit[i] + 1);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, process[i]);
    }

    printf("\n--- Worst Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(i = 0; i < np; i++) {
        if(worstFit[i] != -1)
            printf("%d\t\t%d\t\t%d\n", i + 1, process[i], worstFit[i] + 1);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, process[i]);
    }

    return 0;
}
