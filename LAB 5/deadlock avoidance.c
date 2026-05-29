#include <stdio.h>

int main() {
    int n, m, i, j, k, ch;

    printf("Enter no. of processes: ");
    scanf("%d", &n);

    printf("Enter no. of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m], work[m], finish[n], safe[n];

    printf("Enter Allocation Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&max[i][j]);

    printf("Enter Available Resources:\n");
    for(i=0;i<m;i++)
        scanf("%d",&avail[i]);

    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            need[i][j]=max[i][j]-alloc[i][j];

    printf("\n1. Safety Algorithm");
    printf("\n2. Resource Request");
    printf("\nEnter choice(1 or 2): ");
    scanf("%d",&ch);

    switch(ch) {

    case 1: {
        for(i=0;i<m;i++)
            work[i]=avail[i];
        for(i=0;i<n;i++)
            finish[i]=0;
        int count=0;
        while(count<n) {
            int found=0;
            for(i=0;i<n;i++) {
                if(finish[i]==0) {
                    for(j=0;j<m;j++)
                        if(need[i][j]>work[j])
                            break;
                    if(j==m) {
                        for(k=0;k<m;k++)
                            work[k]+=alloc[i][k];
                        safe[count++]=i;
                        finish[i]=1;
                        found=1;
                    }
                }
            }
            if(found==0)
                break;
        }
        if(count==n) {
            printf("\nSAFE STATE\nSafe Sequence: ");
            for(i=0;i<n;i++)
                printf("P%d ",safe[i]);
        }
        else
            printf("\nUNSAFE STATE");
        break;
    }

    case 2: {
        int p, req[m];
        printf("Enter process number: ");
        scanf("%d",&p);
        printf("Enter Request Vector:\n");
        for(i=0;i<m;i++)
        for(i=0;i<m;i++) {
            if(req[i]>need[p][i]) {
                printf("Error: Exceeded Need");
                return 0;
            }
            if(req[i]>avail[i]) {
                printf("Resources not available");
                return 0;
            }
        }
        for(i=0;i<m;i++) {
            avail[i]-=req[i];
            alloc[p][i]+=req[i];
            need[p][i]-=req[i];
        }
        printf("\nRequest Granted\n");
        break;
    }
    default:
        printf("Invalid Choice");
    }
    return 0;
}
