#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

void sort(int req[], int n) {
  for(int i=0;i<n-1;i++) {
    for(int j=0;j<n-i-1;j++) {
      if(req[j]>req[j+1]) {
        int temp=req[j];
        req[j]=req[j+1];
        req[j+1]=temp;
      }
    }
  }
}

void FCFS(int req[], int n, int head) {
  int seek=0;
  printf("\nFCFS:\n");
  for(int i=0;i<n;i++) {
    printf("%d ", req[i]);
    seek+=abs(head-req[i]);
    head = req[i];
  }
  printf("\nSeek time: %d\n", seek);
}

void SSTF(int req[], int n, int head) {
  int seek = 0, done[n], count = 0;
  for(int i=0;i<n;i++) {
    done[i]=0;
  }
  printf("\nSSTF:\n");
  while(count<n) {
    int mini=-1, min = INT_MAX;
    for(int i=0;i<n;i++) {
      if(done[i]==0 && min>abs(head-req[i])) {
        mini = i;
        min = abs(head-req[i]);
      }
    }
    printf("%d ", req[mini]);
    done[mini]=1;
    count++;
    seek+=min;
    head = req[mini];
  }
  printf("\nSeek time: %d\n", seek);
}

void SCAN(int req[], int n, int head, int dir, int size){
  sort(req, n);
  int i,seek=0;
  for(i = 0; i < n; i++) {
    if(req[i] >= head)
      break;
  }
  printf("\nSCAN:\n");
  if(dir==1) {
    for(int j=i;j<n;j++) {
      printf("%d ",req[j]);
      seek+=req[j]-head;
      head = req[j];
    }
    if(head!=size-1) {
      printf("%d ",size-1);
      seek+=size-1-head;
      head = size-1;
    }
    for(int j=i-1;j>=0;j--) {
      printf("%d ",req[j]);
      seek+=head-req[j];
      head=req[j];
    }
  }
  else {
    for(int j = i - 1; j >= 0; j--) {
      printf("%d ", req[j]);
      seek += head - req[j];
      head = req[j];
    }
    if(head != 0) {
      printf("0 ");
      seek += head - 0;
      head = 0;
    }
    for(int j = i; j < n; j++) {
      printf("%d ", req[j]);
      seek += req[j] - head;
      head = req[j];
    }
  }
  printf("\nSeek time: %d\n", seek);
}

void CSCAN(int req[], int n, int head, int dir, int size) {
  sort(req, n);
  int i,seek=0;
  for(i = 0; i < n; i++) {
    if(req[i] >= head)
      break;
  }
  printf("\nC-SCAN:\n");
  if(dir==1) {
    for(int j=i;j<n;j++) {
      printf("%d ",req[j]);
      seek+=req[j]-head;
      head = req[j];
    }
    if(head!=size-1) {
      printf("%d ",size-1);
      seek+=size-1-head;
      head = size-1;
    }
    printf("0 ");
    seek+=size-1;
    head=0;
    for(int j=0;j<=i-1;j++) {
      printf("%d ",req[j]);
      seek+=head-req[j];
      head = req[j];
    }
  }
  else {
    for(int j=i-1;j>=0;j--) {
      printf("%d ",req[j]);
      seek+=head-req[j];
      head = req[j];
    }
    if(head!=0) {
      printf("0 ");
      seek+=head-0;
      head = 0;
    }
    printf("%d ",size-1);
    seek+=size-1;
    head=size-1;
    for(int j=n-1;j>=i;j--) {
      printf("%d ",req[j]);
      seek+=head-req[j];
      head = req[j];
    }
  }
  printf("\nSeek time: %d\n", seek);
}

void LOOK(int req[], int n, int head, int dir) {
  sort(req, n);
  int i,seek=0;
  for(i = 0; i < n; i++) {
    if(req[i] >= head)
      break;
  }
  printf("\nLOOK:\n");
  if(dir==1) {
    for(int j=i;j<n;j++) {
      printf("%d ",req[j]);
      seek+=req[j]-head;
      head = req[j];
    }
    for(int j=i-1;j>=0;j--) {
      printf("%d ",req[j]);
      seek+=head-req[j];
      head=req[j];
    }
  }
  else {
    for(int j = i - 1; j >= 0; j--) {
      printf("%d ", req[j]);
      seek += head - req[j];
      head = req[j];
    }
    for(int j = i; j < n; j++) {
      printf("%d ", req[j]);
      seek += req[j] - head;
      head = req[j];
    }
  }
  printf("\nSeek time: %d\n", seek);
}

void CLOOK(int req[], int n, int head, int dir) {
  sort(req, n);
  int i,seek=0;
  for(i = 0; i < n; i++) {
    if(req[i] >= head)
      break;
  }
  printf("\nC-LOOK:\n");
  if(dir==1) {
    for(int j=i;j<n;j++) {
      printf("%d ",req[j]);
      seek+=req[j]-head;
      head = req[j];
    }
    seek+=head-req[0];
    head=req[0];
    for(int j=0;j<=i-1;j++) {
      printf("%d ",req[j]);
      seek+=head-req[j];
      head = req[j];
    }
  }
  else {
    for(int j=i-1;j>=0;j--) {
      printf("%d ",req[j]);
      seek+=head-req[j];
      head = req[j];
    }
    seek+=req[n-1]-head;
    for(int j=n-1;j>=i;j--) {
      printf("%d ",req[j]);
      seek+=head-req[j];
      head = req[j];
    }
  }
  printf("\nSeek time: %d\n", seek);
}

void main() {
  int req[20], n, head, dir, size;

  printf("Enter number of requests: ");
  scanf("%d", &n);
  printf("Enter request sequence: ");
  for(int i = 0; i < n; i++) scanf("%d", &req[i]);
  printf("Enter initial head position: ");
  scanf("%d", &head);
  printf("Enter disk direction (0 = left, 1 = right): ");
  scanf("%d", &dir);
  printf("Enter total disk size: ");
  scanf("%d", &size);

  FCFS(req, n, head);
  SSTF(req, n, head);
  SCAN(req, n, head, dir, size);
  CSCAN(req, n, head, dir, size);
  LOOK(req, n, head, dir);
  CLOOK(req, n, head, dir);

}