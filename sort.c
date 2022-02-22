#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

/*
 * homework 1
 * 22.02.2022
 */



/*
 * A function for comparing two elements.
 * arg - comparison argument
 * a - element on the left
 * b - element on the right
 * counter - pointer to the counter being modified
 */

static int comparison(int arg, int a, int b, int * counter) {
  /* args :
   * -2 --- <
   * -1 --- <=
   *  0 --- ==
   *  1 --- >=
   *  2 --- >
   * */
  (*counter)++;
  if(arg == -2 && a < b)
    return 1;
  else if(arg == -1 && a <= b)
    return 1;
  else if(arg == 0 && a == b)
    return 1;
  else if(arg == 1 && a >= b)
    return 1;
  else if(arg == 2 && a > b)
    return 1;
  else return 0;
}



/*
 * Random generation of an array sorted in order.
 */

static void createArraySorted(int n, int * a) {
  srand (time(NULL) + 10);
  a[0] = rand() % (n*10) + 1;
  for(int i = 1; i < n; i++) {
    a[i] = a[i-1] + 1;
  }
}



/*
 * Random generation of an array sorted in reverse order.
 */

static void createArrayReversed(int n, int * a) {
  srand (time(NULL) + 50);
  a[0] = rand() % (n*10) + n;
  for(int i = 1; i < n; i++) {
    a[i] = a[i-1] - 1;
  }
}



/*
 * Random array generation 1
 * seed - time
 */

static void createArrayRandom1(int n, int * a) {
  srand (time(NULL));
  a[0] = rand() % 10000000 + 1;
  for(int i = 1; i < n; i++) {
    a[i] = rand() % 10000000 + 1;
  }
}



/*
 * Random array generation 2
 * seed - time + 25500
 */

static void createArrayRandom2(int n, int * a) {
  srand (time(NULL) + 22500);
  a[0] = rand() % 1000000 + 1;
  for(int i = 1; i < n; i++) {
    a[i] = rand() % 1000000 + 1;
  }
}



/*
 * Bubble sorting with the output of the number of comparisons and moves.
 */

static void bubleSort(int n, int * a) {
  int x, *com = malloc(4), mov = 0;
  *com = 0;

  for(int i = 1; i < n; i++) {
    for(int j = n-1; j >= i; j--) {
            /* a[j-1] > a[j]  */
      if(comparison(2, a[j-1], a[j], com)) {
        mov++;
        x = a[j-1];
        a[j-1] = a[j];
        a[j] = x;
      }
    }
  }

  printf("\nNumber of comparisons - %d", *com);
  printf("\nNumber of movements - %d\n", mov);
  free(com);
}



/* 
 * Quick sorting with the output of the number of comparisons and moves.
 */

static void qSort(int n, int * a) {
  int *com = malloc(4), mov = 0;
  *com = 0;

  void sort(int L, int R) {
    int i = L, j = R, w, x = a[ (L+R) / 2];
    do {
      while (/*a[i] < x*/ comparison(-2, a[i], x, com)) {
        i++;
      }
      while (/*x < a[j]*/ comparison(-2, x, a[j], com)) {
        j--;
      }
      if(i <= j) {
        if(i != j) {
          mov++;
          w = a[i];
          a[i] = a[j];
          a[j] = w;
        }
        i++;
        j--;
      }
    } while(i <= j);
      if (L < j) sort(L, j);
      if (i < R) sort(i, R);
  }

  sort(0, n - 1);

  printf("\nNumber of comparisons - %d", *com);
  printf("\nNumber of movements - %d\n", mov);

  free(com);
}



/* 
 * Testing function.
 * 
 * Based on the selection of an element in the original
 * array and searching for it in the sorted array with checking 
 * the correctness of the position.
 */

static int testArray(int * a, int * aCopy, int n) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if(a[i] == aCopy[j]) {
        if(j > 0 && aCopy[j-1] > a[i] && aCopy[j-1] != -1) {
          return 0;
        }
        if(j < n-1 && aCopy[j+1] < a[i] && aCopy[j+1] != -1) {
          return 0;
        }
        aCopy[j] = -1;
        break;
      }
      if(j == n - 1) {
        return 0;
      }
    }
  } 
  return 1;
}

int main(void) {
  printf("Homework 1\n");
  printf("Bondarenko Ivan 119 group\n");
  printf("Option 1 / 1 / 1 + 4\n");
  printf("\n\n\n");
  printf("Enter n (the number of elements in the array)\n\n>> ");

  int n;
  if(scanf("%d", &n) != 1) {
    printf("\nError: incorrect input");
    return 0;
  }
  if(n < 1){
    printf("\nError: incorrect input");
    return 0;
  }

  int *arrSorted = malloc(sizeof(int) * n),
      *arrReversed = malloc(sizeof(int) * n),
      *arrRandFirst = malloc(sizeof(int) * n),
      *arrRandSecond = malloc(sizeof(int) * n),
      *arrSortedCopy = malloc(sizeof(int) * n),
      *arrReversedCopy = malloc(sizeof(int) * n),
      *arrRandFirstCopy = malloc(sizeof(int) * n),
      *arrRandSecondCopy = malloc(sizeof(int) * n);



  createArraySorted(n, arrSorted);
  createArrayReversed(n, arrReversed);
  createArrayRandom1(n, arrRandFirst);
  createArrayRandom2(n, arrRandSecond);



  memcpy( arrSortedCopy, arrSorted, sizeof(int) * n );
  memcpy( arrReversedCopy, arrReversed, sizeof(int) * n );
  memcpy( arrRandFirstCopy, arrRandFirst, sizeof(int) * n );
  memcpy( arrRandSecondCopy, arrRandSecond, sizeof(int) * n );


  printf("\n-----------------------------------------------\n");
  printf("qSort - sorted array\n");
  qSort(n, arrSortedCopy);
  if(! testArray(arrSorted, arrSortedCopy, n)) {
    printf("\nThe array is sorted with errors");
  }
  else {
    printf("\nThe array is sorted correctly");
  }
  printf("\n-----------------------------------------------\n\n\n");



  printf("\n-----------------------------------------------\n");
  printf("qSort - reversed array\n");
  qSort(n, arrReversedCopy);
  if(! testArray(arrReversed, arrReversedCopy, n)) {
    printf("\nThe array is sorted with errors");
  }
  else {
    printf("\nThe array is sorted correctly");
  }
  printf("\n-----------------------------------------------\n\n\n");



  printf("\n-----------------------------------------------\n");
  printf("qSort - random array 1\n");
  qSort(n, arrRandFirstCopy);
  if(! testArray(arrRandFirst, arrRandFirstCopy, n)) {
    printf("\nThe array is sorted with errors");
  }
  else {
    printf("\nThe array is sorted correctly");
  }
  printf("\n-----------------------------------------------\n\n\n");



  printf("\n-----------------------------------------------\n");
  printf("qSort - random array 2\n");
  qSort(n, arrRandSecondCopy);
  if(! testArray(arrRandSecond, arrRandSecondCopy, n)) {
    printf("\nThe array is sorted with errors");
  }
  else {
    printf("\nThe array is sorted correctly");
  }
  printf("\n-----------------------------------------------\n\n\n");



  memcpy( arrSortedCopy, arrSorted, sizeof(int) * n );
  memcpy( arrReversedCopy, arrReversed, sizeof(int) * n );
  memcpy( arrRandFirstCopy, arrRandFirst, sizeof(int) * n );
  memcpy( arrRandSecondCopy, arrRandSecond, sizeof(int) * n );



  printf("\n\n\n\n");
  printf("                  |  |                 \n");
  printf("                  |  |                 \n");
  printf("                  |  |                 \n");
  printf("              ____    ____             \n");
  printf("              \\          /            \n");
  printf("               \\        /             \n");
  printf("                \\      /              \n");
  printf("                 \\    /               \n");
  printf("                  \\  /                \n");
  printf("                   \\/                 \n");
  printf("\n\n\n\n");



  printf("\n-----------------------------------------------\n");
  printf("bubleSort - sorted array\n");
  bubleSort(n, arrSortedCopy);
  if(! testArray(arrSorted, arrSortedCopy, n)) {
    printf("\nThe array is sorted with errors");
  }
  else {
    printf("\nThe array is sorted correctly");
  }
  printf("\n-----------------------------------------------\n\n\n");



  printf("\n-----------------------------------------------\n");
  printf("bubleSort - reversed array\n");
  bubleSort(n, arrReversedCopy);
  if(! testArray(arrReversed, arrReversedCopy, n)) {
    printf("\nThe array is sorted with errors");
  }
  else {
    printf("\nThe array is sorted correctly");
  }
  printf("\n-----------------------------------------------\n\n\n");



  printf("\n-----------------------------------------------\n");
  printf("bubleSort - random array 1\n");
  bubleSort(n, arrRandFirstCopy);
  if(! testArray(arrRandFirst, arrRandFirstCopy, n)) {
    printf("\nThe array is sorted with errors");
  }
  else {
    printf("\nThe array is sorted correctly");
  }
  printf("\n-----------------------------------------------\n\n\n");



  printf("\n-----------------------------------------------\n");
  printf("bubleSort - random array 2\n");
  bubleSort(n, arrRandSecondCopy);
  if(! testArray(arrRandSecond, arrRandSecondCopy, n)) {
    printf("\nThe array is sorted with errors");
  }
  else {
    printf("\nThe array is sorted correctly");
  }
  printf("\n-----------------------------------------------\n\n\n\n\n");



  free(arrSorted);
  free(arrReversed);
  free(arrRandFirst);
  free(arrRandSecond);

  free(arrSortedCopy);
  free(arrReversedCopy);
  free(arrRandFirstCopy);
  free(arrRandSecondCopy);

  return 0;
}
