/* Laboratory 1 Advance Programming */
/* Authors: Gabriel Badilla & Rodrigo Kobayashi */
/* Compiler: gcc */
#include "doublyLinkedListPolynomial.h"
#include "basicPolynomialArithmetics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int n;

  printf("Enter the degree of the polynomial to generate: ");
  scanf("%d", &n);

  struct Polynomial *polynomial = generatePolynomial(n);
  printPolynomial(polynomial->head);

  struct Polynomial *copyPoly = copyPolynomial(*polynomial);
  printPolynomial(copyPoly->head);

  freeList(polynomial);
  freeList(copyPoly);

  return 0;
}
