#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int Allocation[n][m], Request[n][m];
    int Available[m];

    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &Request[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &Available[i]);
    }

    int Work[m], Finish[n];

    for(i = 0; i < m; i++)
        Work[i] = Available[i];

    for(i = 0; i < n; i++)
        Finish[i] = 0;

    int count = 0;

    while(count < n) {

        int found = 0;

        for(i = 0; i < n; i++) {

            if(Finish[i] == 0) {

                for(j = 0; j < m; j++) {
                    if(Request[i][j] > Work[j])
                        break;
                }

                if(j == m) {

                    for(k = 0; k < m; k++) {
                        Work[k] += Allocation[i][k];
                    }

                    Finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }

        if(found == 0)
            break;
    }

    int deadlock = 0;

    for(i = 0; i < n; i++) {
        if(Finish[i] == 0) {
            deadlock = 1;
            printf("Process P%d is deadlocked.\n", i);
        }
    }

    if(deadlock == 0)
        printf("\nNo Deadlock Detected.\n");

    return 0;
}
