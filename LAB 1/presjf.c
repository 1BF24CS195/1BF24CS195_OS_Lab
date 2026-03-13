#include <stdio.h>
#include <limits.h>

int main(){

    int n,i,time=0,completed=0;
    int at[20], bt[20], rem_bt[20];
    int ct[20], tat[20], wt[20], rt[20];
    int first[20]={0};

    float avg_wt=0, avg_tat=0, avg_rt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter Arrival Time and Burst Time:\n");

    for(i=0;i<n;i++){
        printf("P%d AT: ",i+1);
        scanf("%d",&at[i]);

        printf("P%d BT: ",i+1);
        scanf("%d",&bt[i]);

        rem_bt[i]=bt[i];
        rt[i]=-1;
    }

    while(completed<n){

        int shortest=-1;
        int min_bt=INT_MAX;

        for(i=0;i<n;i++){
            if(at[i]<=time && rem_bt[i]>0 && rem_bt[i]<min_bt){
                min_bt=rem_bt[i];
                shortest=i;
            }
        }

        if(shortest==-1){
            time++;
            continue;
        }

        if(rt[shortest]==-1)
            rt[shortest]=time-at[shortest];

        rem_bt[shortest]--;
        time++;

        if(rem_bt[shortest]==0){
            completed++;
            ct[shortest]=time;

            tat[shortest]=ct[shortest]-at[shortest];
            wt[shortest]=tat[shortest]-bt[shortest];

            avg_wt+=wt[shortest];
            avg_tat+=tat[shortest];
            avg_rt+=rt[shortest];
        }
    }

    printf("\nProcess AT BT CT TAT WT RT\n");

    for(i=0;i<n;i++){
        printf("P%d     %d  %d  %d  %d   %d  %d\n",
        i+1,at[i],bt[i],ct[i],tat[i],wt[i],rt[i]);
    }

    printf("\nAverage Waiting Time = %.2f",avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f",avg_tat/n);
    printf("\nAverage Response Time = %.2f\n",avg_rt/n);

    return 0;
}
