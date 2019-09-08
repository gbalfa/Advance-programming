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
  // Second copy.
  struct Polynomial *copy2Poly = copyPolynomial(polynomial);

  printf("\nPolynomial subtraction:\n");
  struct Polynomial *subtract = subtractPolynomials(polynomial, copyPoly);
  printPolynomial(subtract->head);

  printf("\nPolynomial sum:\n");
  struct Polynomial *sum = addPolynomials(polynomial, copy2Poly);
  printPolynomial(sum->head);

  freePolynomial(polynomial);
  freePolynomial(copyPoly);
  freePolynomial(copy2Poly);

  return 0;
}
