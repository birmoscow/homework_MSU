#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"


/*
 * A function for comparing two elements.
 * arg - comparison argument
 * a - element on the left
 * b - element on the right
 * counter - pointer to the counter being modified
 */

static int comparison(int arg, int a, int b, int * counter) {
  /* 
   * args :
   * -2 --- <
   * -1 --- <=
   *  0 --- ==
   *  1 --- >=
   *  2 --- >
   */
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
 * upd 22.02.2022
 */

static void createArraySorted(int n, int * a) {
  long long int left = -2147483648,
                size = 4294967296 / n,
                right = left + size;
  
  for(int i = 0; i < n; i++) {
    a[i] = (int)(rand() % (right - left + 1) + left);
    right += size;
    left += size;
  }
}



/*
 * Random generation of an array sorted in reverse order.
 * upd 22.02.2022 
 */

static void createArrayReversed(int n, int * a) {
  long long int right = 2147483647,
                size = 4294967296 / n,
                left = right - size;
  
  for(int i = 0; i < n; i++) {
    a[i] = (int)(right - rand() % (right - left + 1));
    right -= size;
    left -= size;
  }
}



/*
 * Random array generation
 * upd 22.02.2022 
 */

static void createArrayRandom(int n, int * a) {
  for(int i = 0; i < n; i++) {
    a[i] = (int)(-2147483647 + rand() % (4294967296));
  }
}



/*
 * Bubble sorting with the output of the number of comparisons and moves.
 */

static void bubleSort(int n, int * a) {
  int x, *com = calloc(1, sizeof(int)), mov = 0;

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
  int *com = calloc(1, sizeof(int)), mov = 0;

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
 * 
 *
 * An array of flags is created that stores
 * information about the checked elements
 * 
 * upd 22.02.2022 
 * 
 */

static int testArray(int * a, int * aCopy, int n) {
  
  /* 
   * upd 22.02.2022 
   * read the annotation
   */
  char *arrFlag = calloc(n, 1);
  
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if( a[i] == aCopy[j] && !arrFlag[j] ) {
        if(j > 0 && aCopy[j-1] > a[i] && arrFlag[j-1] != 1) {
          free(arrFlag);
          return 0;
        }
        if(j < n-1 && aCopy[j+1] < a[i] && arrFlag[j+1] != 1) {
          free(arrFlag);
          return 0;
        }
        arrFlag[j] = 1;
        break;
      }
      if(j == n - 1) {
        free(arrFlag);
        return 0;
      }
    }
  } 
  free(arrFlag);
  return 1;
}

int main(void) {
  
  //upd 22.02.2022
  srand(time(NULL));
  
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
  createArrayRandom(n, arrRandFirst);
  createArrayRandom(n, arrRandSecond);



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










/* 
   ----------------------------------:**++++++++++++++++++++++++++++=@
   ----------------------------------:+++++++***++++++++++++++++++++=@
   ----------------------------------:+++++*++++++++++++++++++++++++++
   ---------------------------------::++++++++++++++++++++++++++++++=#
   ----------------------------::=%%+@@%====%%%%%=++++++++++++++++++=#
   ----------------------:+====%%@@@@@@#@@%@@@@#@%@=++++++++++++=+++=%
   --------------------*%%%=%@@##@@@@@@@@@@@@@@@@@#@@%=+++++++++++++++
   -------------------==%@@##@@@@@@####@@@#%@@#@######@%=+++++=%@@=+=@
   ----------------:=@@@@@##@###@#####@@####@@#######@#@@%@=@#@%@@===%
   --------------+%@@#@@##@%%@###@@%@@@###############@@@@@=%=++=%===%
   ------------*%@@#@%@@@##@@##@%%%@%@@##@@############@###%===%%%%@@@
   -----------*@@@#@@@########@@%%@@@%@#@%%@###############@@@%%%%%@@@
   -----------%@@#@@##########@@@%%+++%@%==@###############@###@%%%%@@
   ----::+=:-+@@#@@#####@@@%%%==+++++%%=%@#@@#############@@@###@%%%@@
   +%#@=:---:@#@%#######@%==++++***++=@@@@@@@@#############@@####%%%@@
   @==++*---%@@@######@%+++********+++=@##################@@@@##@%%%@@
   ###%%*--=@@########=++*****++==%%%%=++===%@################@#@%%%@@
   =%%@@=:+@#########=++***++=%%%%%%@@####@=+=@################@%%%%@@
   *+=%@@=@@########%+****++=======%%%%%%@##%====%%%%@########@@%%%%@@
   =++===%@%#######%++****++=%%@@#@@####@%%%%==%%%@#####@%###@@@%%%%@@
   %@@@@@@@==@###@@=++*****++++====%%@@##@%=+++=@@#@@@#######@@%%%%%%%
   @@@@@@@#=+%@=+%@=++*********++==%%@@@%%%=+**+######@%@#####@%%%%=++
   ##@%@#%@@++*=++++*************++++++++++++**+@@@@####%########@%%++
   ######%@#@**++**+**++++**********************=@##@%%@%####%*@@@%@##
   ######@@###%==+++**++++***++++++===+*********+===%%%==#########%@##
   #####@@@######+++++++++++++===%%%%%==+++++++=+==+***+@#########%@##
   ##=**+=%@@###@+++++++++====%%%%==++=%%@@#%%%%%%%==+++#@@@#####@%@##
   =****++==%###%+++++++++++=%====++++===%@@@@@@@@%%%========%%%%%%%%@
   +***+++==%@##=+++++++++=+===%#@%========%%%%%%@@%%%%#%+****++++++++
   **+++=%=@@@##++===============%%+=+=+%@@@@@@@@@@%%@####%===+=++++++
   *++*+==%%%@#@++=============++++=%##@%=+=%##@@%%%%#######@@%=++=%%%
   +=++==%@@@@#%+++============+++++===%@@@%%%%%%%%@###############@%@
   ++++==%@@@##==++========++++++++===%%%%%%%%=%%@@###########@#######
   +=++=%@@@@##=======%====+++++++===%%@@%%%%=%@@#####################
   ====%%%@@###%======%%%%====+++++==%%%%====%@#######################
   ##%=@%@@####%%======%%%%%%%=============%@#########################
   ##%=%=%@@###@%%======%%%%@@@@%%%%%%%%%@@###########################
   ####%+%%@###@%%%=======%%%%@@@@@@@@@@@##@##########################
   #####%%%@###@@%%==========%%%%%@@@@@@###@#@########################
   #####@=@@####@@%%=====%%%%==%%%@@@@@###@@@%@#######################
   ######=@@######@%%%%%==%%%%%%%@@@@@##@##@@#########################
   #####%%@@#######@@@@@%%%%%%@@@@@#####@@@%@#########################
   ####@++%###########################@@%%@@##################@#@#####
   ####=%@############################@%%@@####################@@@@###
   I discovered that I’ve got
   Relatives and they’re my lot
   They are woods that are so dear
   Friends of corn and every ear
   Streams of water, skies of blue
   I will tell them: “I love you”.
   It’s the Homeland of mine
   I will love it all the time.
  
*/
