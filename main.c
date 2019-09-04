/* Laboratory 1 Advance Programming */
/* Authors: Gabriel Badilla & Rodrigo Kobayashi */
/* Compiler: gcc */
#include "doublyLinkedListPolynomial.h"
#include "basicPolynomialArithmetics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  struct doublyLinkedList *polynomial =
      (struct doublyLinkedList *)malloc(sizeof(struct doublyLinkedList));
  polynomial->head = NULL;
  polynomial->tail = NULL;

  int i, n;
  double a = 10.0; /* --> range of rand generation [0,a] */
  time_t t;

  printf("Enter the degree of the polynomial to generate: ");
  scanf("%d", &n);

  /* Intializes random number generator */
  srand((unsigned)time(&t));

  /* construct the polynomial */
  for (i = n; i >= 0; --i)
    push(polynomial, (((double)rand() / (double)(RAND_MAX)) * a), i);

  printPolynomial(polynomial->head);
  struct doublyLinkedList *copyPoly = copyPolynomial(*polynomial);
  printPolynomial(copyPoly->head);
  freeList(polynomial);
  freeList(copyPoly);

  return 0;
}
