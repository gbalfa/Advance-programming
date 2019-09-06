/* Laboratory Advance Programming */
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
  printf("Generated polynomial:\n");
  printPolynomial(polynomial->head);
  struct Polynomial *copyPoly = copyPolynomial(polynomial);
  printf("\nPolynomial copy:\n");
  printPolynomial(copyPoly->head);
  //Second copy.
  struct Polynomial *copy2Poly = copyPolynomial(polynomial);

  printf("\nPolynomial substraction:\n");
  struct Polynomial* substract = substractPolynomials(polynomial, copyPoly);
  printPolynomial(substract->head);

  printf("\nPolynomial sum:\n");
  struct Polynomial* sum = addPolynomials(polynomial, copy2Poly);
  printPolynomial(sum->head);

  freeList(polynomial);
  freeList(copyPoly);

  return 0;
}
