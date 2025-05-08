#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include <stdbool.h>
#include <limits.h>
// #include <math.h>
// #include <time.h>
// #include <ctype.h>

int n, m, max[10][10], allocation[10][10], need[10][10], total[10], available[10], work[10], finish[10], safeseq[10];

int checksafeseq() {
  int i, j, k=0, count = 0, found;
  while(count<n) {
    found=0;
    for(i=0;i<n;i++) {
      if(finish[i]==0) {
        for(j=0;j<m;j++) {
          if(work[j]<need[i][j])
            break;
        }
        if(j==m) {
          for(j=0;j<m;j++)
            work[j]+=allocation[i][j];
          safeseq[k++]=i;
          finish[i]=1;
          count++;
          found = 1;
        }
      }
    }
    if(found==0)
      return 0;
  }
  return 1;
}

void main() {
  int i,j;
  printf("Enter number of processes: ");
  scanf("%d", &n);
  printf("Enter number of types of resources: ");
  scanf("%d", &m);
  printf("Enter current allocation matrix:\n");
  for(i=0;i<n;i++) {
    for(j=0;j<m;j++) {
      scanf("%d", &allocation[i][j]);
    }
  }
  printf("Enter max allocation matrix:\n");
  for(i=0;i<n;i++) {
    for(j=0;j<m;j++) {
      scanf("%d", &max[i][j]);
    }
  }
  printf("Enter total instances of each resource:\n");
  for(j = 0; j < m; j++) {
    scanf("%d", &total[j]);
    available[j] = total[j];
  }

  for(i=0;i<n;i++) {
    finish[i]=0;
    for(j=0;j<m;j++) {
      need[i][j]=max[i][j]-allocation[i][j];
      available[j] = available[j] - allocation[i][j];
    }
  }
  for(j=0;j<m;j++) {
    work[j] = available[j];
  }

  if(checksafeseq()) {
    for(i=0;i<n;i++)
      printf("P%d   ", safeseq[i]);
  }
  else
    printf("Unsafe sequence");
}