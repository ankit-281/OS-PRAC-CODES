#include <stdio.h>
#include <conio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stdbool.h>
#include <limits.h>
// #include <math.h>
// #include <time.h>
// #include <ctype.h>
void main() {
  int n, i, j, completed=0, time = 0, idle = 0, total_wt = 0, total_tat = 0;
  float avg_wt=0, avg_tat=0;
  typedef struct {
    int pid;
    int done;
    int at;
    int bt;
    int rbt;
    int ct;
    int tat;
    int wt;
  } Process;
  Process p[10];

  printf("Enter no. of processes: ");
  scanf("%d", &n);
  for(i = 0; i < n; i++) {
    p[i].pid = i + 1;
    p[i].done=0;
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
    p[i].rbt = p[i].bt;
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

  printf("Gannt chart:\n");
  int prev=-1;
  while(completed<n) {
    int mini = -1, minrbt = INT_MAX;
    for(i=0;i<n;i++) {
      if(p[i].at<=time && p[i].done==0 && minrbt>p[i].rbt) {
        minrbt = p[i].rbt;
        mini = i;
      }
    }

    if(mini==-1) {
      idle++;
      time++;
      if(prev!=-2) {
        printf("%d  IDLE  ",time-1);
        prev=-2;
      }

    }
    else {
      time++;
      p[mini].rbt--;

      if(prev!=p[mini].pid) {
        prev=p[mini].pid;
        printf("%d  P%d  ",time-1,p[mini].pid);
      }

      if(p[mini].rbt==0) {
        completed++;
        p[mini].done=1;

        p[mini].ct = time;
        p[mini].tat = p[mini].ct - p[mini].at;
        p[mini].wt = p[mini].tat - p[mini].bt;
        total_tat += p[mini].tat;
        total_wt += p[mini].wt;
      }
    }
  }
  printf("%d  ",time);
}