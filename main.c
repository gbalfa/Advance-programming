/* Laboratory Advance Programming */
/* Authors: Gabriel Badilla & Rodrigo Kobayashi */
/* Compiler: gcc */
#include "basicPolynomialArithmetics.h"
#include "doublyLinkedListPolynomial.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  int n;
  printf("Enter the degree of the polynomial to generate: ");
  scanf("%d", &n);

  struct Polynomial *polynomial = generatePolynomial(n);
  printf("Generated polynomial:\n");
  printPolynomial(polynomial->head);
  struct Polynomial *copyPoly = copyPolynomial(polynomial);
  printf("\nPolynomial copy:\n");
  printPolynomial(copyPoly->head);

  printf("\nSubstrahend:\n");
  struct Polynomial *subtrahend = generatePolynomial(10);
  printPolynomial(subtrahend->head);

  printf("\nPolynomial subtraction:\n");
  struct Polynomial *difference = subtractPolynomials(polynomial, subtrahend);
  printPolynomial(difference->head);

  printf("\nPolynomial sum:\n");
  struct Polynomial *sum = addPolynomials(polynomial, copyPoly);
  printPolynomial(sum->head);

  freePolynomial(polynomial);
  freePolynomial(copyPoly);
  freePolynomial(subtrahend);

  return 0;
}
