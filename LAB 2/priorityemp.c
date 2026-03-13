#include <stdio.h>
#include <limits.h>

int main()
{
    int n,i,time=0,completed=0;
    int at[20],bt[20],pr[20],rem_bt[20];
    int ct[20],tat[20],wt[20],rt[20];

    float avg_wt=0,avg_tat=0,avg_rt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter Arrival Time, Burst Time and Priority:\n");

    for(i=0;i<n;i++)
    {
        printf("P%d AT: ",i+1);
        scanf("%d",&at[i]);

        printf("P%d BT: ",i+1);
        scanf("%d",&bt[i]);

        printf("P%d Priority: ",i+1);
        scanf("%d",&pr[i]);

        rem_bt[i]=bt[i];
        rt[i]=-1;
    }

    while(completed<n)
    {
        int highest=-1;
        int min_pr=INT_MAX;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && rem_bt[i]>0 && pr[i]<min_pr)
            {
                min_pr=pr[i];
                highest=i;
            }
        }

        if(highest==-1)
        {
            time++;
            continue;
        }

        if(rt[highest]==-1)
            rt[highest] = time - at[highest];

        rem_bt[highest]--;
        time++;

        if(rem_bt[highest]==0)
        {
            completed++;

            ct[highest]=time;
            tat[highest]=ct[highest]-at[highest];
            wt[highest]=tat[highest]-bt[highest];

            avg_wt+=wt[highest];
            avg_tat+=tat[highest];
            avg_rt+=rt[highest];
        }
    }

    printf("\nProcess AT BT PR CT TAT WT RT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d     %d  %d  %d  %d  %d   %d  %d\n",
        i+1,at[i],bt[i],pr[i],ct[i],tat[i],wt[i],rt[i]);
    }

    printf("\nAverage Waiting Time = %.2f",avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f",avg_tat/n);
    printf("\nAverage Response Time = %.2f\n",avg_rt/n);

    return 0;
}
