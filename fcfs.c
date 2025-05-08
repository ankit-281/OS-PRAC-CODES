#include <stdio.h>
#include <conio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>
// #include <limits.h>
// #include <math.h>
// #include <time.h>
// #include <ctype.h>
void main() {
  int n, i, j, time = 0, idle = 0, total_wt = 0, total_tat = 0;
  float avg_wt=0, avg_tat=0;
  typedef struct {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
  } Process;
  Process p[10];

  printf("Enter no. of processes: ");
  scanf("%d", &n);
  for(i = 0; i < n; i++) {
    p[i].pid = i + 1;
  }
  printf("Enter the arrival time of each process:\n");
  for(i = 0; i < n; i++) {
    printf("Process %d: ", i + 1);
    scanf("%d", &p[i].at);
  }
  printf("Enter the burst time of each process:\n");
  for(i = 0; i < n; i++) {
    printf("Process %d: ", i + 1);
    scanf("%d", &p[i].bt);
  }

  for(i=0;i<n;i++) {
    for(j=0;j<n-i-1;j++) {
      if(p[j].at>p[j+1].at) {
        Process temp = p[j];
        p[j] = p[j+1];
        p[j+1] = temp;
      }
    }
  }

  printf("Gannt chart:\n0  ");
  for(i=0;i<n;i++) {
    if(time<p[i].at) {
      idle+=p[i].at-time;
      time=p[i].at;
      printf("IDLE  %d  ",time);
    }
    p[i].ct = time+p[i].bt;
    time+=p[i].bt;
    printf("P%d  %d  ",p[i].pid,time);
  }

  printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
  for(i = 0; i < n; i++) {
      p[i].tat = p[i].ct - p[i].at;
      p[i].wt = p[i].tat - p[i].bt;
      total_tat += p[i].tat;
      total_wt += p[i].wt;
      printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
  }
  avg_tat = (float)total_tat / n;
  avg_wt = (float)total_wt / n;

  printf("\nAverage Turnaround Time = %.2f", avg_tat);
  printf("\nAverage Waiting Time = %.2f", avg_wt);
  printf("\nTotal Idle Time = %d\n", idle);
}