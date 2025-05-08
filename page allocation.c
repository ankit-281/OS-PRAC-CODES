#include <stdio.h>
#include <limits.h>

void printFrame(int status, int f, int frame[]) {
  if(status==0)
    printf("\nF ");
  else
    printf("\nH ");
  for(int i=0;i<f;i++) {
    if(frame[i]!=-1)
      printf(" %d ",frame[i]);
  }
}

void fifo(int p, int f, int page[]) {
  int frame[10], next[10], j, hits=0, faults=0, k=0;
  printf("\nFIFO:\n");
  for(int j=0;j<f;j++)
    frame[j]=-1;
  for(int i=0;i<p;i++) {
    for(j=0;j<f;j++) {
      if(page[i]==frame[j]) {
        hits++;
        printFrame(1, f, frame);
        break;
      }
    }
    if(j==f) {
      frame[k]=page[i];
      k=(k+1)%f;
      faults++;
      printFrame(0, f, frame);
    }
  }
}
int findidxopt(int p, int f, int page[], int frame[], int start) {
  int farthest = -1, idx = -1;
  for (int j = 0; j < f; j++) {
    int i;
    for (i = start; i < p; i++) {
      if (frame[j] == page[i]) {
        if (i > farthest) {
          farthest = i;
          idx = j;
        }
        break;
      }
    }
    if (i == p)
      return j; // page not used again
  }
  return (idx == -1) ? 0 : idx;
}
void opt(int p, int f, int page[]) {
  int frame[10], j, hits=0, faults=0, filled=0;
  printf("\nOPT:\n");
  for(int j=0;j<f;j++)
    frame[j]=-1;
  for(int i=0;i<p;i++) {
    for(j=0;j<f;j++) {
      if(page[i]==frame[j]) {
        hits++;
        printf("\nH ");
        for(int a=0;a<f;a++) {
          if(frame[a]!=-1)
            printf("%d ", frame[a]);
        }
        break;
      }
    }
    if(j==f) {
      faults++;
      if(filled<f) {
        frame[filled++]=page[i];
        printf("\nF ");
        for(int a=0;a<f;a++) {
          if(frame[a]!=-1)
            printf("%d ", frame[a]);
        }
      }
      else {
        int idx=findidxopt(p, f, page, frame, i+1);
        frame[idx]=page[i];
        printf("\nF ");
        for(int a=0;a<f;a++) {
          if(frame[a]!=-1)
            printf("%d ", frame[a]);
        }
      }
    }
  }
}
int findidxlru(int p, int f, int page[], int frame[], int start) {
  int lru=INT_MAX, idx=-1;
  for(int j=0;j<f;j++) {
    for(int k=start;k>=0;k--) {
      if(page[k]==frame[j]) {
        if(k<lru) {
          lru=k;
          idx=j;
        }
        break;
      }
    }
  }
  return idx;
}
void lru(int p, int f, int page[]) {
  int frame[10], hits=0, faults=0, filled=0, hit;
  printf("\nLRU:\n");
  for(int j=0;j<f;j++)
    frame[j]=-1;
  for(int i=0;i<p;i++) {
    hit=0;
    for(int j=0;j<f;j++) {
      if(frame[j]==page[i]) {
        hits++;
        hit=1;
        printFrame(1, f, frame);
        break;
      }
    }
    if(hit==0) {
      if(filled<f) {
        frame[filled++]=page[i];
        printFrame(0, f, frame);
      }
      else {
        int idx=findidxlru(p, f, page, frame, i-1);
        frame[idx]=page[i];
        printFrame(0, f, frame);
      }
    }
  }
}

void lfu(int p, int f, int page[]) {
  int frame[10], freq[10], hits = 0, faults = 0, filled = 0;
  printf("\nLFU:\n");

  for (int i = 0; i < f; i++) {
    frame[i] = -1;
    freq[i] = 0;
  }

  for (int i = 0; i < p; i++) {
    int hit = 0;
    for (int j = 0; j < f; j++) {
      if (frame[j] == page[i]) {
        freq[j]++;
        hits++;
        hit = 1;
        printFrame(1, f, frame);
        break;
      }
    }
    if(!hit) {
      faults++;
      if (filled < f) {
        frame[filled] = page[i];
        freq[filled] = 1;
        filled++;
        printFrame(0, f, frame);
      } else {
        // find min freq
        // start from cross and keep going till u find a page that is in frame and whose frequency is equal to minimum frequency
      }
    }
  }

}
void main() {
  int p, f, page[10];
  printf("Enter no of pages: ");
  scanf("%d", &p);
  printf("Enter no of frames: ");
  scanf("%d", &f);
  printf("Enter page stream: ");
  for(int i=0;i<p;i++)
    scanf("%d", &page[i]);
  fifo(p, f, page);
  opt(p, f, page);
  lru(p, f, page);
  lfu(p, f, page);
}
