#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================= Common Printing Function ================= */
void print_result(int n, int at[], int bt[], int ct[],
                  int tat[], int wt[],
                  int gantt[], int time_mark[], int g){

    float sum_tat=0, sum_wt=0;
    int i;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
        sum_tat+=tat[i];
        sum_wt+=wt[i];
    }

    printf("\nAverage TAT: %.2f", sum_tat/n);
    printf("\nAverage WT: %.2f\n", sum_wt/n);

    printf("\nGantt Chart:\n");

    /* Print top bar */
    for(i=0;i<g;i++){
        if(gantt[i]==-1)
            printf("| IDLE  ");
        else
            printf("|  P%-1d  ", gantt[i]+1);
    }
    printf("|\n");

    /* Print time marks perfectly aligned */
    int width = 7; // width of each box
    printf("%-4d", time_mark[0]);
    for(i=1;i<=g;i++){
        printf("%*d", width, time_mark[i]);
    }
    printf("\n");
}

/* ================= FCFS ================= */
void fcfs(int n, int at[], int bt[]){

    int ct[n], tat[n], wt[n];
    int gantt[1000], time_mark[1000];
    int i, current_time=0, g=0;

    time_mark[0]=0;

    for(i=0;i<n;i++){

        while(current_time < at[i]){
            gantt[g] = -1;   // IDLE
            current_time++;
            time_mark[++g] = current_time;
        }

        gantt[g] = i;
        current_time += bt[i];
        time_mark[++g] = current_time;

        ct[i] = current_time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    print_result(n,at,bt,ct,tat,wt,gantt,time_mark,g);
}

/* ================= Non Preemptive SJF ================= */
void np_sjf(int n, int at[], int bt[]){

    int ct[n], tat[n], wt[n], visited[n];
    int gantt[1000], time_mark[1000];
    int completed=0,current_time=0,g=0,i;

    for(i=0;i<n;i++) visited[i]=0;
    time_mark[0]=0;

    while(completed<n){

        int idx=-1,min=9999;

        for(i=0;i<n;i++)
            if(at[i]<=current_time && !visited[i] && bt[i]<min){
                min=bt[i];
                idx=i;
            }

        if(idx==-1){
            gantt[g]=-1;   // IDLE
            current_time++;
            time_mark[++g]=current_time;
        }
        else{
            gantt[g]=idx;
            current_time+=bt[idx];
            time_mark[++g]=current_time;

            ct[idx]=current_time;
            tat[idx]=ct[idx]-at[idx];
            wt[idx]=tat[idx]-bt[idx];

            visited[idx]=1;
            completed++;
        }
    }

    print_result(n,at,bt,ct,tat,wt,gantt,time_mark,g);
}

/* ================= Preemptive SJF ================= */
void p_sjf(int n, int at[], int bt[]){

    int rt[n], ct[n], tat[n], wt[n];
    int gantt[1000], time_mark[1000];
    int completed=0,current_time=0,g=0,i;

    for(i=0;i<n;i++) rt[i]=bt[i];
    time_mark[0]=0;

    while(completed<n){

        int idx=-1,min=9999;

        for(i=0;i<n;i++)
            if(at[i]<=current_time && rt[i]>0 && rt[i]<min){
                min=rt[i];
                idx=i;
            }

        if(idx==-1){
            gantt[g]=-1;
            current_time++;
            time_mark[++g]=current_time;
        }
        else{
            gantt[g]=idx;
            rt[idx]--;
            current_time++;
            time_mark[++g]=current_time;

            if(rt[idx]==0){
                ct[idx]=current_time;
                tat[idx]=ct[idx]-at[idx];
                wt[idx]=tat[idx]-bt[idx];
                completed++;
            }
        }
    }

    print_result(n,at,bt,ct,tat,wt,gantt,time_mark,g);
}

/* ================= Non Preemptive Priority ================= */
void np_priority(int n, int at[], int bt[], int pr[]){

    int ct[n], tat[n], wt[n], visited[n];
    int gantt[1000], time_mark[1000];
    int completed=0,current_time=0,g=0,i;

    for(i=0;i<n;i++) visited[i]=0;
    time_mark[0]=0;

    while(completed<n){

        int idx=-1,high=9999;

        for(i=0;i<n;i++)
            if(at[i]<=current_time && !visited[i] && pr[i]<high){
                high=pr[i];
                idx=i;
            }

        if(idx==-1){
            gantt[g]=-1; // IDLE
            current_time++;
            time_mark[++g]=current_time;
        }
        else{
            gantt[g]=idx;
            current_time+=bt[idx];
            time_mark[++g]=current_time;

            ct[idx]=current_time;
            tat[idx]=ct[idx]-at[idx];
            wt[idx]=tat[idx]-bt[idx];

            visited[idx]=1;
            completed++;
        }
    }

    print_result(n,at,bt,ct,tat,wt,gantt,time_mark,g);
}

/* ================= Preemptive Priority ================= */
void p_priority(int n, int at[], int bt[], int pr[]){

    int rt[n], ct[n], tat[n], wt[n];
    int gantt[1000], time_mark[1000];
    int completed=0,current_time=0,g=0,i;

    for(i=0;i<n;i++) rt[i]=bt[i];
    time_mark[0]=0;

    while(completed<n){

        int idx=-1,high=9999;

        for(i=0;i<n;i++)
            if(at[i]<=current_time && rt[i]>0 && pr[i]<high){
                high=pr[i];
                idx=i;
            }

        if(idx==-1){
            gantt[g]=-1;
            current_time++;
            time_mark[++g]=current_time;
        }
        else{
            gantt[g]=idx;
            rt[idx]--;
            current_time++;
            time_mark[++g]=current_time;

            if(rt[idx]==0){
                ct[idx]=current_time;
                tat[idx]=ct[idx]-at[idx];
                wt[idx]=tat[idx]-bt[idx];
                completed++;
            }
        }
    }

    print_result(n,at,bt,ct,tat,wt,gantt,time_mark,g);
}

/* ================= Round Robin ================= */
void round_robin(int n, int at[], int bt[], int tq){

    int rt[n], ct[n], tat[n], wt[n];
    int queue[1000], front=0,rear=0;
    int gantt[1000], time_mark[1000];
    int visited[n];
    int completed=0,current_time=0,g=0,i;

    for(i=0;i<n;i++){
        rt[i]=bt[i];
        visited[i]=0;
    }

    time_mark[0]=0;

    printf("\nReady Queue during execution:\n");

    while(completed<n){

        // Add newly arrived processes
        for(i=0;i<n;i++){
            if(at[i]<=current_time && !visited[i]){
                queue[rear++]=i;
                visited[i]=1;
            }
        }

        if(front==rear){
            gantt[g]=-1; // IDLE
            current_time++;
            time_mark[++g]=current_time;
            continue;
        }

        // Print ready queue BEFORE execution
        printf("Time %d: Ready Queue = ", current_time);
        for(i=front;i<rear;i++){
            printf("P%d ", queue[i]+1);
        }
        printf("\n");

        int idx=queue[front++]; // take first process

        gantt[g]=idx;

        if(rt[idx]>tq){
            current_time+=tq;
            rt[idx]-=tq;
        }else{
            current_time+=rt[idx];
            rt[idx]=0;
            ct[idx]=current_time;
            completed++;
        }

        time_mark[++g]=current_time;

        // Add newly arrived processes after execution (next time)
        for(i=0;i<n;i++){
            if(at[i]<=current_time && !visited[i]){
                queue[rear++]=i;
                visited[i]=1;
            }
        }

        // If process not finished, re-add to queue
        if(rt[idx]>0)
            queue[rear++]=idx;
    }

    for(i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
    }

    print_result(n,at,bt,ct,tat,wt,gantt,time_mark,g);
}

/* ================= MAIN ================= */
int main(){

    int n,choice,tq;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int at[n],bt[n],pr[n];

    for(int i=0;i<n;i++){
        printf("Arrival time of P%d: ",i+1);
        scanf("%d",&at[i]);
        printf("Burst time of P%d: ",i+1);
        scanf("%d",&bt[i]);
    }

    while(1){

        printf("\n===== CPU Scheduling Simulator =====\n");
        printf("1. FCFS\n2. SJF (Non-Preemptive)\n3. SJF (Preemptive)\n");
        printf("4. Priority (Non-Preemptive)\n5. Priority (Preemptive)\n");
        printf("6. Round Robin\n0. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){

            case 1: fcfs(n,at,bt); break;
            case 2: np_sjf(n,at,bt); break;
            case 3: p_sjf(n,at,bt); break;
            case 4:
                for(int i=0;i<n;i++){
                    printf("Priority of P%d: ",i+1);
                    scanf("%d",&pr[i]);
                }
                np_priority(n,at,bt,pr); break;
            case 5:
                for(int i=0;i<n;i++){
                    printf("Priority of P%d: ",i+1);
                    scanf("%d",&pr[i]);
                }
                p_priority(n,at,bt,pr); break;
            case 6:
                printf("Enter Time Quantum: ");
                scanf("%d",&tq);
                round_robin(n,at,bt,tq); break;
            case 0: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}