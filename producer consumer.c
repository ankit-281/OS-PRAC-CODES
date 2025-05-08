#include <stdio.h>
#include <conio.h>
#define SIZE 5 

int buffer[SIZE], in=0, out=0, count;

void producer() {
  int itemp;
  if(count==SIZE) {
    printf("Buffer full\n");
  }
  else {
    printf("Enter item to produce: ");
    scanf("%d", &itemp);
    buffer[in] = itemp;
    in = (in+1)%SIZE;
    count++;
    printf("Item produced: %d\n", itemp);
  }
}

void consumer() {
  int itemc;
  if(count==0) {
    printf("Buffer empty\n");
  }
  else {
    itemc = buffer[out];
    out = (out+1)%SIZE;
    count--;
    printf("Item consumed: %d\n", itemc);
  }
}

void main() {
  int n;
  do {
    printf("Enter 1 for producer, 2 for consumer, 3 to exit: ");
    scanf("%d", &n);
    switch(n) {
      case 1:
      producer();
      break;
      case 2:
      consumer();
      break;
      case 3:
      printf("Exiting...");
      break;
      default:
      printf("Enter valid input.\n");
    }
  }
  while(n!=3);
}